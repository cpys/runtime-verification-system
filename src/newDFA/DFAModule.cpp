//
// Created by yingzi on 2017/5/22.
//

#include <regex>
#include <iostream>
#include "DFAModule.h"
#include "DFAVar.h"
#include "DFAState.h"
#include "DFASpec.h"

DFAModule::DFAModule() {
    this->stateStartNum = -1;
}

DFAModule::~DFAModule() {
    for (auto& var : this->vars) {
        if (var.second != NULL) {
            delete (var.second);
            var.second = NULL;
        }
    }
    this->vars.clear();

    for (auto& state : this->states) {
        if (state.second != NULL) {
            delete (state.second);
            state.second = NULL;
        }
    }
    this->states.clear();

    for (auto& spec : this->specs) {
        if (spec != NULL) {
            delete (spec);
            spec = NULL;
        }
    }
    this->specs.clear();
}

void DFAModule::initVarType(const map<string, string>& varTypes) {
    for (auto& varType : varTypes) {
        Var* var = new DFAVar();
        var->setVarName(varType.first);
        var->setVarType(varType.second);
        this->vars[varType.first] = var;
    }
}

void DFAModule::addState(int stateNum, vector<Var*> vars) {
    State* state = new DFAState();
    state->initStateNum(stateNum);
    for (auto& var : vars) {
        state->addVar(var);
    }
    this->states[stateNum] = state;
}

void DFAModule::addTran(int sourceStateNum, int targetStateNum, const string& tranCondition) {
    State* state = this->states[sourceStateNum];
    if (state == NULL) return;
    state->addTran(targetStateNum, tranCondition);
}

void DFAModule::addSpec(const string& tempWord, const string& content) {
    Spec* spec = new DFASpec();
    spec->setTempWord(tempWord);
    spec->setContent(content);

    this->specs.push_back(spec);
}

void DFAModule::setStartStateNum(int startStateNum) {
    this->stateStartNum = startStateNum;
}

State* DFAModule::getState(int stateNum) {
    return this->states[stateNum];
}

void DFAModule::execute() {
    // 初始化所有结点标识为未访问过
    this->stateFlag.clear();
    for (auto& state : this->states) {
        this->stateFlag[state.first] = false;
    }

    // 将起始状态结点标识为已访问
    if (this->stateFlag.find(this->stateStartNum) != this->stateFlag.end()) {
        this->stateFlag[this->stateStartNum] = true;
    }

    // 只要未到达结束状态就继续运行
    int stateNum = this->stateStartNum;
    while (stateNum != this->stateTailNum) {
        // 获取当前状态
        State* state = this->states[stateNum];
        if (state == NULL) {
            // TODO
            // 无法获取当前状态
            return;
        }

        // 访问当前状态
        cout << "this is state " << stateNum << ", " << state->toString() << endl;
        // 标识被访问的状态为已访问
        this->stateFlag[stateNum] = true;

        // 获取下面可以到达的状态
        int nextStateNum = state->getNextState();
        if (nextStateNum < 0) {
            // TODO
            // 无下一个状态
            break;
        }
        else if (this->stateFlag[nextStateNum]) {
            // TODO
            // 下一个状态已经访问过了
            break;
        }
        stateNum = nextStateNum;
    }
}