//
// Created by chenkuan on 17-5-29.
//

#include <iostream>
#include <DFAModule.h>

int main() {
    // 建立模型
    Module* module = new DFAModule();

    module->addVarDecl("int", "x");
    module->addVarDecl("int", "y");

    module->addState(1, vector<string>{"x > 3", "y > 0"});
    module->addState(2, vector<string>{"x > 5", "y > 2"});

    module->addTran("event1", 1, 2, vector<string>{"x > 5"});

    module->addSpec("G", "x > 0");

    // 模型建立完成后，开始添加事件
    module->addEvent("event1", map<string, string>{{"x", "6"}});

    return 0;
}