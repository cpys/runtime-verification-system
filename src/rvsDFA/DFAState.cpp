//
// Created by chenkuan on 17-5-29.
//

#include "DFAState.h"

DFAState::DFAState() {
}

DFAState::~DFAState() {
}

void DFAState::setStateNum(int stateNum) {
    this->stateNum = stateNum;
}

void DFAState::addExpr(expr & exp) {
    this->exps.insert(exp);
}

void DFAState::addTran(Tran * tran) {
    this->trans.push_back(tran);
}