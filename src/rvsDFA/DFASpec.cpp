//
// Created by chenkuan on 17-5-29.
//

#include "DFASpec.h"

DFASpec::DFASpec() {

}

DFASpec::~DFASpec() {

}

void DFASpec::addTempWord(const string & tempWord) {
    this->tempWord = tempWord;
}

void DFASpec::addExpr(expr & exp) {
    this->exps.insert(exp);
}