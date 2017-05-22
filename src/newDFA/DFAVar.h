//
// Created by yingzi on 2017/5/22.
//

#ifndef RUNTIME_VERIFICATION_SYSTEM_DFAVAR_H
#define RUNTIME_VERIFICATION_SYSTEM_DFAVAR_H

#include <string>
#include "../DFAInterface/Var.h"
using namespace std;

class DFAVar : public Var {
public:
    DFAVar();
    ~DFAVar();
    void setVarName(const string&);
    void setVarType(const string&);
    void setVarValue(const string&);

    string* getVarName();
    string* getVarType();
    string* getVarValue();

private:
    string* varName;
    string* varType;
    string* varValue;
};


#endif //RUNTIME_VERIFICATION_SYSTEM_DFAVAR_H
