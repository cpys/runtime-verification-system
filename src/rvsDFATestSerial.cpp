//
// Created by yingzi on 2017/6/26.
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
#include <tinyxml2.h>
#include <SerialForward.h>

using std::cout;
using std::cin;
using std::cerr;
using std::endl;

void quit(int);

SerialForward serialForwardVM("/dev/pts/1");
SerialForward serialForwardPort("/dev/ttyS0");

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

    signal(SIGINT, quit);

    // 初始化串口监控
    serialForwardPort.init();
    serialForwardVM.init();

    // 循环从串口获取消息解析成事件
    using namespace tinyxml2;
    XMLDocument xmlDocument;
    string message;
    while (true) {
        message = serialForwardVM.recvMessage();
        if (message == "") continue;
//        cout << message << endl;

        XMLError xmlError = xmlDocument.Parse(message.c_str());
        if (xmlError != XML_SUCCESS) {
            cerr << "Cannot parse " << message << endl;
            continue;
        }

        XMLElement* root = xmlDocument.FirstChildElement();
        string eventName = root->Attribute("name");
        string eventValue = root->Attribute("value");

        std::istringstream iss(eventValue);
        string eventVar, eventVarOper, eventVarValue;
        iss >> eventVar >> eventVarOper >> eventVarValue;

        if (module->addEvent(eventName, {{eventVar, eventVarValue}})) {
            serialForwardPort.sendMessage(message);
        }
        cout << endl;
    }

    return 0;
}

void quit(int signum) {
    serialForwardVM.closePort();
    serialForwardPort.closePort();
    exit(0);
}