//
// Created by chenkuan on 17-5-29.
//

#include "DFAState.h"

DFAState::DFAState() {
    this->stateNum = -1;
}

DFAState::~DFAState() {
    for (auto& tran : this->trans) {
        if (tran != nullptr) {
            delete(tran);
            tran = nullptr;
        }
    }
}

void DFAState::setStateNum(int stateNum) {
    this->stateNum = stateNum;
}

void DFAState::addExpr(expr &exp) {
    this->exps.insert(exp);
}

void DFAState::addTran(Tran *tran) {
    this->trans.push_back(tran);
}

int DFAState::getStateNum() const {
    return this->stateNum;
}
