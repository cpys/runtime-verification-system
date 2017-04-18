//
// Created by chenkuan on 2017/4/18.
//

#ifndef RUNTIME_VERIFICATION_SYSTEM_MODULE_H
#define RUNTIME_VERIFICATION_SYSTEM_MODULE_H

#include <set>
#include <fstream>
#include <string>
#include "State.h"
#include "Trans.h"
#include "Spec.h"

class Module {
private:
	std::string module_name;
	char *filename;
	State state0;   // 初始状态
	std::set<State> states;    // 状态路径
	Trans trans;
	Spec spec;
public:
	bool readSMVFromFile();

	bool generateStates();  // 生成状态路径，直到状态重复

	bool setFile(char *filename);
};


#endif //RUNTIME_VERIFICATION_SYSTEM_MODULE_H
