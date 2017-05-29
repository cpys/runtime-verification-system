//
// Created by chenkuan on 17-5-29.
//

#ifndef RUNTIME_VERIFICATION_SYSTEM_DFATRAN_H
#define RUNTIME_VERIFICATION_SYSTEM_DFATRAN_H

#include <string>
#include <set>
#include "../rvsDFAInterface/Tran.h"
#include "../../api/c++/z3++.h"

using std::string;
using std::set;
using namespace z3;

class DFATran : public Tran{
public:
    DFATran();
    ~DFATran();

    void setName(const string&);
    void setSourceStateNum(int);
    void setDestStateNum(int);
    void addExpr(expr&);

private:
    string tranName;
    int sourceStateNum;
    int destStateNum;

    set<expr> exps; // 表达式集合
};


#endif //RUNTIME_VERIFICATION_SYSTEM_DFATRAN_H
