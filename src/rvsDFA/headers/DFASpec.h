//
// Created by chenkuan on 17-5-29.
//

#ifndef RUNTIME_VERIFICATION_SYSTEM_DFASPEC_H
#define RUNTIME_VERIFICATION_SYSTEM_DFASPEC_H

#include <set>
#include <Spec.h>

using std::set;

class DFASpec : public Spec {

public:
    DFASpec() = default;
    ~DFASpec() override = default;

    void addTempWord(const string &tempWord) override;
    void addExpr(expr &exp) override;

private:
    string tempWord;
    set<expr> exps;
};


#endif //RUNTIME_VERIFICATION_SYSTEM_DFASPEC_H
