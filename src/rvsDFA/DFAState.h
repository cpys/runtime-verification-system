//
// Created by chenkuan on 17-5-29.
//

#ifndef RUNTIME_VERIFICATION_SYSTEM_DFASTATE_H
#define RUNTIME_VERIFICATION_SYSTEM_DFASTATE_H


#include <string>
#include <set>
#include <vector>

#include "../rvsDFAInterface/State.h"

using std::string;
using std::set;
using std::vector;

class DFAState : public State{

public:
    DFAState();
    ~DFAState() override;

    void setStateNum(int stateNum) override;
    void addExpr(expr &exp) override;
    void addTran(Tran *tran) override;

    int getStateNum() const override ;

private:
    int stateNum;

    set<expr> exps; // 表达式集合
    vector <Tran*> trans;   // 转移数组
};


#endif //RUNTIME_VERIFICATION_SYSTEM_DFASTATE_H
