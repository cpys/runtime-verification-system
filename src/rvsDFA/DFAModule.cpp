//
// Created by chenkuan on 17-5-29.
//

#include <iostream>
#include <regex>
#include <stack>
#include <cctype>
#include <DFAModule.h>
#include <DFAState.h>
#include <DFATran.h>
#include <DFASpec.h>
#include <DFAEvent.h>

using std::cout;
using std::endl;
using std::cerr;
using std::stack;

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
            expr exp = (exp_var == this->ctx.int_val(var.second.c_str())); // stoi(var.second);
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
    // 借用运算符栈和运算数栈实现表达式的解析
    stack<string> operatorStack;
    // expr栈用来记录中间表达式结果
    stack<expr> exprStack;

    // 先压入最低优先级运算符
    operatorStack.push("$");

    // 遍历字符串表达式
    string identifier;    // 记录标识符
    string flag;    // 记录当前类型
    for (auto& c : constraint) {
        if (flag == "") {
            // 当前无类型，即可从任意符号开始新的标识符
            if (isalpha(c) != 0 || c == '_') {
                // 当前开始一个新的变量
                flag = "var";
                identifier.push_back(c);
            }
            else if (isdigit(c) != 0 || c == '.') {
                // 当前开始一个新的运算数
                flag = "operand";
                identifier.push_back(c);
            }
            else if (isOperator(c)) {
                // 当前为运算符
                flag = "operator";
                identifier.push_back(c);
            }
            else if (isspace(c) == 0) {
                // 其他情况必须为空格
                cerr << "非法字符" << c << endl;
            }
        }
        else if (flag == "var") {
            // 当前已处于变量状态
            if (isalnum(c) != 0 || c == '_') {
                // 继续当前变量
                identifier.push_back(c);
            }
            else  {
                // 当前为其他字符则生成完整变量

                // 根据变量名生成变量名expr
                expr exp = generateVarExp(identifier);
                exprStack.push(exp);
                identifier.clear();

                if (isspace(c) != 0) {
                    flag = "";
                }
                else if (isOperator(c)){
                    flag = "operator";
                    identifier.push_back(c);
                }
                else {
                    cerr << "不合法的标识符" << identifier + c << endl;
                }
            }
        }
        else if (flag == "operand") {
            // 当前已处于运算数状态
            if (isdigit(c) != 0 || c == '.') {
                // 继续当前运算数
                identifier.push_back(c);
            }
            else {
                // 当前为其他字符则生成完整运算数
                // 分析数的类型得到不同的expr
                expr exp = generateNumExp(identifier);
                exprStack.push(exp);
                identifier.clear();

                if (isspace(c) != 0) {
                    flag = "";
                }
                else if (isOperator(c)) {
                    flag = "operator";
                    identifier.push_back(c);
                }
                else {
                    cerr << "非法的标识符" << identifier + c << endl;
                }
            }
        }
        else if (flag == "operator") {
            // 当前已经处于运算符状态
            if (isOperator(c)) {
                // 继续当前运算符
                identifier.push_back(c);
            }
            else {
                // 当前为其他字符则生成完整运算符
                // 将当前运算符与栈顶相比较
                while (!compareOperator(identifier, operatorStack.top())) {
                    // 只要当前运算符比栈顶运算符优先级低就一直退两个表达式和一个运算符进行运算后压栈
                    const string& operatorTop = operatorStack.top();
                    operatorStack.pop();

                    expr expr2 = exprStack.top();
                    exprStack.pop();
                    expr expr1 = exprStack.top();
                    exprStack.pop();

                    exprStack.push(calcExpr(expr1, operatorTop, expr2));
                }
                // 退出循环时表示当前运算符比栈顶运算符优先级高
                operatorStack.push(identifier);
                identifier.clear();

                if (isalpha(c) != 0 || c == '_') {
                    flag = "var";
                    identifier.push_back(c);
                }
                else if (isdigit(c) != 0 || c == '.') {
                    flag = "operand";
                    identifier.push_back(c);
                }
                else if (isspace(c) != 0) {
                    flag = "";
                }
                else {
                    cerr << "非法字符" << c << endl;
                }
            }
        }
    }

    // 循环结束后需要手动添加结束符, 即循环退栈
    if (flag == "var") {
        // 根据变量名生成变量名expr
        expr exp = generateVarExp(identifier);
        exprStack.push(exp);
        identifier.clear();
    }
    else if (flag == "operand") {
        // 分析数的类型得到不同的expr
        expr exp = generateNumExp(identifier);
        exprStack.push(exp);
        identifier.clear();
    }
    else if (flag == "operator") {
        cerr << "表达式" << constraint << "以运算符结尾，非法！" << endl;
    }

    while (operatorStack.size() > 1) {
        const string &operatorTop = operatorStack.top();
        operatorStack.pop();

        if (exprStack.size() < 2) {
            cerr << "运算数或变量不足，表达式" << constraint << "不合法" << endl;
            break;
        }
        expr expr2 = exprStack.top();
        exprStack.pop();
        expr expr1 = exprStack.top();
        exprStack.pop();

        exprStack.push(calcExpr(expr1, operatorTop, expr2));
    }

    return exprStack.top();
}

