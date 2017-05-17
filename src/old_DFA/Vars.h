//
// Created by chenkuan on 2017/4/18.
//

#ifndef RUNTIME_VERIFICATION_SYSTEM_VARS_H
#define RUNTIME_VERIFICATION_SYSTEM_VARS_H


#include <utility>
#include <string>
#include <map>
#include <set>

class Vars {
private:
	std::set<std::string> vars_name;
	std::map<std::string, std::pair<int, int>> vars_range;
public:
	bool setVarRange(std::string, int, int);
};


#endif //RUNTIME_VERIFICATION_SYSTEM_VARS_H
