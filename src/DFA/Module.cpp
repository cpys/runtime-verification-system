//
// Created by yingzi on 2017/5/9.
//

#include "Module.h"

Module::Module() {
    this->module_name = "DefaultModule";
}

int Module::addVar(const std::string& var) {
    return this->vars.addVar(var);
}

//int Module::addState(State& state) {
//    return this->states.addState(state);
//}
//
//bool Module::addTran(Tran& tran) {
//    return this->trans.addTran(tran);
//}

int Module::addState(const std::string &state_string) {
    // TODO
    // 根据state_string解析变量与其值，填入新建的状态中
    State state(state_string);
    return this->states.addState(state);
}

bool Module::addTran(const int &source, const int &target, const std::string &condition) {
    // TODO
    // 根据condition解析转移中的变量表达式，填入新建的Tran中
    Tran tran(source, target);
    tran.addCondition(condition);
    return this->trans.addTran(tran);
}