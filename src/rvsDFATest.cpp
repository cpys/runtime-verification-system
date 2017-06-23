//
// Created by chenkuan on 17-5-29.
//

#include <iostream>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <cstring>
#include <unistd.h>
#include <csignal>
#include <sstream>
#include <Module.h>
#include <DFAModule.h>
#include "tinyxml2/tinyxml2.h"

using std::cout;
using std::cin;
using std::cerr;
using std::endl;

void Server(Module*);
void quit(int);

int main() {
    // 建立模型
    Module* module = new DFAModule();

    module->addVarDecl("int", "x");
    module->addVarDecl("int", "y");

    module->addState(1, {"x > y + 5", "y > 0"});
    module->addState(2, {"x > 5", "y > 2"});
    module->addState(3, {"x > 7", "y > 5"});
    module->addState(4, {"x > 9", "y > 10"});
    module->addState(5, {"x > 23", "y > 17"});
    module->addState(6, {"x > 6", "y > 5"});

    module->addTran("event1", 1, 2, {"y > 2"});
    module->addTran("event2", 2, 3, {"y > 5"});
    module->addTran("event3", 3, 4, {"x > 9"});
    module->addTran("event4", 2, 6, {"y > 5"});
    module->addTran("event5", 6, 4, {"x > 9"});
    module->addTran("event6", 4, 5, {"y > 17", "x > 23"});

    module->addSpec("A", {"x > 5"});

//    Server(module);

    // 模型建立完成后，开始添加事件
    module->addEvent("event1", {{"x", "6"}});
    module->addEvent("event5", {{"x", "12"}});
    module->addEvent("event6", {{"y", "20"}, {"x", "24"}});

    // 手动输入事件
    while (true) {
        cout << "请输入事件名称：（输入event_end结束）" << endl;
        string eventName;
        cin >> eventName;
        if (eventName == "event_end") break;
        cout << "请逐行输入变量名和变量值，以空格分隔，输入var_end结束事件内的变量输入：" << endl;
        string varName, varValue;
        map<string, string> vars;
        cin >> varName;
        while (varName != "var_end") {
            cin >> varValue;
            vars[varName] = varValue;
            cin >> varName;
        }
        module->addEvent(eventName, vars);
    }

    return 0;
}

int serverSocket, clientSocket;

void Server (Module* module){
    serverSocket = socket(AF_INET, SOCK_STREAM, 0);

    struct sockaddr_in serverAddr;

    serverAddr.sin_family = AF_INET;
    serverAddr.sin_addr.s_addr = htonl(INADDR_ANY);
    serverAddr.sin_port = htons(8899);

    bind(serverSocket, (struct sockaddr*)&serverAddr, sizeof(serverAddr));

    listen(serverSocket, 5);

    cout << "server waiting for client connect" << endl;

    clientSocket = accept(serverSocket, NULL, NULL);
    if (clientSocket < 0) {
        cerr << "accept error" << endl;
        return ;
    }

    signal(SIGINT, quit);

    using namespace tinyxml2;

    char charRecv[50] = {0};
    int recvNum;
    XMLDocument xmlDocument;
    while (true) {
        memset(charRecv, 0, 50);
        if ((recvNum = recv(clientSocket, charRecv, 50, 0)) < 0) {
            cerr << "recv error" << endl;
            break;
        }

        cout << charRecv << endl;

        XMLError xmlError = xmlDocument.Parse(charRecv);
        if (xmlError != XML_SUCCESS) {
            cerr << "Cannot parse " << charRecv << endl;
            continue;
        }
        XMLElement* root = xmlDocument.FirstChildElement();
//        cout << root->Attribute("name") << " " << root->Attribute("value") << endl;

        string eventName = root->Attribute("name");
        string eventValue = root->Attribute("value");
        std::stringstream ss(eventValue);
        string eventVar, eventVarOper, eventVarValue;
        ss >> eventVar >> eventVarOper >> eventVarValue;
        module->addEvent(eventName, {{eventVar, eventVarValue}});

//        cout << charRecv << endl;
    }

    quit(SIGINT);
}

void quit(int signum) {
    close(serverSocket);
    close(clientSocket);
    exit(0);
}