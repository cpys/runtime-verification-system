//
// Created by chenkuan on 17-5-29.
//

#include <DFASpec.h>

void DFASpec::addTempWord(const string & tempWord) {
    this->tempWord = tempWord;
}

void DFASpec::addExpr(expr & exp) {
    this->exps.push_back(exp);
}

const vector<expr> &DFASpec::getExps() const {
    return this->exps;
}