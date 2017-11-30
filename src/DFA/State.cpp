//
// Created by yingzi on 2017/11/30.
//

#include "State.h"

void State::setStateNum(int stateNum) {
    this->stateNum = stateNum;
    this->emptyFlag = false;
}

void State::setStartFlag() {
    this->startFlag = true;
}

void State::setEndFlag() {
    this->endFlag = true;
}

void State::addZ3Expr(const Z3Expr &z3Expr) {
    z3ExprList.push_back(z3Expr);
}

void State::addTran(const Tran *tran) {
    outTranList.push_back(tran);
}

bool State::isEmpty() {
    return emptyFlag;
}

int State::getStateNum() {
    return stateNum;
}

bool State::isStartState() {
    return startFlag;
}

bool State::isEndState() {
    return endFlag;
}

const vector<const Z3Expr> &State::getZ3ExprList() {
    return z3ExprList;
}

const vector<const Tran *> &State::getTranList() {
    return outTranList;
}

void State::clear() {
    this->emptyFlag = true;
    startFlag = false;
    endFlag = false;
    z3ExprList.clear();
    outTranList.clear();
}
