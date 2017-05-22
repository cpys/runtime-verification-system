//
// Created by yingzi on 2017/5/22.
//

#include <regex>
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

}