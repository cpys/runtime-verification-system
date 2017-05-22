//
// Created by yingzi on 2017/5/22.
//

#include "DFAVar.h"

DFAVar::DFAVar() {
    this->varName = NULL;
    this->varType = NULL;
    this->varValue = NULL;
}

DFAVar::~DFAVar() {
    if (this->varName != NULL) {
        delete(this->varName);
        this->varName = NULL;
    }
    if (this->varType != NULL) {
        delete(this->varType);
        this->varType = NULL;
    }
    if (this->varValue != NULL) {
        delete(this->varValue);
        this->varValue = NULL;
    }
}

void DFAVar::setVarName(const string & varName) {
    this->varName = new string(varName);
}

void DFAVar::setVarType(const string& varType) {
    this->varType = new string(varType);
}

void DFAVar::setVarValue(const string& varValue) {
    this->varValue = new string(varValue);
}

string* DFAVar::getVarName() {
    return this->varName;
}

string* DFAVar::getVarType() {
    return this->varType;
}

string* DFAVar::getVarValue() {
    return this->varValue;
}

