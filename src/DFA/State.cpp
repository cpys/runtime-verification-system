//
// Created by yingzi on 2017/5/9.
//

#include "State.h"

State::State() {}

State::State(std::string& state_string) {
    // TODO
    // 根据表达式解析出变量和值填入状态
    this->state_string = state_string;
}

bool State::setVarValue(int var_num, int var_value) {
    // TODO
    return true;
}

bool State::addVarValue(int var_num, int var_value) {
    return this->setVarValue(var_num, var_value);
}

int State::getVarValue(int var_num) {
    return this->vars_value[var_num];
}