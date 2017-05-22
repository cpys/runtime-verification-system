//
// Created by yingzi on 2017/5/22.
//

#include "DFASpec.h"

DFASpec::DFASpec() {
    this->tempWord = NULL;
    this->content = NULL;
}

DFASpec::~DFASpec() {
    if (this->tempWord != NULL) {
        free(this->tempWord);
        this->tempWord = NULL;
    }
    if (this->content != NULL) {
        free(this->content);
        this->content = NULL;
    }
}

void DFASpec::setTempWord(const string & tempWord) {
    this->tempWord = new string(tempWord);
}

void DFASpec::setContent(const string & spec) {
    this->content = new string(spec);
}

string* DFASpec::getTempWord() {
    return this->tempWord;
}

string* DFASpec::getContent() {
    return this->content;
}