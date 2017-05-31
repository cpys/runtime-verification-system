//
// Created by chenkuan on 17-5-29.
//

#ifndef RUNTIME_VERIFICATION_SYSTEM_DFASPEC_H
#define RUNTIME_VERIFICATION_SYSTEM_DFASPEC_H

#include <Spec.h>

class DFASpec : public Spec {

public:
    DFASpec() = default;
    ~DFASpec() override = default;

    void addTempWord(const string &tempWord) override ;
    void addConstraint(const string &constraint) override ;
    void addExpr(expr &exp) override;

    const vector<expr> &getExps() const override ;
    const string &getTempWord() const override ;
    const vector<string> &getConstraints() const override ;

    const string toString() const override ;

private:
    string tempWord;
    vector<string> constraints;
    vector<expr> exps;
};


#endif //RUNTIME_VERIFICATION_SYSTEM_DFASPEC_H
