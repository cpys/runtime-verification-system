//
// Created by chenkuan on 2017/4/18.
//

#ifndef RUNTIME_VERIFICATION_SYSTEM_MODULE_H
#define RUNTIME_VERIFICATION_SYSTEM_MODULE_H

#include <vector>
#include <fstream>
#include <string>
#include "Vars.h"
#include "State.h"
#include "Trans.h"
#include "Spec.h"

class Module {
private:
	std::string module_name;
	char *filename;

	Vars vars;  // 变量集
	State state0;   // 初始状态
	Trans trans;    // 转移关系
	Spec spec;  // LTL

	std::vector<State> state_path;    // 状态路径
	//std::set<State> states;     // 状态集合
public:
	bool readSMVFromFile();

	bool generateStates();  // 生成状态路径，直到状态重复

	bool setFile(char *filename);

	std::vector<State> getStatePath();
};


#endif //RUNTIME_VERIFICATION_SYSTEM_MODULE_H
