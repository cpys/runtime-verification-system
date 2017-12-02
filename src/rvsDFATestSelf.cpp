#include <iostream>
#include <cstring>
#include <csignal>
#include <sstream>
#include <Module.h>

using std::cout;
using std::cin;
using std::cerr;
using std::endl;

int main() {
    // 建立模型
    Module* module = new Module();

    module->addVarDecl("int", "x");

    module->addState(1, {"x >= 0", "x < 10"});
    module->addState(2, {"x >= 10", "x < 20"});
    module->addState(3, {"x >= 20", "x < 30"});
    module->addState(4, {"x >= 30", "x < 40"});
    module->addState(5, {"x >= 40", "x < 50"});

    module->addTran("increase", 1, 2);
    module->addTran("increase", 2, 3);
    module->addTran("increase", 3, 4);
    module->addTran("increase", 4, 5);
    module->addTran("increase", 1, 3);
    module->addTran("increase", 2, 4);
    module->addTran("increase", 3, 5);
    module->addTran("decrease", 3, 1);
    module->addTran("decrease", 4, 2);
    module->addTran("decrease", 5, 3);

    module->addSpec("x3 - x1 <= 20");
    module->addSpec("x5 - x3 <= 20");

    module->initModule();

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