//
// Created by yingzi on 2017/5/9.
//

/*
 * 单个转移关系
 */

#ifndef RUNTIME_VERIFICATION_SYSTEM_TRAN_H
#define RUNTIME_VERIFICATION_SYSTEM_TRAN_H

#include <string>

class Tran {
private:
    int state_from; // 转移来源状态
    int state_to;   // 转移目标状态
    std::string condition;  // 发生此转移的条件
    std::string operation;  // 此转移发生时的操作

public:
    Tran();
    Tran(int state_from, int state_to);

    int getStateFrom();
    int getStateTo();
    bool addCondition(std::string condition);
};


#endif //RUNTIME_VERIFICATION_SYSTEM_TRAN_H
