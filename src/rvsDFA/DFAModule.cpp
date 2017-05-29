//
// Created by chenkuan on 17-5-29.
//

#include <iostream>
#include "DFAModule.h"
#include "DFAState.h"
#include "DFATran.h"
#include "DFASpec.h"
#include "../rvsDFAInterface/Event.h"
#include "DFAEvent.h"

using std::cout;
using std::endl;

DFAModule::DFAModule() {}

DFAModule::~DFAModule() {
    for (auto& state : this->states) {
        if (state.second != NULL) {
            delete(state.second);
            state.second = NULL;
        }
    }
    for (auto& tran : this->trans) {
        if (tran.second != NULL) {
            delete(tran.second);
            tran.second = NULL;
        }
    }
}

void DFAModule::addVarDecl(const string & varType, const string & varName) {
    this->varsDecl[varName] = varType;
}

void DFAModule::addState(int stateNum, const vector<string> & stateConstraints) {
    State* state = this->states[stateNum];
    if (state != NULL) {
        delete(state);
    }

    state = new DFAState();
    state->setStateNum(stateNum);
    for (auto& stateConstraint : stateConstraints) {
        // TODO
        // 将状态的约束字符串解析成expr，添加到状态中expr集合中
    }
}

void DFAModule::addTran(const string& tranName, int sourceStateNum, int destStateNum, const string & tranConstraint) {
    // 取出源状态编号对应的状态
    State* state = this->states[sourceStateNum];
    if (state == NULL) {
        // TODO
        cout << "不存在源状态" << sourceStateNum << endl;
        return;
    }

    // 构造一个转移类对象
    Tran* tran = new DFATran();
    tran->setName(tranName);
    tran->setSourceStateNum(sourceStateNum);
    tran->setDestStateNum(destStateNum);
    // TODO
    // 将转移约束字符串解析成expr,添加到转移中expr集合中

    // 将构造完的转移类添加到源state和module中
    state->addTran(tran);
    this->trans[tranName] = tran;
}

void DFAModule::addSpec(const string & tempWord, const string & tempConstraint) {
    // 构造一个Spec类对象
    Spec* spec = new DFASpec();
    spec->addTempWord(tempWord);
    // TODO
    // 将判定逻辑的约束字符串解析成expr,添加到Spec对象的expr集合中

    this->specs.push_back(spec);
}

void DFAModule::addEvent(const string & eventName, map<string, string>& varsValue) {
    // 构造一个Event类对象
    Event* event = new DFAEvent();
    event->setEventName(eventName);

    for (auto& varValue : varsValue) {
        string varType = varsDecl[varValue.first];
        if (varType == "") {
            // TODO
            cout << "没有变量" << varValue.first << endl;
            return;
        }
        // TODO
        // 根据变量类型将变量值转换成expr添加到Event类对象中
    }

    // 每次添加事件时进行check
    this->check();

    this->events.push_back(event);
}

void DFAModule::check() {
    // TODO
    // 每次添加新事件时调用check
}