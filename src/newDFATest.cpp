//
// Created by yingzi on 2017/5/22.
//

#include <iostream>
#include "newDFA/headers/DFAModule.h"
#include "newDFA/headers/DFAVar.h"

using namespace std;

int main() {
    Module* module = new DFAModule();

    module->addVarType("m_a_int", "int");
    module->addVarType("m_b_double", "double");
    module->addVarType("m_c_string", "string");

    // 添加状态1
    Var* var1_s1 = new DFAVar("m_a_int", "int",  "123");
    Var* var2_s1 = new DFAVar("m_b_double", "double", "456.78");
    vector <Var*> vars_s1 {var1_s1, var2_s1};
    module->addState(1, vars_s1);

    // 添加状态2
    Var* var1_s2 = new DFAVar("m_a_int", "int", "234");
    Var* var2_s2 = new DFAVar("m_b_double", "double", "678.9");
    vector <Var*> vars_s2 {var1_s2, var2_s2};
    module->addState(2, vars_s2);

    // 添加转移
    module->addTran(1, 2, "m_a_int > 100");

//    // 输出状态1的下一个可达状态
//    int nextStateNum = module->getState(1)->getNextState();
//    cout << "下一个状态为状态" << nextStateNum << endl;

    // 添加判定逻辑
    module->addSpec("G", "m_b_double > 400");

//    // 执行模型
    module->setStartStateNum(1);
    module->execute();

    delete(module);
    return 0;
}