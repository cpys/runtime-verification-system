#include <iostream>
#include <cstring>
#include <csignal>
#include <sstream>
#include "Model.h"

using std::cout;
using std::cin;
using std::cerr;
using std::endl;

int main() {
    // 建立模型
    auto model = new Model();

    model->addVarDecl("int", "x");

    model->addStartState(1, {"x >= 0", "x < 10"});
    model->addState(2, {"x >= 10", "x < 20"});
    model->addState(3, {"x >= 20", "x < 30"});
    model->addState(4, {"x >= 30", "x < 40"});
    model->addEndState(5, {"x >= 40", "x < 50"});

    model->addTran("increase", 1, 2);
    model->addTran("increase", 2, 3);
    model->addTran("increase", 3, 4);
    model->addTran("increase", 4, 5);
    model->addTran("increase", 1, 3);
    model->addTran("increase", 2, 4);
    model->addTran("increase", 3, 5);
    model->addTran("decrease", 3, 1);
    model->addTran("decrease", 4, 2);
    model->addTran("decrease", 5, 3);

    model->addSpec("x3 - x1 <= 20");
    model->addSpec("x5 - x3 <= 20");

    if (!model->initModel()) {
        cerr << "模型初始化失败！" << endl;
        return -1;
    }

    // 模型建立完成后，开始添加事件
    model->addEvent("increase", {{"x", "12"}});
    model->addEvent("increase", {{"x", "18"}});
    model->addEvent("increase", {{"x", "29"}});
    model->addEvent("decrease", {{"x", "7"}});
    model->addEvent("increase", {{"x", "26"}});
    model->addEvent("increase", {{"x", "43"}});
    model->addEvent("decrease", {{"x", "19"}});
    model->addEvent("decrease", {{"x", "25"}});
    model->addEvent("increase", {{"x", "37"}});
    model->addEvent("increase", {{"x", "49"}});

//    // 手动输入事件
//    while (true) {
//        cout << "请输入事件名称：（输入event_end结束）" << endl;
//        string eventName;
//        cin >> eventName;
//        if (eventName == "event_end") break;
//        cout << "请逐行输入变量名和变量值，以空格分隔，输入var_end结束事件内的变量输入：" << endl;
//        string varName, varValue;
//        map<string, string> vars;
//        cin >> varName;
//        while (varName != "var_end") {
//            cin >> varValue;
//            vars[varName] = varValue;
//            cin >> varName;
//        }
//        model->addEvent(eventName, vars);
//    }

    return 0;
}