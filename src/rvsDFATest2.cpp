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
#include <DFAModule.h>
#include "tinyxml2/tinyxml2.h"
#include <netlink_client.h>

using std::cout;
using std::cin;
using std::cerr;
using std::endl;

void quit(int);

int main() {
    // 建立模型
    Module* module = new DFAModule();

    module->addVarDecl("int", "x");

    module->addState(1, {"x > 0"});
    module->addState(2, {"x > 1"});
    module->addState(3, {"x > 2"});
    module->addState(4, {"x > 3"});
    module->addState(5, {"x > 4"});
    module->addState(6, {"x > 5", "x < 100"});

    module->addTran("event1", 1, 2, {"x > 0"});
    module->addTran("event2", 2, 3, {"x > 0"});
    module->addTran("event3", 3, 4, {"x > 0"});
    module->addTran("event4", 4, 5, {"x > 0"});
    module->addTran("event5", 5, 6, {"x > 0", "x < 100"});

    module->addSpec("G", {"x < 100"});

    netLinkInit();

    signal(SIGINT, quit);

    using namespace tinyxml2;
    char charRecv[50] = {0};
    int recvNum;
    XMLDocument xmlDocument;
    while (true) {
        memset(charRecv, 0, 50);
        if ((recvNum = getMessage(charRecv)) < 0) {
            cerr << "recv error" << endl;
            break;
        }

//        cout << charRecv << endl;

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

    return 0;
}

void quit(int signum) {
    quitNetLink();
    exit(0);
}