//
// Created by chenkuan on 17-5-29.
//

#ifndef RUNTIME_VERIFICATION_SYSTEM_DFAMODULE_H
#define RUNTIME_VERIFICATION_SYSTEM_DFAMODULE_H



#include "../rvsDFAInterface/Module.h"
#include "../rvsDFAInterface/State.h"
#include "../rvsDFAInterface/Tran.h"
#include "../rvsDFAInterface/Spec.h"

#include "../../api/c++/z3++.h"
#include "../rvsDFAInterface/Event.h"

using namespace z3;

class DFAModule : public Module {

public:
    DFAModule();
    ~DFAModule();

    void addVarDecl(const string&, const string&);
    void addState(int, const vector<string>&);
    void addTran(const string&, int, int, const string&);
    void addSpec(const string&, const string&);
    void addEvent(const string&, map<string, string>&);
    void check();

private:
    map<string, string> varsDecl;   // 所有变量声明，变量名：类型
    map<int, State*> states;    // 所有状态的声明，编号：状态
    map<string, Tran*> trans;   // 所有转移的声明，转移名：转移
    vector<Spec*> specs;    // 所有判定逻辑的声明
    vector<Event*> events;  // 所有事件的声明

    context ctx;    // 检查状态转移的z3上下文
};


#endif //RUNTIME_VERIFICATION_SYSTEM_DFAMODULE_H
