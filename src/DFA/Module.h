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
#include "Tran.h"

using std::string;
using std::vector;
using std::map;
using z3::context;
using z3::solver;
using Z3Expr = z3::expr;
using Z3ExprVector = z3::expr_vector;

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

    /**
     * 初始化模型，进行虚拟空节点检查
     * 初始化变量序号表达式
     */
    void initModule();

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
    Z3ExprVector z3ExprVector;

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
    /**
     * 所有的变量序号对应的Z3表达式
     * 变量名称:(变量序号：Z3表达式)
     */
    map<string, map<int, Z3Expr> > z3VarsNumExpr;

    /**
     * 将字符串形式的表达式转成Z3表达式
     * 提取出的变量需要分离出变量名称和序号来获取预定的Z3表达式
     * @param exprStr 字符串表达式
     * @return
     */
    const Z3Expr extractZ3Expr(const string &exprStr);
    /**
     * 验证待定的下一个状态和事件上的变量能否通过验证
     * 验证成功则保留新加入的Z3表达式
     * 验证失败则删除新加入的Z3表达式
     * @param nextState 待定的下一个状态
     * @param varValueMap 事件上的变量名：变量值 映射表
     * @return 验证结果
     */
    bool verify(const State *nextState, const map<string, string> &varValueMap);
    /**
     * 判断字符是否为合法运算符号
     * @param c 运算符号
     * @return 是否合法
     */
    bool isOperator(char c);
};


#endif //RUNTIME_VERIFICATION_SYSTEM_MODULE_H
