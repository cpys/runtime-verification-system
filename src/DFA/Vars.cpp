//
// Created by yingzi on 2017/5/9.
//

#include "Vars.h"

Vars::Vars() {
    this->next_var_num = 1;
}

int Vars::addVar(std::string var_name) {
    if (this->vars_num.find(var_name) != this->vars_num.end()) {
        return this->vars_num[var_name];
    }
    else {
        this->vars_num[var_name] = this->next_var_num;
        this->vars_name[this->next_var_num] = var_name;
        this->next_var_num++;
        return this->next_var_num - 1;
    }
}

int Vars::getVarNum(std::string var_name) {
    return this->addVar(var_name);
}

std::string Vars::getVarName(int var_num) {
    return this->vars_name[var_num];
}