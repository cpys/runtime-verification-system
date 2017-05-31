//
// Created by chenkuan on 17-5-29.
//

#include <iostream>
#include <regex>
#include <DFAModule.h>
#include <DFAState.h>
#include <DFATran.h>
#include <DFASpec.h>
#include <DFAEvent.h>

using std::cout;
using std::endl;
using std::cerr;

DFAModule::DFAModule() : slv(ctx) {
    this->currentStateNum = -1;
}

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
    for (auto& spec : this->specs) {
        if (spec != nullptr) {
            delete(spec);
            spec = nullptr;
        }
    }
    for (auto& event : this->events) {
        if (event != nullptr) {
            delete(event);
            event = nullptr;
        }
    }
    slv.reset();
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
    State* sourceState = this->states[sourceStateNum];
    if (sourceState == nullptr) {
        // TODO
        cerr << "不存在源状态" << sourceStateNum << endl;
        return;
    }

    State* destState = this->states[destStateNum];
    if (destState == nullptr) {
        // TODO
        cerr << "不存在目标状态" << destStateNum << endl;
    }

    // 构造一个转移类对象
    Tran* tran = new DFATran();
    tran->setName(tranName);
    tran->setSourceState(sourceState);
    tran->setDestState(destState);
    // 将转移约束字符串解析成expr,添加到转移中expr集合中
    for (auto& tranConstraint : tranConstraints) {
        expr exp = this->extractExpr(tranConstraint);
        tran->addExpr(exp);
    }

    // 将构造完的转移类添加到源state和module中
    sourceState->addTran(tran);
    this->trans[tranName] = tran;
}

void DFAModule::addSpec(const string &tempWord, const vector<string> &tempConstraints) {
    // 构造一个Spec类对象
    Spec* spec = new DFASpec();
    spec->addTempWord(tempWord);
    // 将判定逻辑的约束字符串解析成expr,添加到Spec对象的expr集合中
    for (auto& constraint : tempConstraints) {
        spec->addConstraint(constraint);
        expr exp = this->extractExpr(constraint);
        spec->addExpr(exp);
    }

    // 将Spec类对象添加到module中
    this->specs.push_back(spec);
    // 根据Spec时序词的不同，给其正确性赋相应初值
    if (tempWord == "G") {
        this->specValidity[spec] = true;
    }
    else if (tempWord == "A") {
        this->specValidity[spec] = false;
    }
    else {
        // TODO
        cerr << "不合法的时序词" << tempWord << endl;
    }
}

void DFAModule::addEvent(const string &eventName, const map<string, string> &vars) {
    // 构造一个Event类对象
    Event* event = new DFAEvent();
    event->setEventName(eventName);

    for (auto& var : vars) {
        string varType = varsDecl[var.first];
        if (varType == "") {
            // TODO
            cerr << "没有变量" << var.first << endl;
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
            cerr << "变量类型" << varType << "不支持" << endl;
            continue;
        }

    }

    // 每次添加事件时进行轨迹描绘
    this->trace(event);

    // 每次添加事件时对spec进行check
    this->check();

    this->events.push_back(event);
}

void DFAModule::check() {
    // TODO
    // 每次添加新事件时调用check
    for (auto& spec : this->specs) {
        // 跳过已成功验证过的逻辑
        if (spec->getTempWord() == "A" && this->specValidity[spec] == true) continue;
        if (spec->getTempWord() == "G" && this->specValidity[spec] == false) continue;

        this->slv.reset();
        // 先添加spec的表达式
        for (auto& exp : spec->getExps()) {
            this->slv.add(exp);
        }
        // 再添加状态中的表达式
        for (auto& stateNum : this->stateNums) {
            for (auto& exp : this->states[stateNum]->getExps()) {
                this->slv.add(exp);
            }
        }

        z3::check_result  result = slv.check();
        if (result == z3::sat && spec->getTempWord() == "A") {
            // TODO
            cout << "验证逻辑" << spec->toString() << "通过验证" << endl;
            this->specValidity[spec] = true;
        }
        if (result == z3::unsat && spec->getTempWord() == "G") {
            // TODO
            cout << "验证逻辑" << spec->toString() << "验证失败" << endl;
            this->specValidity[spec] = false;
        }
    }

}

