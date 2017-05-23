//
// Created by yingzi on 2017/5/22.
//

#include "headers/DFASpec.h"

DFASpec::DFASpec() {
    this->tempWord = NULL;
    this->content = NULL;
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
}

void DFASpec::setTempWord(const string & tempWord) {
    this->tempWord = new string(tempWord);
}

void DFASpec::setContent(const string & spec) {
    this->content = new string(spec);
}

string* DFASpec::getTempWord() const {
    return this->tempWord;
}

string* DFASpec::getContent() const {
    return this->content;
}