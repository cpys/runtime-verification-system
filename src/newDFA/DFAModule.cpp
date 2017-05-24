//
// Created by yingzi on 2017/5/22.
//

#include <regex>
#include <iostream>
#include "headers/DFAModule.h"
#include "headers/DFAVar.h"
#include "headers/DFAState.h"
#include "headers/DFASpec.h"

DFAModule::DFAModule() {
    this->stateStartNum = -1;
    this->stateTailNum = -1;
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

void DFAModule::addVarType(const string& varName, const string& varType) {
    Var* var = new DFAVar();
    var->setVarName(varName);
    var->setVarType(varType);
    this->vars[varName] = var;
}

void DFAModule::addState(int stateNum, const vector<Var*>& vars) {
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
    cout << "开始执行模型" << endl;

    // 依次验证待验证逻辑
    for (auto& spec : this->specs) {

        string tempWord = *spec->getTempWord();
        string content = *spec->getContent();
        bool specValid;
        if (tempWord == "G") {
            // 时序词为所有状态满足时, specValid默认为true
            specValid = true;
        }
        else if (tempWord == "A") {
            // 时序词为存在状态满足时，specValid默认为false
            specValid = false;
        }
        else cout << "时序词\"" << tempWord << "\"不合法" << endl;

        // 初始化所有结点标识为未访问过
        this->stateFlag.clear();
        for (auto &state : this->states) {
            this->stateFlag[state.first] = false;
        }

        // 只要未到达结束状态就继续运行
        int stateNum = this->stateStartNum;
        while (stateNum != this->stateTailNum) {
            // 获取当前状态
            State *state = this->states[stateNum];
            if (state == NULL) {
                // TODO
                cout << "状态" << stateNum << "不存在" << endl;
                return;
            }

            // 访问当前状态
            cout << state->toString() << endl;
            // 标识被访问的状态为已访问
            this->stateFlag[stateNum] = true;

            // 判断状态是否满足spec要求
            // TODO

            // 获取下面可以到达的状态
            int nextStateNum = state->getNextState();
            if (nextStateNum < 0) {
                // TODO
                cout << "无后续状态" << endl;
                break;
            } else if (this->stateFlag[nextStateNum]) {
                // TODO
                cout << "下一状态" << nextStateNum << "已访问过，结束执行" << endl;
                break;
            }
            stateNum = nextStateNum;
        }

        if (stateNum == this->stateTailNum) {
            cout << "到达终止状态" << stateNum << endl;
        }
    }

    cout << "模型执行结束" << endl;
}