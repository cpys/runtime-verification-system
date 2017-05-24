//
// Created by yingzi on 2017/5/22.
//

#ifndef RUNTIME_VERIFICATION_SYSTEM_DFASTATE_H
#define RUNTIME_VERIFICATION_SYSTEM_DFASTATE_H

#include <string>
#include <map>
#include "../../DFAInterface/State.h"
#include "../../DFAInterface/Var.h"
using namespace std;

class DFAState : public State {
public:
    DFAState();
    ~DFAState();

    void initStateNum(int);
    void addVar(Var*);
    void addTran(int, const string&);

    int getStateNum() const;
    Var* getVar(const string&);

    int getNextState();

    string toString();

private:
    int stateNum;   // 状态的编号
    map<string, Var*> vars; // 状态里的变量集
    map<int, string*> trans;    // 状态里的转移条件集，目的状态编号：转移条件

    bool checkCondition(string*);   // 检查表达式是否正确
};


#endif //RUNTIME_VERIFICATION_SYSTEM_DFASTATE_H
