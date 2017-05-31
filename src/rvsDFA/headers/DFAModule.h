//
// Created by chenkuan on 17-5-29.
//

#ifndef RUNTIME_VERIFICATION_SYSTEM_DFAMODULE_H
#define RUNTIME_VERIFICATION_SYSTEM_DFAMODULE_H

#include <Module.h>
#include <State.h>
#include <Tran.h>
#include <Spec.h>
#include <Event.h>
#include <c++/z3++.h>

using namespace z3;

class DFAModule : public Module {

public:
    DFAModule();
    ~DFAModule() override;

    void addVarDecl(const string &varType, const string &varName) override;
    void addState(int stateNum, const vector<string> &stateConstraints) override ;
    void addTran(const string &tranName, int sourceStateName, int destStateNum, const vector<string> &tranConstraints) override ;
    void addSpec(const string &tempWord, const vector<string> &tempConstraints) override ;
    void addEvent(const string &eventName, const map<string, string> &vars) override;
    void check() override ;

private:
    map<string, string> varsDecl;   // 所有变量声明，变量名：类型
    map<int, State*> states;    // 所有状态的声明，编号：状态
    map<string, Tran*> trans;   // 所有转移的声明，转移名：转移
    vector<Spec*> specs;    // 所有判定逻辑的声明
    vector<Event*> events;  // 所有事件的声明

    context ctx;    // 检查状态转移的z3上下文
    solver slv; // 检查状态转移的z3求解器

    map<Spec*, bool> specValidity;  // 所有判定逻辑的正确性

    int currentStateNum;    // 模型执行过程中当前状态编号
    vector <int> stateNums; // 事件加入过程中产生的新状态编号，可能为0,1,2个

    /*
     * 对字符串约束进行解析，提取出expr返回
     * @param 字符串表示的约束
     * @return expr
     */
    expr extractExpr(const string& constraint);

    /*
     * 对添加的事件进行状态转移选择
     * @param 事件指针
     * @return 新加入的状态编号
     */
    void trace(Event* event);
};


#endif //RUNTIME_VERIFICATION_SYSTEM_DFAMODULE_H
