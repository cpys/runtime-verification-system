//
// Created by chenkuan on 17-5-29.
//

#ifndef RUNTIME_VERIFICATION_SYSTEM_TRAN_H
#define RUNTIME_VERIFICATION_SYSTEM_TRAN_H

#include <string>
#include "../../api/c++/z3++.h"

using std::string;
using z3::expr;

class Tran {

public:
    Tran() = default;
    virtual ~Tran() = default;

    /*
     * 设置转移类的名称
     * @param 转移名称
     */
    virtual void setName(const string&) = 0;

    /*
     * 设置转移源状态编号
     * @param 源状态编号
     */
    virtual void setSourceStateNum(int) = 0;

    /*
     * 设置转移目标状态编号
     * @param 目标状态编号
     */
    virtual void setDestStateNum(int) = 0;

    /*
     * 添加expr到expr集合中
     * @param expr
     */
    virtual void addExpr(expr&) = 0;
};


#endif //RUNTIME_VERIFICATION_SYSTEM_TRAN_H
