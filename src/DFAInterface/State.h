//
// Created by yingzi on 2017/5/22.
//

#ifndef RUNTIME_VERIFICATION_SYSTEM_STATE_H
#define RUNTIME_VERIFICATION_SYSTEM_STATE_H

#include <string>
#include <vector>
#include "Var.h"
using std::string;
using std::vector;

class State {

public:
    State();
    virtual ~State();

    /*
     * 初始化状态编号
     * @param 状态编号
     */
    virtual void initStateNum(int) = 0;

    /*
     * 添加变量
     * @param 变量
     */
    virtual void addVar(Var*) = 0;

//    /*
//     * 初始化状态内容
//     * @param 状态内容
//     */
//    virtual void initStateContent(const string&) = 0;

    /*
     * 添加一个转移关系
     * @param 目标状态编号，转移条件
     */
    virtual void addTran(int, const string&) = 0;

    /*
     * 获取在当前状态下能到达的下一个状态
     * @return 下一个可达状态
     */
    virtual int getNextState() = 0;

//    /*
//     * 获取在给定条件时能到达的下一个状态编号
//     * @param 给定条件
//     * @return 下一个可达状态的列表
//     */
//    virtual vector<int> getNextState(const string&) = 0;

    /*
     * 给状态提供一个内容格式化输出
     * @return 状态内容输出
     */
    virtual string toString() = 0;
};

#endif //RUNTIME_VERIFICATION_SYSTEM_STATE_H
