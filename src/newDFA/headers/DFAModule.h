//
// Created by yingzi on 2017/5/22.
//

#ifndef RUNTIME_VERIFICATION_SYSTEM_DFAMODULE_H
#define RUNTIME_VERIFICATION_SYSTEM_DFAMODULE_H

#include <string>
#include <map>
#include <vector>
#include "../../DFAInterface/Module.h"
#include "../../DFAInterface/Var.h"
#include "../../DFAInterface/State.h"
#include "../../DFAInterface/Spec.h"
using namespace std;

class DFAModule : public Module{
public:
    DFAModule();
    ~DFAModule();

    void initVarType(const map<string, string>&);
    void addVarType(const string&, const string&);
    void addState(int, const vector<Var*>&);
    void addTran(int, int, const string&);
    void addSpec(const string&, const string&);

    void setStartStateNum(int);

    State* getState(int);

    void execute();

private:
    map<string, Var*> vars; // 所有变量的声明，名称：变量
    map<int, State*> states;    // 所有状态的声明，编号：状态
    vector<Spec*> specs;    // 所有验证逻辑的声明

    int stateStartNum;  // 起始状态编号
    int stateTailNum;   // 结束状态编号

    map<int, bool> stateFlag;   // 标识状态的访问

    /*
     * 对单条验证逻辑进行验证
     * @param 验证逻辑
     */
    void verifySpec(Spec*);
};


#endif //RUNTIME_VERIFICATION_SYSTEM_DFAMODULE_H
