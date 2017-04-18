//
// Created by chenkuan on 2017/4/18.
//

#include "State.h"

bool State::setVarInitValue(std::string name, int value) {
	var_value[name] = value;
	return true;
}