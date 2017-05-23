//
// Created by yingzi on 2017/5/22.
//

#ifndef RUNTIME_VERIFICATION_SYSTEM_DFAVAR_H
#define RUNTIME_VERIFICATION_SYSTEM_DFAVAR_H

#include <string>
#include <cassert>
#include "../../DFAInterface/Var.h"
using namespace std;

class DFAVar : public Var {
public:
    DFAVar();
    DFAVar(const string&, const string&, const string&);
    ~DFAVar();

    void setVarName(const string&);
    void setVarType(const string&);
    void setVarValue(const string&);

    string* getVarName() const;
    string* getVarType() const;

    int getVarValueInt() const;
    double getVarValueDouble() const;
    string getVarValueString() const;
//    string* getVarValue() const;

    bool operator == (const Var& other) const {
        if (*this->varType == "int") {
            return this->varValueInt == other.getVarValueInt();
        }
        else if (*this->varType == "double") {
            return this->varValueDouble == other.getVarValueDouble();
        }
        else return this->varValueString == other.getVarValueString();
    }

    bool operator != (const Var& other) const {
        return !(*this == other);
    }

    bool operator < (Var& other) {
        if (*this->varType == "int") {
            return this->varValueInt < other.getVarValueInt();
        }
        else if (*this->varType == "double") {
            return this->varValueDouble < other.getVarValueDouble();
        }
        else if (*this->varType != "string") {
            // TODO
            cout << "比较时出现不合法的类型\""  << *this->varType << "\"" << endl;
        }
        return this->varValueString < other.getVarValueString();
    }

    bool operator <= (Var& other) {
        return (*this == other) || (*this < other);
    }

    bool operator > (Var& other) {
        return !(*this <= other);
    }

    bool operator >= (Var& other) {
        return !(*this < other);
    }

private:
    string* varName;
    string* varType;
//    string* varValue;
    int varValueInt;
    double varValueDouble;
    string varValueString;

    /*
     * 根据varValue更新int、double、string等变量的值
     * @return 更新是否成功
     */
    bool updateVarTypeValue();
};


#endif //RUNTIME_VERIFICATION_SYSTEM_DFAVAR_H