expr DFAModule::extractExpr(const string &constraint) {
    // TODO
    // 对字符串约束进行解析，提取出expr返回
    // 暂时要求条件表达式满足如下形式
    // 变量名 关系运算符 变量值
    std::regex re("[[:space:]]*([a-zA-Z_][a-zA-Z0-9_]*)[[:space:]]*(==|!=|<|<=|>|>=)[[:space:]]*([[:digit:]]+|[[:digit:]]*.[[:digit:]]+)[[:space:]]*");
    std::smatch sm; // 存储匹配结果
    regex_match(constraint, sm, re);
    if (sm.size() != 4) {
        // TODO
        cerr << "表达式暂不支持" << endl;
        return this->ctx.int_const("wrong");
    }

    // 先根据表达式中的变量获取其类型，然后生成对应的初始化表达式
    string varName = sm[1];
    string oper = sm[2];
    string valueStr = sm[3];

    string varType = this->varsDecl[varName];
    if (varType == "int") {
        expr exp = this->ctx.int_const(varName.c_str());
        int value = stoi(valueStr);
        if (oper == "==") return exp == value;
        if (oper == "!=") return exp != value;
        if (oper == "<") return exp < value;
        if (oper == "<=") return exp <= value;
        if (oper == ">") return exp > value;
        if (oper == ">=") return exp >= value;

        // TODO
        cerr << "不支持的运算符" << oper << endl;
    }
    else if (varType == "real") {
        expr exp = this->ctx.real_const(varName.c_str());
        double value = stod(valueStr);
        if (oper == "==") return exp == value;
        if (oper == "!=") return exp != value;
        if (oper == "<") return exp < value;
        if (oper == "<=") return exp <= value;
        if (oper == ">") return exp > value;
        if (oper == ">=") return exp >= value;

        // TODO
        cerr << "不支持的运算符" << oper << endl;
    }

    return this->ctx.int_const("wrong");
}

void DFAModule::trace(Event *event) {
    this->stateNums = {};
    // 如果当前有状态，则优先从此状态出发判断
    if (this->currentStateNum >= 0) {
        State* currentState = this->states[this->currentStateNum];
        if (currentState == nullptr) {
            // TODO
            cerr << "找不到当前 状态" << this->currentStateNum << endl;
            return;
        }
        // 判断当前状态是否能转移到下一状态
        int nextState = currentState->getNextState(event, this->slv);
        if (nextState >= 0) {
            // TODO
            cout << "事件" << event->getEventName() << "将当前状态" << this->currentStateNum << "转移到了状态" << nextState << endl;
            this->currentStateNum = nextState;
            this->stateNums = {this->currentStateNum, nextState};
            return ;
        }
    }

    // 当前无状态或者当前有状态却无法转移到下一状态，则从所有转移中搜索
    string eventName = event->getEventName();
    for (auto& tranMap : this->trans) {
        // 首先要事件名匹配
        if (tranMap.first == eventName) {
            // 然后判断该转移的源状态是否能经由该转移和该事件转移到下一状态
            Tran* currentTran = tranMap.second;
            bool couldTran = currentTran->checkEvent(event, this->slv);
            if (couldTran) {
                cout << "事件" << eventName << "产生了从状态" << currentTran->getSourceStateNum() << "到状态" << currentTran->getDestStateNum() << "的转移" << endl;
                this->currentStateNum = currentTran->getDestStateNum();
                this->stateNums = {currentTran->getSourceStateNum(), currentTran->getDestStateNum()};
                return;
            }
        }
    }

    cout << "事件" << eventName << "无法找到合适的转移" << endl;
}