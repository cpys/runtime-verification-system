//
// Created by chenkuan on 2017/4/18.
//

#include "Spec.h"

bool Spec::addSpec(std::string name, std::string oper, int value) {
	if (oper == "=") {
		var_range[name] = {value, value};
	} else if (oper == "<") {
		var_range[name] = {INT_MIN, value - 1};
	} else if (oper == ">") {
		var_range[name] = {value + 1, INT_MAX};
	} else var_range[name] = {INT_MIN, INT_MAX};
	return true;
}

bool Spec::negate(int min, int max) {
	// TODO
}