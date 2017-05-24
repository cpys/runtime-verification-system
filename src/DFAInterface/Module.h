//
// Created by yingzi on 2017/5/22.
//

#ifndef RUNTIME_VERIFICATION_SYSTEM_MODULE_H
#define RUNTIME_VERIFICATION_SYSTEM_MODULE_H

#include <string>
#include <map>
#include <vector>
#include "Var.h"
#include "State.h"
using std::string;
using std::map;
using std::vector;

class Module {

public:
    Module() = default;
    virtual ~Module() = default;

    /*
     * 初始化变量类型
     * @param <变量名，变量类型>表
     * 变量类型声明格式："变量名:变量类型"
     * 变量类型可取值："int","double","string"
     */
    virtual void initVarType(const map<string, string>&) = 0;

    /*
     * 添加一个变量类型
     * @param 变量名，变量类型
     * 变量类型可取值："int","double","string"
     */
    virtual void addVarType(const string&, const string&) = 0;

    /*
     * 添加一个状态
     * @param 状态编号，变量列表
     */
    virtual void addState(int, const vector<Var*>&) = 0;

    /*
     * 添加一个转移关系
     * @param 源状态编号，目标状态编号，转移条件
     */
    virtual void addTran(int, int, const string&) = 0;

    /*
     * 添加判定逻辑
     * @param 时序词，验证内容
     */
    virtual void addSpec(const string&, const string&) = 0;

    /*
     * 设置起点状态
     * @param 起点状态编号
     */
    virtual void setStartStateNum(int) = 0;

    /*
     * 设置终止状态
     * @param 终止状态编号
     */
    virtual void setTailStateNum(int) = 0;

    /*
     * 根据状态编号获取状态
     * @param 状态编号
     * @return 状态
     */
    virtual State* getState(int) = 0;

    /*
     * 执行模型中的判定逻辑
     */
    virtual void execute() = 0;


};


#endif //RUNTIME_VERIFICATION_SYSTEM_MODULE_H
