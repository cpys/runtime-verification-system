//
// Created by chenkuan on 17-5-29.
//

#ifndef RUNTIME_VERIFICATION_SYSTEM_DFASTATE_H
#define RUNTIME_VERIFICATION_SYSTEM_DFASTATE_H

#include <State.h>
#include <Tran.h>
#include <vector>

using std::vector;

class DFAState : public State{

public:
    DFAState();
    ~DFAState() override = default;

    void setStateNum(int stateNum) override;
    void addExpr(expr &exp) override;
    void addTran(Tran *tran) override;

    int getStateNum() const override ;

    int getNextState(Event *event, solver &slv) override;

    const set<expr> &getExps() const override;

private:
    int stateNum;

    set<expr> exps; // 表达式集合
    vector <Tran*> trans;   // 转移数组
};


#endif //RUNTIME_VERIFICATION_SYSTEM_DFASTATE_H
