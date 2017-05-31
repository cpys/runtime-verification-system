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

    void addTempWord(const string &tempWord) override;
    void addExpr(expr &exp) override;

    const vector<expr> &getExps() const override ;

private:
    string tempWord;
    vector<expr> exps;
};


#endif //RUNTIME_VERIFICATION_SYSTEM_DFASPEC_H
