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
};


#endif //RUNTIME_VERIFICATION_SYSTEM_STATE_H
