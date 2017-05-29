//
// Created by chenkuan on 17-5-29.
//

#include <iostream>
#include "DFAModule.h"
#include "DFAState.h"
#include "DFATran.h"
#include "DFASpec.h"
#include "DFAEvent.h"

using std::cout;
using std::endl;

DFAModule::~DFAModule() {
    for (auto& state : this->states) {
        if (state.second != nullptr) {
            delete(state.second);
            state.second = nullptr;
        }
    }
    for (auto& tran : this->trans) {
        if (tran.second != nullptr) {
            delete(tran.second);
            tran.second = nullptr;
        }
    }
}

void DFAModule::addVarDecl(const string &varType, const string &varName) {
    this->varsDecl[varName] = varType;
}

void DFAModule::addState(int stateNum, const vector<string> &stateConstraints) {
    State* state = this->states[stateNum];
    if (state != nullptr) {
        delete(state);
    }

    // 构造一个状态类对象
    state = new DFAState();
    state->setStateNum(stateNum);
    for (auto& stateConstraint : stateConstraints) {
        // 将状态的约束字符串解析成expr，添加到状态中expr集合中
        expr exp = this->extractExpr(stateConstraint);
        state->addExpr(exp);
    }

    // 将状态添加到模型中
    this->states[stateNum] = state;
}

void DFAModule::addTran(const string &tranName, int sourceStateNum, int destStateNum,
                        const vector<string> &tranConstraints) {
    // 取出源状态编号对应的状态
    State* state = this->states[sourceStateNum];
    if (state == nullptr) {
        // TODO
        cout << "不存在源状态" << sourceStateNum << endl;
        return;
    }

    // 构造一个转移类对象
    Tran* tran = new DFATran();
    tran->setName(tranName);
    tran->setSourceStateNum(sourceStateNum);
    tran->setDestStateNum(destStateNum);
    // 将转移约束字符串解析成expr,添加到转移中expr集合中
    for (auto& tranConstraint : tranConstraints) {
        expr exp = this->extractExpr(tranConstraint);
        tran->addExpr(exp);
    }

    // 将构造完的转移类添加到源state和module中
    state->addTran(tran);
    this->trans[tranName] = tran;
}

void DFAModule::addSpec(const string &tempWord, const string &tempConstraint) {
    // 构造一个Spec类对象
    Spec* spec = new DFASpec();
    spec->addTempWord(tempWord);
    // 将判定逻辑的约束字符串解析成expr,添加到Spec对象的expr集合中
    expr exp = this->extractExpr(tempConstraint);
    spec->addExpr(exp);

    // 将Spec类对象添加到module中
    this->specs.push_back(spec);
}

void DFAModule::addEvent(const string &eventName, map<string, string> &vars) {
    // 构造一个Event类对象
    Event* event = new DFAEvent();
    event->setEventName(eventName);

    for (auto& var : vars) {
        string varType = varsDecl[var.first];
        if (varType == "") {
            // TODO
            cout << "没有变量" << var.first << endl;
            return;
        }
        // 根据变量类型将变量值转换成expr添加到Event类对象中
        if (varType == "int") {
            expr exp_var = this->ctx.int_const(var.first.c_str());
            expr exp = exp_var == stoi(var.second);
            event->addExpr(exp);
        }
        else if (varType == "real") {
            expr exp_var = this->ctx.real_const(var.first.c_str());
            expr exp = exp_var == stod(var.second);
            event->addExpr(exp);
        }
        else {
            // TODO
            cout << "变量类型" << varType << "不支持" << endl;
            continue;
        }

    }

    // 每次添加事件时进行check
    this->check();

    this->events.push_back(event);
}

void DFAModule::check() {
    // TODO
    // 每次添加新事件时调用check
}

expr DFAModule::extractExpr(const string &constraint) {
    // TODO
    // 对字符串约束进行解析，提取出expr返回
    expr exp = this->ctx.int_const("haha");
    return exp;
}
