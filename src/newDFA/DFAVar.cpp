//
// Created by yingzi on 2017/5/22.
//

#include <iostream>
#include "headers/DFAVar.h"

DFAVar::DFAVar() {
    this->varName = NULL;
    this->varType = NULL;
//    this->varValue = NULL;
}

DFAVar::DFAVar(const string& varName, const string& varType, const string& varValue) {
    this->varName = new string(varName);
    this->varType = new string(varType);
    this->varValueString = varValue;

    this->updateVarTypeValue();
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
//    if (this->varValue != NULL) {
//        delete(this->varValue);
//        this->varValue = NULL;
//    }
}

void DFAVar::setVarName(const string & varName) {
    if (this->varName != NULL) {
        delete(this->varName);
    }
    this->varName = new string(varName);
}

void DFAVar::setVarType(const string& varType) {
    if (this->varType != NULL) {
        delete(this->varType);
    }
    this->varType = new string(varType);
}

void DFAVar::setVarValue(const string& varValue) {
    this->varValueString = varValue;
//    this->varValue = new string(varValue);
    this->updateVarTypeValue();
}

string* DFAVar::getVarName() const {
    return this->varName;
}

string* DFAVar::getVarType() const {
    return this->varType;
}

int DFAVar::getVarValueInt() const {
    return this->varValueInt;
}

double DFAVar::getVarValueDouble() const {
    return this->varValueDouble;
}

string DFAVar::getVarValueString() const {
    return this->varValueString;
}

//string* DFAVar::getVarValue() const {
//    return this->varValue;
//}

bool DFAVar::updateVarTypeValue() {
    if (*this->varType == "int") {
        this->varValueInt = stoi(this->varValueString);
    }
    else if (*this->varType == "double") {
        this->varValueDouble = stod(this->varValueString);
    }
    else if (*this->varType != "string") {
        // TODO
        cout << "类型\"" << *this->varType << "\"不合法" << endl;
        return false;
    }

    return true;
}