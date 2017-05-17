//
// Created by yingzi on 2017/5/16.
//

#include <iostream>
#include "DFA/Module.h"
using namespace std;

int main() {
    Module module;
    module.addVar("x");
    module.addVar("y");

    State state0;
    module.addState(state0);
    Tran tran;
    module.addTran(tran);

    return 0;
}