//
// Created by yingzi on 2017/5/9.
//

/*
 * 记录状态中的变量与值列表
 */

#ifndef RUNTIME_VERIFICATION_SYSTEM_STATE_H
#define RUNTIME_VERIFICATION_SYSTEM_STATE_H

#include <map>
#include <string>

class State {
private:
    std::map<int, int> vars_value;  // 变量对应的值
    std::string state_string;

public:
    State();
    explicit State(std::string& state_string);

    bool setVarValue(int var_num, int var_value);   // 设置状态中变量的值
    bool addVarValue(int var_num, int var_value);
    int getVarValue(int var_num);   // 返回状态中变量的值

    bool operator < (const State& other) const {
        if (this->vars_value.size() != other.vars_value.size()) {
            return this->vars_value.size() < other.vars_value.size();
        }
        else {
            for (auto it1 = this->vars_value.rbegin(), it2 = other.vars_value.rbegin(); it1 != this->vars_value.rend(); it1++, it2++) {
                if (it1->first != it2->first) return it1->first < it2->first;
                else if (it1->second != it2->second) return it1->second < it2->second;
            }
        }
        return this->vars_value < other.vars_value;
    }
};


#endif //RUNTIME_VERIFICATION_SYSTEM_STATE_H
