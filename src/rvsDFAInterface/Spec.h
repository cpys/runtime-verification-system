//
// Created by chenkuan on 17-5-29.
//

#ifndef RUNTIME_VERIFICATION_SYSTEM_SPEC_H
#define RUNTIME_VERIFICATION_SYSTEM_SPEC_H

#include <string>
#include <vector>
#include <c++/z3++.h>

using std::string;
using std::vector;
using z3::expr;

class Spec {

public:
    Spec() = default;
    virtual ~Spec() = default;

    /*
     * 添加时序词
     * @param 时序词
     */
    virtual void addTempWord(const string&) = 0;

    /*
     * 添加expr
     * @param expr
     */
    virtual void addExpr(expr&) = 0;

    /*
     * 获取表达式列表
     * @return 表达式列表
     */
    virtual const vector<expr> &getExps() const = 0;
};


#endif //RUNTIME_VERIFICATION_SYSTEM_SPEC_H
