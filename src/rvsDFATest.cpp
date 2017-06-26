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

    module->addState(1, {"x >= 0", "x < 10"});
    module->addState(2, {"x >= 10", "x < 20"});
    module->addState(3, {"x >= 20", "x < 30"});
    module->addState(4, {"x >= 30", "x < 40"});
    module->addState(5, {"x >= 40", "x < 50"});

    module->addTran("increase", 1, 2, {"x >= 10"});
    module->addTran("increase", 2, 3, {"x >= 20"});
    module->addTran("increase", 3, 4, {"x >= 30"});
    module->addTran("increase", 4, 5, {"x >= 40"});
    module->addTran("increase", 1, 3, {"x >= 10"});
    module->addTran("increase", 2, 4, {"x >= 20"});
    module->addTran("increase", 3, 5, {"x >= 30"});
    module->addTran("decrease", 3, 1, {"x < 20"});
    module->addTran("decrease", 4, 2, {"x < 30"});
    module->addTran("decrease", 5, 3, {"x < 40"});

    module->initModule();

    module->addSpec({"x3 - x1 <= 20", "x5 - x3 <= 20"});

//    Server(module);

    // 模型建立完成后，开始添加事件
    module->addEvent("increase", {{"x", "12"}});
    module->addEvent("increase", {{"x", "18"}});
    module->addEvent("increase", {{"x", "29"}});
    module->addEvent("decrease", {{"x", "7"}});
    module->addEvent("increase", {{"x", "26"}});
    module->addEvent("increase", {{"x", "43"}});
    module->addEvent("decrease", {{"x", "19"}});
    module->addEvent("decrease", {{"x", "25"}});
    module->addEvent("increase", {{"x", "37"}});
    module->addEvent("increase", {{"x", "49"}});

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