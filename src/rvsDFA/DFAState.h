//
// Created by chenkuan on 17-5-29.
//

#ifndef RUNTIME_VERIFICATION_SYSTEM_DFASTATE_H
#define RUNTIME_VERIFICATION_SYSTEM_DFASTATE_H


#include <string>
#include <set>
#include <vector>

#include "../rvsDFAInterface/State.h"
#include "../../api/c++/z3++.h"

using std::string;
using std::set;
using std::vector;
using namespace z3;

class DFAState : public State{

public:
    DFAState();
    ~DFAState();

    void setStateNum(int);
    void addExpr(expr&);
    void addTran(Tran*);

private:
    int stateNum;

    set<expr> exps; // 表达式集合
    vector <Tran*> trans;   // 转移数组
};


#endif //RUNTIME_VERIFICATION_SYSTEM_DFASTATE_H
