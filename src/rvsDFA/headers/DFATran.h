//
// Created by chenkuan on 17-5-29.
//

#ifndef RUNTIME_VERIFICATION_SYSTEM_DFATRAN_H
#define RUNTIME_VERIFICATION_SYSTEM_DFATRAN_H

#include <Tran.h>

class DFATran : public Tran{
public:
    DFATran() = default;
    ~DFATran() override = default;

    void setName(const string &tranName) override ;
    void setSourceState(State *state) override;
    void setDestState(State *state) override;
    void addExpr(expr &exp) override ;

    const string getName() const override;
    State *getSourceState() const override;
    State *getDestState() const override;
    int getSourceStateNum() const override;
    int getDestStateNum() const override;

    const vector<expr> &getExps() const override;

    bool checkEvent(Event *event, solver &slv) override;

private:
    string tranName;
    State* sourceState;
    State* destState;

    vector<expr> exps; // 表达式集合
};


#endif //RUNTIME_VERIFICATION_SYSTEM_DFATRAN_H
