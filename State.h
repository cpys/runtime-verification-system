//
// Created by chenkuan on 2017/4/18.
//

#ifndef RUNTIME_VERIFICATION_SYSTEM_STATE_H
#define RUNTIME_VERIFICATION_SYSTEM_STATE_H

#include <map>
#include <string>
#include <set>

class State {
private:
	std::set<std::string> var_names;
	// 变量值
	std::map<std::string, int> var_value;
	// 范围
	std::map<std::string, std::pair<int, int>> var_range;
public:
	bool setVarName(std::string);

	bool setVarRange(std::string, int, int);

	bool setVarInitValue(std::string, int);
};


#endif //RUNTIME_VERIFICATION_SYSTEM_STATE_H
