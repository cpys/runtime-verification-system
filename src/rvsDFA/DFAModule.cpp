//
// Created by chenkuan on 17-5-29.
//

#include <iostream>
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
}

expr DFAModule::extractExpr(const string &constraint) {
    // TODO
    // 对字符串约束进行解析，提取出expr返回
    expr exp;
    return exp;
}

void DFAModule::trace(Event *event) {
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
            return;
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
                break;
            }
        }
    }

    cout << "事件" << eventName << "无法找到合适的转移" << endl;
}