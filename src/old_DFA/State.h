//
// Created by chenkuan on 2017/4/18.
//

#ifndef RUNTIME_VERIFICATION_SYSTEM_STATE_H
#define RUNTIME_VERIFICATION_SYSTEM_STATE_H

#include <map>
#include <string>
#include <set>
#include <iostream>

class State {
private:
	// 变量值
	std::map<std::string, int> var_value;
public:
	bool setVarInitValue(std::string, int);

	friend std::ostream &operator<<(std::ostream &os, State &state) {
		for (auto &vv : state.var_value) {
			os << vv.first << " : " << vv.second << std::endl;
		}
		return os;
	}

	std::map<std::string, int> getVarValue();

	bool setVarValue(std::map<std::string, int>);
};


#endif //RUNTIME_VERIFICATION_SYSTEM_STATE_H
