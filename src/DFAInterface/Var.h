//
// Created by yingzi on 2017/5/22.
//

#ifndef RUNTIME_VERIFICATION_SYSTEM_VAR_H
#define RUNTIME_VERIFICATION_SYSTEM_VAR_H

#include <string>
using std::string;

class Var {
public:
    Var();
    virtual ~Var();

    /*
     * 设置变量名称
     * @param 变量名称
     */
    virtual void setVarName(const string&) = 0;

    /*
     * 设置变量类型
     * @param 变量类型
     */
    virtual void setVarType(const string&) = 0;

    /*
     * 设置变量值
     * @param 变量值
     */
    virtual void setVarValue(const string&) = 0;

    /*
     * 获取变量名称
     * @return 变量名称
     */
    virtual string* getVarName() = 0;

    /*
     * 获取变量类型
     * @return 变量类型
     */
    virtual string* getVarType() = 0;

    /*
     * 获取变量值
     * @return 变量值
     */
    virtual string* getVarValue() = 0;
};

#endif //RUNTIME_VERIFICATION_SYSTEM_VAR_H
