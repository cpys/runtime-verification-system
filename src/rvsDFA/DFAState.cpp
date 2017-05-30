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

int DFAState::getNextState(Event *event, solver &slv) {
    // 遍历此状态出发的转移关系，依次判断是否符合
    for (auto& tran : this->trans) {
        if (tran->getName() != event->getEventName()) continue;

        slv.reset();
        // 先添加状态内的expr
        for (auto& exp : this->exps) {
            slv.add(exp);
        }
        // 再添加转移内的expr
        for (auto& exp : tran->getExps()) {
            slv.add(exp);
        }
        // 再添加事件内的expr
        for (auto& exp : event->getExps()) {
            slv.add(exp);
        }
        if (slv.check() == z3::sat) {
            return tran->getDestStateNum();
        }
    }
    return -1;
}

set<expr> DFAState::getExps() const {
    return this->exps;
}
