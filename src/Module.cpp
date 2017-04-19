//
// Created by chenkuan on 2017/4/18.
//

#include "Module.h"

bool Module::readSMVFromFile() {
	std::ifstream file(filename);
	std::string s;
	while (file >> s) {
		if (s == "MODULE") {
			file >> module_name;
		} else if (s == "VAR") {
			std::string var_name;
			while (file >> var_name && var_name != "VAR_END") {
				int min, max;
				file >> min >> max;
				vars.setVarRange(var_name, min, max);
			}
		} else if (s == "ASSIGN") {
			std::string init;
			while (file >> init && init != "ASSIGN_END") {
				std::string var_name;
				int value;
				file >> var_name >> value;
				state0.setVarInitValue(var_name, value);
			}
		} else if (s == "TRANS") {
			std::string var_name;
			while (file >> var_name && var_name != "TRANS_END") {
				if (var_name != "1") {
					int value0, value1;
					file >> value0 >> value1;
					trans.addTrans(var_name, value0, value1);
				} else {
					int value;
					file >> var_name >> value;
					trans.addDefaultTrans(var_name, value);
				}
			}
		} else if (s == "LTLSPEC") {
			std::string var_name;
			while (file >> var_name && var_name != "LTLSPEC_END") {
				std::string oper;
				int value;
				file >> oper >> value;
				spec.addSpec(var_name, oper, value);
			}
		}
	}
}

bool Module::generateStates() {
	State state = state0;
	//while (states.find(state) != states.end()) {
	for (int i = 0; i < 10; i++) {
		// 将新状态添加
		state_path.push_back(state);
		//states.insert(state);

		// 开始转移
		trans.getNextState(state);
	}
	return true;
}

bool Module::setFile(char *filename) {
	this->filename = filename;
}

std::vector<State> Module::getStatePath() {
	return state_path;
}