//
// Created by yingzi on 2017/11/30.
//

#include <iostream>
#include <stack>
#include "Module.h"

using std::cout;
using std::cerr;
using std::endl;
using std::stack;

Module::~Module() {
    for (auto &kv : states) {
        delete(kv.second);
    }
    for (auto &tran : trans) {
        delete(tran);
    }
}

void Module::addVarDecl(const string &varType, const string &varName) {
    this->varsDecl[varName] = varType;
}

void Module::addStartState(int stateNum, const vector<string> &stateExprStrList) {
    this->addState(stateNum, stateExprStrList);
    this->states[stateNum]->setStartFlag();
    this->currentState = this->states[stateNum];
}

void Module::addEndState(int stateNum, const vector<string> &stateExprStrList) {
    this->addState(stateNum, stateExprStrList);
    this->states[stateNum]->setEndFlag();
}

void Module::addState(int stateNum, const vector<string> &stateExprStrList) {
    State *oldState = this->states[stateNum];
    if (oldState == nullptr) {
        oldState = new State();
    }
    else if (!oldState->isEmpty()) {
        cerr << "已经添加过编号为" << stateNum << "的节点，将覆盖旧节点" << endl;
        oldState->clear();
    }

    // 新建状态机节点，将编号和解析成Z3的表达式添加进节点
    State *newState = oldState;
    newState->setStateNum(stateNum);
    for (auto &stateExprStr : stateExprStrList) {
        const Z3Expr z3Expr = this->extractZ3Expr(stateExprStr);
        newState->addZ3Expr(z3Expr);
    }

    // 记录或更新此状态到模型中
    this->states[stateNum] = newState;
}

void Module::addTran(const string &tranName, int sourceStateNum, int destStateNum) {
    // 如果源节点和目标节点尚不存在，则先创建相应状态节点
    State *sourceState = this->states[sourceStateNum];
    if (sourceState == nullptr) {
        sourceState = new State();
    }

    State *destState = this->states[destStateNum];
    if (destState == nullptr) {
        destState = new State();
    }

    // 创建Tran类，添加相应属性
    auto tran = new Tran();
    tran->setTranName(tranName);
    tran->setSourceState(sourceState);
    tran->setDestState(destState);

    // 将Tran类对象添加到源State和模型中
    sourceState->addTran(tran);
    this->trans.push_back(tran);
}

void Module::addSpec(const string &specStr) {
    // 生成Z3表达式添加进模型
    const Z3Expr z3Expr = this->extractZ3Expr(specStr);
    z3ExprVector.push_back(z3Expr);
}

bool Module::addEvent(const string &eventName, const map<string, string> &varValueMap) {
    // 假设不能转移
    bool result = false;
    const State *nextState = nullptr;

    // 先查看当前状态能否转移到相邻状态
    const vector<const Tran *> outTranList = currentState->getTranList();
    for (auto &tran : outTranList) {
        nextState = tran->getDestState();
        if (tran->getTranName() == eventName) {
            result = this->verify(nextState, varValueMap);
            if (result) {
                break;
            }
        }
    }

    // 如果无法转移到相邻状态或者转移到相邻状态验证失败则在全局中搜索转移
    if (!result) {
        for (auto &tran : trans) {
            nextState = tran->getDestState();
            if (tran->getSourceState() != currentState && nextState != currentState && tran->getTranName() == eventName) {
                result = this->verify(nextState, varValueMap);
                if (result) {
                    break;
                }
            }
        }
    }

    if (result) {
        cout << "事件" << eventName << "导致节点" << currentState->getStateNum() << "转移到节点" << nextState->getStateNum() << endl;
        currentState = const_cast<State *>(nextState);
        return true;
    }
    else {
        return false;
    }
}

void Module::initModule() {
    int num = 0;
    for (auto &kv : states) {
        if (kv.second->isEmpty()) {
            ++num;
        }
    }
    cerr << "模型中存在" << num << "个虚拟的空节点" << endl;

    // 初始化变量序号表达式
    for (auto &varDecl : varsDecl) {
        for (auto &state : states) {
            if (varDecl.second == "int") {
                z3VarsNumExpr[varDecl.first][state.first] = ctx.int_const((varDecl.first + std::to_string(state.first)).c_str());
            }
            else if (varDecl.second == "double") {
                z3VarsNumExpr[varDecl.first][state.first] = ctx.real_const((varDecl.first + std::to_string(state.first)).c_str());
            }
            else if (varDecl.second == "bool") {
                z3VarsNumExpr[varDecl.first][state.first] = ctx.bool_const((varDecl.first + std::to_string(state.first)).c_str());
            }
            cerr << "不支持的变量类型" << varDecl.second << endl;
        }
    }
}

