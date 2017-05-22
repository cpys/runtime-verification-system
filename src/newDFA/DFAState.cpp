//
// Created by yingzi on 2017/5/22.
//

#include <regex>
#include "DFAState.h"

DFAState::DFAState() {
    this->stateNum = -1;
}

DFAState::~DFAState() {
    for (auto& var : this->vars) {
        if (var.second != NULL) {
            delete(var.second);
            var.second = NULL;
        }
    }
    this->vars.clear();

    for (auto& tran : this->trans) {
        if (tran.second != NULL) {
            delete(tran.second);
            tran.second = NULL;
        }
    }
    this->trans.clear();
}

void DFAState::initStateNum(int stateNum) {
    this->stateNum = stateNum;
}

void DFAState::addVar(Var* var) {
    string* varName = var->getVarName();
    if (varName != NULL) {
        this->vars[*varName] = var;
    }
}

void DFAState::addTran(int targetStateNum, const string& tranCondition) {
    this->trans[targetStateNum] = new string(tranCondition);
}

vector<int> DFAState::getNextState() {
    vector<int> nextStates;
    for (auto& tran : this->trans) {
        string* condition = tran.second;

        // TODO
    }
}