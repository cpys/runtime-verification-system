//
// Created by yingzi on 2017/5/9.
//

/*
 * 记录所有变量并进行编号
 */

#ifndef RUNTIME_VERIFICATION_SYSTEM_VARS_H
#define RUNTIME_VERIFICATION_SYSTEM_VARS_H


class Vars {
private:
    std::map<std::string, int> vars_num;    // 名称到编号
    std::vector<std::string> vars_name; // 编号到名称

public:
    int getVarNum(std::string var_name);    // 获取变量名称对应的编号，如果变量不存在则添加变量
    std::string getVarName(int var_num);    // 获取变量编号对应的名称，如果编号不存在返回""
};


#endif //RUNTIME_VERIFICATION_SYSTEM_VARS_H