const Z3Expr Module::extractZ3Expr(const string &exprStr) {
    // TODO
    // 借用运算符栈和运算数栈实现表达式的解析
    stack<string> operatorStack;
    // expr栈用来记录中间表达式结果
    stack<Z3Expr> exprStack;

    // 先压入最低优先级运算符
    operatorStack.push("$");

    // 遍历字符串表达式
    string identifier;    // 记录标识符
    string currentType;    // 记录当前类型
    for (auto &c : exprStr) {
        if (currentType.empty()) {
            // 当前无类型，即可从任意符号开始新的标识符
            if (isalpha(c) != 0 || c == '_') {
                // 当前开始一个新的变量
                currentType = "var";
                identifier.push_back(c);
            } else if (isdigit(c) != 0 || c == '.') {
                // 当前开始一个新的运算数
                currentType = "operand";
                identifier.push_back(c);
            } else if (isOperator(c)) {
                // 当前为运算符
                currentType = "operator";
                identifier.push_back(c);
            } else if (isspace(c) == 0) {
                // 其他情况必须为空格
                cerr << "非法字符" << c << endl;
            }
        } else if (currentType == "var") {
            // 当前已处于变量状态
            if (isalnum(c) != 0 || c == '_') {
                // 继续当前变量
                identifier.push_back(c);
            } else {
                // 当前为其他字符则生成完整变量

                // 根据变量名生成变量名expr
                Z3Expr exp = generateVarExp(identifier);
                exprStack.push(exp);
                identifier.clear();

                if (isspace(c) != 0) {
                    currentType = "";
                } else if (isOperator(c)) {
                    currentType = "operator";
                    identifier.push_back(c);
                } else {
                    cerr << "不合法的标识符" << identifier + c << endl;
                }
            }
        } else if (currentType == "operand") {
            // 当前已处于运算数状态
            if (isdigit(c) != 0 || c == '.') {
                // 继续当前运算数
                identifier.push_back(c);
            } else {
                // 当前为其他字符则生成完整运算数
                // 分析数的类型得到不同的expr
                Z3Expr exp = generateNumExp(identifier);
                exprStack.push(exp);
                identifier.clear();

                if (isspace(c) != 0) {
                    currentType = "";
                } else if (isOperator(c)) {
                    currentType = "operator";
                    identifier.push_back(c);
                } else {
                    cerr << "非法的标识符" << identifier + c << endl;
                }
            }
        } else if (currentType == "operator") {
            // 当前已经处于运算符状态
            if (isOperator(c)) {
                // 继续当前运算符
                identifier.push_back(c);
            } else {
                // 当前为其他字符则生成完整运算符
                // 将当前运算符与栈顶相比较
                while (!compareOperator(identifier, operatorStack.top())) {
                    // 只要当前运算符比栈顶运算符优先级低就一直退两个表达式和一个运算符进行运算后压栈
                    const string operatorTop = operatorStack.top() + "";
                    operatorStack.pop();

                    Z3Expr expr2 = exprStack.top();
                    exprStack.pop();
                    Z3Expr expr1 = exprStack.top();
                    exprStack.pop();

                    exprStack.push(calcExpr(expr1, operatorTop, expr2));
                }
                // 退出循环时表示当前运算符比栈顶运算符优先级高
                operatorStack.push(identifier);
                identifier.clear();

                if (isalpha(c) != 0 || c == '_') {
                    currentType = "var";
                    identifier.push_back(c);
                } else if (isdigit(c) != 0 || c == '.') {
                    currentType = "operand";
                    identifier.push_back(c);
                } else if (isspace(c) != 0) {
                    currentType = "";
                } else {
                    cerr << "非法字符" << c << endl;
                }
            }
        }
    }

    // 循环结束后需要手动添加结束符, 即循环退栈
    if (currentType == "var") {
        // 根据变量名生成变量名expr
        Z3Expr exp = generateVarExp(identifier);
        exprStack.push(exp);
        identifier.clear();
    } else if (currentType == "operand") {
        // 分析数的类型得到不同的expr
        Z3Expr exp = generateNumExp(identifier);
        exprStack.push(exp);
        identifier.clear();
    } else if (currentType == "operator") {
        cerr << "表达式" << exprStr << "以运算符结尾，非法！" << endl;
    }

    while (operatorStack.size() > 1) {
        string operatorTop = operatorStack.top() + "";
        operatorStack.pop();

        if (exprStack.size() < 2) {
            cerr << "运算数或变量不足，表达式" << exprStr << "不合法" << endl;
            break;
        }
        Z3Expr expr2 = exprStack.top();
        exprStack.pop();
        Z3Expr expr1 = exprStack.top();
        exprStack.pop();

        exprStack.push(calcExpr(expr1, operatorTop, expr2));
    }

    return exprStack.top();
}

bool Module::verify(const State *nextState, const map<string, string> &varValueMap) {
    slv.push();
    // 先添加下一状态中的全部Z3表达式
    const vector<Z3Expr> &stateZ3ExprList = nextState->getZ3ExprList();
    for (auto &z3Expr : stateZ3ExprList) {
        slv.add(z3Expr);
    }

    // 再将事件上的变量全部构造成Z3表达式添加进去
    int nextStateNum = nextState->getStateNum();
    for (auto &varValue : varValueMap) {
        string varType = varsDecl[varValue.first];
        if (varType.empty()) {
            cerr << "事件中出现未定义的变量" << varValue.first << endl;
            continue;
        }

        if (varType == "int") {
            slv.add(z3VarsNumExpr[varValue.first][nextStateNum] == std::stoi(varValue.second));
        }
        else if (varType == "double") {
            slv.add(z3VarsNumExpr[varValue.first][nextStateNum] == std::stod(varValue.second));
        }
        else if (varType == "bool") {
            slv.add(z3VarsNumExpr[varValue.first][nextStateNum] == (varValue.second == "true"));
        }
    }

    if (slv.check() == z3::sat) {
        return true;
    }
    else {
        slv.pop();
        return false;
    }
}

bool Module::isOperator(char c) {
    static string operatorStr = "+-*/<>!=";
    return operatorStr.find(c) != string::npos;
}
