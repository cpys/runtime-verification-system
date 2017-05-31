//
// Created by chenkuan on 17-5-29.
//

#include <iostream>
#include <DFAModule.h>

using std::cout;
using std::cin;
using std::endl;

int main() {
    // 建立模型
    Module* module = new DFAModule();

    module->addVarDecl("int", "x");
    module->addVarDecl("int", "y");

    module->addState(1, vector<string>{"x > 3", "y > 0"});
    module->addState(2, vector<string>{"x > 5", "y > 2"});
    module->addState(3, vector<string>{"x > 7", "y > 5"});
    module->addState(4, vector<string>{"x > 9", "y > 10"});
    module->addState(5, vector<string>{"x > 23", "y > 17"});
    module->addState(6, vector<string>{"x > 6", "y > 5"});

    module->addTran("event1", 1, 2, vector<string>{"y > 2"});
    module->addTran("event2", 2, 3, vector<string>{"y > 5"});
    module->addTran("event3", 3, 4, vector<string>{"x > 9"});
    module->addTran("event4", 2, 6, vector<string>{"y > 5"});
    module->addTran("event5", 6, 4, vector<string>{"x > 9"});
    module->addTran("event6", 4, 5, vector<string>{"y > 17", "x > 23"});

    module->addSpec("A", {"x > 5"});

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