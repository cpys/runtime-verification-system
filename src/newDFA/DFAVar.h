//
// Created by yingzi on 2017/5/22.
//

#ifndef RUNTIME_VERIFICATION_SYSTEM_DFAVAR_H
#define RUNTIME_VERIFICATION_SYSTEM_DFAVAR_H

#include <string>
#include <cassert>
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

    friend operator == (const Var& other) {
        if (varType != other.getVarType()) return false;
        return varValue == other.getVarValue();
    }

    friend operator != (const Var& other) {
        return !(*this == other);
    }

    friend operator < (const Var& other) {
        if (varType == NULL || other.getVarType() == NULL) {
            // TODO
            // 类型不能为NULL
        }
        assert(varType == other.getVarType());
        if (varType == "int") {
            return stoi(varValue) < stoi(other.getVarValue());
        }
        else if (varType == "double") {
            return stod(varValue) < stod(other.getVarValue());
        }
        else if (varType == "string") {
            return varValue < other.getVarValue();
        }
        else {
            // TODO
            // 不合法的类型
        }
    }

    friend operator <= (const Var& other) {
        return (*this == other) || (*this < other);
    }

    friend operator > (const Var& other) {
        return !(*this <= other);
    }

    friend operator >= (const Var& other) {
        return !(*this < other);
    }

private:
    string* varName;
    string* varType;
    string* varValue;
};


#endif //RUNTIME_VERIFICATION_SYSTEM_DFAVAR_H
