//
// Created by yingzi on 2017/11/30.
//

#ifndef RUNTIME_VERIFICATION_SYSTEM_SPEC_H
#define RUNTIME_VERIFICATION_SYSTEM_SPEC_H

#include <z3++.h>

using Z3Expr = z3::expr;

class Spec {
  public:
    Spec() = default;
    ~Spec();

    /**
     * 设置Z3表达式
     * @param z3Expr Z3表达式
     */
    void setZ3Expr(const Z3Expr &z3Expr);
    /**
     * 获取存储的Z3表达式
     * @return
     */
    const Z3Expr &getZ3Expr();

};


#endif //RUNTIME_VERIFICATION_SYSTEM_SPEC_H
