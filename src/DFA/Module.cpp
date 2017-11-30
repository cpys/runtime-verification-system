//
// Created by yingzi on 2017/11/30.
//

#include <iostream>
#include "Module.h"

using std::cerr;
using std::endl;

Module::~Module() {
    for (auto &kv : states) {
        delete(kv.second);
    }
    for (auto &tran : trans) {
        delete(tran);
    }
    for (auto &spec : specs) {
        delete(spec);
    }
}

void Module::addVarDecl(const string &varType, const string &varName) {
    this->varsDecl[varName] = varType;
}

void Module::addStartState(int stateNum, const vector<string> &stateExprStrList) {
    this->addState(stateNum, stateExprStrList);
    this->states[stateNum]->setStartFlag();
    this->currentState = this->states[stateNum];
}

void Module::addEndState(int stateNum, const vector<string> &stateExprStrList) {
    this->addState(stateNum, stateExprStrList);
    this->states[stateNum]->setEndFlag();
}

void Module::addState(int stateNum, const vector<string> &stateExprStrList) {
    State *oldState = this->states[stateNum];
    if (oldState != nullptr && !oldState->isEmpty()) {
        cerr << "已经添加过编号为" << stateNum << "的节点，将覆盖旧节点" << endl;
    }

    // 新建状态机节点，将编号和解析成Z3的表达式添加进节点
    State *newState = oldState;
    newState->setStateNum(stateNum);
    newState->clearZ3Expr();
    for (auto &stateExpStr : stateExprStrList) {
        Z3Expr z3Expr = this->extractZ3Expr(stateExpStr);
        newState->addZ3Expr(z3Expr);
    }

    // 记录此状态到模型中
    this->states[stateNum] = newState;
}

void Module::addTran(const string &tranName, int sourceStateNum, int destStateNum) {
    // 如果源节点和目标节点尚不存在，则先创建相应状态节点
    State *sourceState = this->states[sourceStateNum];
    if (sourceState == nullptr) {
        sourceState = new State();
    }

    State *destState = this->states[destStateNum];
    if (destState == nullptr) {
        destState = new State();
    }

    // 创建Tran类，添加相应属性
    Tran *tran = new Tran();
    tran->setTranName(tranName);
    tran->setSourceState(sourceState);
    tran->setDestState(destState);

    // 将Tran类对象添加到源State和模型中
    sourceState->addTran(tran);
    this->trans.push_back(tran);
}

void Module::addSpec(const string &specStr) {
    // 构造一个Spec类对象
    Spec *spec = new Spec();
    // TODO 解析

    // 将Spec类对象添加到模型中
    this->specs.push_back(spec);
}

bool Module::addEvent(const string &eventName, const map<string, string> &varValueMap) {
    return true;
}
