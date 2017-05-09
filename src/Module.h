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

	int depth;
public:
	explicit Module(int depth = 10);	// 默认构造函数

	bool readSMVFromFile();

	bool generateStates();  // 生成状态路径，直到状态重复

	bool setFile(char *);

	std::vector<State> getStatePath();

	void setBmcDepth(int);	// 设置状态搜索树最大深度
};


#endif //RUNTIME_VERIFICATION_SYSTEM_MODULE_H
