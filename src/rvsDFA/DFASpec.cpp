//
// Created by chenkuan on 17-5-29.
//

#include <DFASpec.h>

void DFASpec::addTempWord(const string & tempWord) {
    this->tempWord = tempWord;
}

void DFASpec::addConstraint(const string &constraint) {
    this->constraints.push_back(constraint);
}

void DFASpec::addExpr(expr & exp) {
    this->exps.push_back(exp);
}

const vector<expr> &DFASpec::getExps() const {
    return this->exps;
}

const string &DFASpec::getTempWord() const {
    return this->tempWord;
}

const vector<string> &DFASpec::getConstraints() const {
    return this->constraints;
}

const string DFASpec::toString() const {
    string ans = this->tempWord;
    ans.push_back(' ');
    for (auto& constraint : this->constraints) {
        ans.append(constraint);
        ans.push_back(' ');
    }
    return ans;
}