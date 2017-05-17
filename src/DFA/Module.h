//
// Created by yingzi on 2017/5/9.
//

#ifndef RUNTIME_VERIFICATION_SYSTEM_MODULE_H
#define RUNTIME_VERIFICATION_SYSTEM_MODULE_H

#include <string>
#include "Vars.h"
#include "States.h"
#include "Trans.h"

class Module {
private:
    std::string module_name;    // 模型名称
    Vars vars;  // 变量集
    State state0;   // 初始状态
    States states;  // 状态集
    Trans trans;    // 转移集

public:
    Module();
    int addVar(const std::string& var);   // 添加变量到变量集，返回变量编号
//    int addState(State& state); // 添加状态到状态集，返回状态编号
//    bool addTran(Tran& tran);    // 添加转移到转移集

    int addState(const std::string& state_string);    // 添加状态到状态集，返回状态编号
    bool addTran(const int& source, const int& target, const std::string& condition);   // 添加转移关系到转移集
};


#endif //RUNTIME_VERIFICATION_SYSTEM_MODULE_H
