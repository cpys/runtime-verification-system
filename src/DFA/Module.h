//
// Created by yingzi on 2017/11/30.
//

#ifndef RUNTIME_VERIFICATION_SYSTEM_MODULE_H
#define RUNTIME_VERIFICATION_SYSTEM_MODULE_H

#include <string>
#include <vector>
#include <map>
#include <z3++.h>
#include "State.h"
#include "Spec.h"
#include "Tran.h"

using std::string;
using std::vector;
using std::map;
using z3::context;
using z3::solver;
using Z3Expr = z3::expr;

class Module {
  public:
    Module() = default;
    ~Module();
    /**
     * 添加变量声明
     * @param varType 变量类型
     * @param varName 变量名称
     */
    void addVarDecl(const string &varType, const string &varName);
    /**
     * 添加起始状态节点定义
     * @param stateNum 起始状态节点编号
     * @param stateExprStrList 状态节点上的字符串表达式列表
     */
    void addStartState(int stateNum, const vector<string> &stateExprStrList);
    /**
     * 添加终止状态节点定义
     * @param stateNum 终止状态节点编号
     * @param stateExprStrList 状态节点上的字符串表达式列表
     */
    void addEndState(int stateNum, const vector<string> &stateExprStrList);
    /**
     * 添加状态节点定义
     * @param stateNum 状态节点编号
     * @param stateExprStrList 状态节点上的字符串表达式列表
     */
    void addState(int stateNum, const vector<string> &stateExprStrList);
    /**
     * 添加状态节点转移定义
     * @param tranName 转移名称
     * @param sourceStateNum 源节点
     * @param destStateNum 目的节点
     */
    void addTran(const string &tranName, int sourceStateNum, int destStateNum);
    /**
     * 添加一条轨迹验证约束
     * @param specStr 约束的字符串表达式
     */
    void addSpec(const string &specStr);
    /**
     * 添加事件，返回事件验证结果
     * @param eventName 事件名称
     * @param varValueMap 变量名:变量值 映射表
     * @return 事件验证结果
     */
    bool addEvent(const string &eventName, const map<string, string> &varValueMap);

  private:
    /**
     * 所有变量声明，变量名：类型
     */
    map<string, string> varsDecl;
    /**
     * 状态节点自身编号与实际状态结构映射表
     */
    map<int, State *> states;
    /**
     * 所有的转移
     */
    vector<Tran *> trans;
    /**
     * 所有的判定逻辑
     */
    vector<Spec *> specs;

    /**
     * 当前状态节点
     */
    State *currentState = nullptr;
    /**
     * 状态节点轨迹
     */
    vector<State *> stateTrace;

    /**
     * Z3求解器的上下文
     */
    context ctx;
    /**
     * Z3求解器
     */
    solver slv{ctx};
};


#endif //RUNTIME_VERIFICATION_SYSTEM_MODULE_H
