//
// Created by yingzi on 2017/5/9.
//

#include "Module.h"

int Module::addVar(std::string var) {
    return this->vars.addVar(var);
}

int Module::addState(State& state) {
    return this->states.addState(state);
}

bool Module::addTran(Tran& tran) {
    return this->trans.addTran(tran.getStateFrom(), tran);
}