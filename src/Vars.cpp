//
// Created by chenkuan on 2017/4/18.
//

#include "Vars.h"

bool Vars::setVarRange(std::string var_name, int min, int max) {
	vars_name.insert(var_name);
	vars_range[var_name] = {min, max};
	return true;
}