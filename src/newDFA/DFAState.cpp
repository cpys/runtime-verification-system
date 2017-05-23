//
// Created by yingzi on 2017/5/22.
//

#include <regex>
#include <sstream>
#include "headers/DFAState.h"
#include "headers/DFAVar.h"

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

int DFAState::getNextState() {
    for (auto& tran : this->trans) {
        string* condition = tran.second;

        if (this->checkCondition(condition)) {
            return tran.first;
        }
    }
    return -1;
}

bool DFAState::checkCondition(string* condition) {
    // 当前要求条件表达式如以下形式
    // 变量名 关系运算符 变量值
    regex re("[[:space:]]*([a-zA-Z_][a-zA-Z0-9_]*)[[:space:]]*(==|!=|<|<=|>|>=)[[:space:]]*([[:digit:]]+|[[:digit:]]*.[[:digit:]]+)[[:space:]]*");
    smatch sm;  // 存储匹配结果
    regex_match(*condition, sm, re);
    if (sm.size() != 4) return false;

    // 先把状态中对应的变量取出
    Var* var = this->vars[sm[1]];
    if (var == NULL) {
        // 变量非法
        // TODO
        return false;
    }
    string varType = *var->getVarType();

    // 再根据条件表达式右边的值定义新的变量
    Var* rVar = new DFAVar();
    rVar->setVarType(varType);
    rVar->setVarName(sm[1]);
    rVar->setVarValue(sm[3]);

//    // 最后根据关系运算符进行判断
//    if (sm[2] == "==") return (*rVar) == (*var);
//    else if (sm[2] == "!=") return rVar != *var;
//    else if (sm[2] == "<") return rVar < *var;
//    else if (sm[2] == "<=") return rVar <= *var;
//    else if (sm[2] == ">") return rVar > *var;
//    else if (sm[2] == ">=") return rVar >= *var;
//    else {
//        // TODO
//        // 运算符非法
//    }

    return false;
}

string DFAState::toString() {
    ostringstream oss;
    oss << endl << "状态" << this->stateNum << endl;
    for (auto& s_var : this->vars) {
        oss << "变量" << s_var.first << ", ";
        oss << "类型" << s_var.second->getVarType() << ", ";
        oss << "值" << s_var.second->getVarValue() << endl;
    }
    for (auto& tran : this->trans) {
        oss << "从转移条件\"" << tran.second << "\"转移到状态" << tran.first << endl;
    }

    return oss.str();
}