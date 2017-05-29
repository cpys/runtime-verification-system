//
// Created by chenkuan on 17-5-29.
//

#ifndef RUNTIME_VERIFICATION_SYSTEM_DFASPEC_H
#define RUNTIME_VERIFICATION_SYSTEM_DFASPEC_H

#include <set>
#include "../rvsDFAInterface/Spec.h"

using std::set;

class DFASpec : public Spec {

public:
    DFASpec();
    ~DFASpec();

    void addTempWord(const string&);
    void addExpr(expr&);

private:
    string tempWord;
    set<expr> exps;
};


#endif //RUNTIME_VERIFICATION_SYSTEM_DFASPEC_H
