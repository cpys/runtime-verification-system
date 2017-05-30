//
// Created by chenkuan on 17-5-29.
//

#include "DFATran.h"

DFATran::DFATran() {
}

DFATran::~DFATran() {

}

void DFATran::setName(const string & tranName) {
    this->tranName = tranName;
}

void DFATran::setSourceState(State *state) {
    this->sourceState = state;
}

void DFATran::setDestState(State *state) {
    this->destState = state;
}

void DFATran::addExpr(expr & exp) {
    this->exps.insert(exp);
}

const string DFATran::getName() const {
    return this->tranName;
}

State *DFATran::getSourceState() const {
    return this->sourceState;
}

State *DFATran::getDestState() const {
    return this->destState;
}

int DFATran::getSourceStateNum() const {
    if (this->sourceState == nullptr) return -1;
    return this->sourceState->getStateNum();
}

int DFATran::getDestStateNum() const {
    if (this->destState == nullptr) return -1;
    return this->sourceState->getStateNum();
}

set<expr> DFATran::getExps() const {
    return this->exps;
}

bool DFATran::checkEvent(Event *event, solver &slv) {
    // 检查给定事件后该转移是否符合
    if (event->getEventName() != this->tranName) return false;

    slv.reset();
    // 先添加源状态的表达式集
    for (auto& exp : this->sourceState->getExps()) {
        slv.add(exp);
    }
    // 再添加转移上的表达式集
    for (auto& exp : this->exps) {
        slv.add(exp);
    }
    // 最后添加事件上的表达式集
    for (auto& exp : event->getExps()) {
        slv.add(exp);
    }

    return slv.check() == z3::sat;
}
