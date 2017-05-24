//
// Created by yingzi on 2017/5/22.
//

#include "headers/DFASpec.h"

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

void DFASpec::setContent(const string & spec) {
    if (this->content != NULL) {
        delete(this->content);
    }
    this->content = new string(spec);

}

string* DFASpec::getTempWord() const {
    return this->tempWord;
}

string* DFASpec::getContent() const {
    return this->content;
}

bool DFASpec::verifyState(const State* state) {
    // TODO
}