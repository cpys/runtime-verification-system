//
// Created by chenkuan on 17-5-29.
//

#ifndef RUNTIME_VERIFICATION_SYSTEM_STATE_H
#define RUNTIME_VERIFICATION_SYSTEM_STATE_H

#include <set>
//#include <Tran.h>
#include <Event.h>
#include <c++/z3++.h>

using std::set;
using z3::expr;
using z3::solver;

class Tran;

class State {

public:
    State() = default;
    virtual ~State() = default;

    /*
     * 设置状态编号
     * @param 状态编号
     */
    virtual void setStateNum(int) = 0;

    /*
     * 向状态内expr集合中添加expr
     * @param expr
     */
    virtual void addExpr(expr&) = 0;

    /*
     * 添加转移
     * @param 转移指针
     */
    virtual void addTran(Tran*) = 0;

    /*
     * 获取状态编号
     * @return 状态编号
     */
    virtual int getStateNum() const = 0;

    /*
     * 在给定事件的情况下获取下一个可达状态，无则返回负数
     * @param 事件 求解器
     * @return 下一状态
     */
    virtual int getNextState(Event*, solver&) = 0;

    /*
     * 获取状态中的表达式集合
     * @return 表达式集合
     */
    virtual const set<expr> &getExps() const = 0;
};


#endif //RUNTIME_VERIFICATION_SYSTEM_STATE_H
