//
// Created by chenkuan on 17-5-29.
//

#include <iostream>
#include "rvsDFA/DFAModule.h"

int main() {
    Module* module = new DFAModule();

    module->addVarDecl("int", "x");
    module->addVarDecl("int", "y");

    module->addState(1, vector<string>{"x > 3", "y > 0"});
    module->addState(2, vector<string>{"x > 5", "y > 2"});

    module->addTran("tran1", 1, 2, vector<string>{"x > 5"});

    module->addSpec("G", "x > 0");

    return 0;
}