//expr DFAModule::extractExpr(const string &constraint) {
//    // TODO
//    // 对字符串约束进行解析，提取出expr返回
//    // 暂时要求条件表达式满足如下形式
//    // 变量名 关系运算符 变量值
//    std::regex re("[[:space:]]*([a-zA-Z_][a-zA-Z0-9_]*)[[:space:]]*(==|!=|<|<=|>|>=)[[:space:]]*([[:digit:]]+|[[:digit:]]*.[[:digit:]]+)[[:space:]]*");
//    std::smatch sm; // 存储匹配结果
//    regex_match(constraint, sm, re);
//    if (sm.size() != 4) {
//        // TODO
//        cerr << "表达式暂不支持" << endl;
//        return this->ctx.int_const("wrong");
//    }
//
//    // 先根据表达式中的变量获取其类型，然后生成对应的初始化表达式
//    string varName = sm[1];
//    string oper = sm[2];
//    string valueStr = sm[3];
//
//    string varType = this->varsDecl[varName];
//    if (varType == "int") {
//        expr exp = this->ctx.int_const(varName.c_str());
//        int value = stoi(valueStr);
//        if (oper == "==") return exp == value;
//        if (oper == "!=") return exp != value;
//        if (oper == "<") return exp < value;
//        if (oper == "<=") return exp <= value;
//        if (oper == ">") return exp > value;
//        if (oper == ">=") return exp >= value;
//
//        // TODO
//        cerr << "不支持的运算符" << oper << endl;
//    }
//    else if (varType == "real") {
//        expr exp = this->ctx.real_const(varName.c_str());
//        double value = stod(valueStr);
//        if (oper == "==") return exp == value;
//        if (oper == "!=") return exp != value;
//        if (oper == "<") return exp < value;
//        if (oper == "<=") return exp <= value;
//        if (oper == ">") return exp > value;
//        if (oper == ">=") return exp >= value;
//
//        // TODO
//        cerr << "不支持的运算符" << oper << endl;
//    }
//
//    return this->ctx.int_const("wrong");
//}

void DFAModule::trace(Event *event) {
    this->stateNums.clear();
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

bool DFAModule::isOperator(const char &c) {
    string operatorStr = "+-*/<>!=";
    return operatorStr.find(c) != string::npos;
}

expr DFAModule::generateVarExp(const string &varName) {
    if (this->varsDecl.find(varName) == this->varsDecl.end()) {
        cerr << "未声明的变量" << varName << endl;
    }
    string varType = this->varsDecl[varName];
    if (varType == "int") {
        return this->ctx.int_const(varName.c_str());
    }
    else if (varType == "double") {
        return this->ctx.real_const(varName.c_str());
    }
    else {
        cerr << "变量" << varName << "类型" << varType << "不支持" <<endl;
        return this->ctx.string_val(varName);
    }
}

expr DFAModule::generateNumExp(const string &operand) {
    if (operand.find('.') >= 0) return this->ctx.real_val(operand.c_str());
    else return this->ctx.int_val(operand.c_str());
}

bool DFAModule::compareOperator(const string &operator1, const string &operator2) {
    map<string, int> operatorPriority = {
            {"$", 0},
            {"==", 1},
            {"!=", 1},
            {"<", 2},
            {"<=", 2},
            {">", 2},
            {">=", 2},
            {"+", 3},
            {"-", 3},
            {"*", 4},
            {"/", 4}
    };
    if (operatorPriority.find(operator1) == operatorPriority.end()) {
        cerr << "运算符" << operator1 << "不支持" << endl;
        return false;
    }
    if (operatorPriority.find(operator2) == operatorPriority.end()) {
        cerr << "运算符" << operator2 << "不支持" << endl;
        return false;
    }
    return operatorPriority[operator1] > operatorPriority[operator2];
}

expr DFAModule::calcExpr(expr &expr1, const string &currentOperator, expr &expr2) {
    if (currentOperator == "==") return expr1 == expr2;
    if (currentOperator == "!=") return expr1 != expr2;
    if (currentOperator == "<") return expr1 < expr2;
    if (currentOperator == "<=") return expr1 <= expr2;
    if (currentOperator == ">") return expr1 > expr2;
    if (currentOperator == ">=") return expr1 >= expr2;
    if (currentOperator == "+") return expr1 + expr2;
    if (currentOperator == "-") return expr1 - expr2;
    if (currentOperator == "*") return expr1 * expr2;
    if (currentOperator == "/") return expr1 / expr2;
    else {
        cerr << "不支持的运算符" << currentOperator << endl;
        return expr1;
    }
}