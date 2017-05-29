//
// Created by chenkuan on 17-5-29.
//

#ifndef RUNTIME_VERIFICATION_SYSTEM_STATE_H
#define RUNTIME_VERIFICATION_SYSTEM_STATE_H

#include "Tran.h"
#include "../../api/c++/z3++.h"

using z3::expr;

class State {

public:
    State() = default;
    virtual ~State() = default;

    /*
     * 设置状态编号
     * @param 状态编号
     */
    virtual void setStateNum(int) = 0;

//    /*
//     * 添加变量约束
//     * @param 变量约束字符串
//     */
//    virtual void addVarConstraint(const string&) = 0;

//    /*
//     * 获取状态context指针
//     * @return context指针
//     */
//    virtual context* getContext() = 0;

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
};


#endif //RUNTIME_VERIFICATION_SYSTEM_STATE_H
