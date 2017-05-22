//
// Created by yingzi on 2017/5/22.
//

#ifndef RUNTIME_VERIFICATION_SYSTEM_STATE_H
#define RUNTIME_VERIFICATION_SYSTEM_STATE_H

#include <string>
#include <map>
using std::string;
using std::map;

class State {

public:
    State() = default;
    virtual ~State() = default;

    /*
     * 初始化变量类型
     * @param <变量名，变量类型>表
     */
    virtual void initVarType(const map<string, string>&) = 0;

    /*
     * 初始化状态编号
     * @param 状态编号
     */
    virtual void initStateNum(int) = 0;

    /*
     * 初始化状态内容
     * @param 状态内容
     */
    virtual void initStateContent(const string&) = 0;

    /*
     * 添加一个转移关系
     * @param 目标状态编号，转移条件
     */
    virtual void addTran(int, const string&) = 0;

    /*
     * 获取在给定条件时能到达的下一个状态编号
     * @param 给定条件
     * @return 下一个可达状态的列表
     */
    virtual vector<int> getNextState(const string&) = 0;
};

#endif //RUNTIME_VERIFICATION_SYSTEM_STATE_H
