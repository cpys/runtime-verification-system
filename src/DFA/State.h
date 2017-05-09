//
// Created by yingzi on 2017/5/9.
//

/*
 * 记录状态中的变量与值列表
 */

#ifndef RUNTIME_VERIFICATION_SYSTEM_STATE_H
#define RUNTIME_VERIFICATION_SYSTEM_STATE_H

#include <map>

class State {
private:
    std::map<int, int> vars_value;  // 变量对应的值

public:
    bool setVarValue(int var_num, int var_value);   // 设置状态中变量的值
    bool addVarValue(int var_num, int var_value);
    int getVarValue(int var_num);   // 返回状态中变量的值
};


#endif //RUNTIME_VERIFICATION_SYSTEM_STATE_H
