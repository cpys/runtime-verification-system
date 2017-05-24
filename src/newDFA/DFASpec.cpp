//
// Created by yingzi on 2017/5/22.
//

#include <regex>
#include <iostream>
#include "headers/DFASpec.h"
#include "headers/DFAVar.h"

DFASpec::DFASpec() {
    this->tempWord = NULL;
    this->content = NULL;
    this->varName = NULL;
    this->varOperator = NULL;
    this->varValue = NULL;
}

DFASpec::~DFASpec() {
    if (this->tempWord != NULL) {
        delete(this->tempWord);
        this->tempWord = NULL;
    }
    if (this->content != NULL) {
        delete(this->content);
        this->content = NULL;
    }
    if (this->varName != NULL) {
        delete(this->varName);
        this->varName = NULL;
    }
    if (this->varOperator != NULL) {
        delete(this->varOperator);
        this->varOperator = NULL;
    }
    if (this->varValue != NULL) {
        delete(this->varValue);
        this->varValue = NULL;
    }
}

void DFASpec::setTempWord(const string & tempWord) {
    if (this->tempWord != NULL) {
        delete(this->tempWord);
    }
    this->tempWord = new string(tempWord);
}

void DFASpec::setContent(const string & content) {
    if (this->content != NULL) {
        delete(this->content);
    }
    this->content = new string(content);
    this->updateContentInfo();
}

string* DFASpec::getTempWord() const {
    return this->tempWord;
}

string* DFASpec::getContent() const {
    return this->content;
}

bool DFASpec::verifyState(State* state) {
    // TODO
    // 先把状态中对应的变量取出
    DFAVar* var = dynamic_cast<DFAVar*>(state->getVar(*this->varName));

    // 再根据判定逻辑右边的值定义新的变量
    DFAVar* rVar = new DFAVar();
    string varType = *var->getVarType();
    rVar->setVarType(varType);
    rVar->setVarValue(*this->varValue);

    bool flag;
    // 然后根据关系运算符进行判断
    if (*this->varOperator == "==") flag =  (*var == *rVar);
    else if (*this->varOperator == "!=") flag = (*var != *rVar);
    else if (*this->varOperator == "<") flag = (*var < *rVar);
    else if (*this->varOperator == "<=") flag = (*var <= *rVar);
    else if (*this->varOperator == ">") flag = (*var > *rVar);
    else if (*this->varOperator == ">=") flag = (*var >= *rVar);
    else {
        // TODO
        cout << "运算符\"" << *this->varOperator << "\"不合法" << endl;
        flag = false;
    }

    return flag;
}

void DFASpec::updateContentInfo() {
    // 当前要求验证逻辑如以下形式
    // 变量名 关系运算符 变量值
    regex re("[[:space:]]*([a-zA-Z_][a-zA-Z0-9_]*)[[:space:]]*(==|!=|<|<=|>|>=)[[:space:]]*([[:digit:]]+|[[:digit:]]*.[[:digit:]]+)[[:space:]]*");
    smatch sm;
    regex_match(*this->content, sm, re);

    if (this->varName != NULL) {
        delete(this->varName);
    }
    this->varName = new string(sm[1]);

    if (this->varOperator != NULL) {
        delete(this->varOperator);
    }
    this->varOperator = new string(sm[2]);

    if (this->varValue != NULL) {
        delete(this->varValue);
    }
    this->varValue = new string(sm[3]);
}

string DFASpec::toString() {
    ostringstream oss;
    oss << *this->tempWord << "(" << *this->content << ")";
    return oss.str();
}