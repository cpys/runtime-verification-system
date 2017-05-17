//
// Created by chenkuan on 2017/4/18.
//

#include "State.h"

bool State::setVarInitValue(std::string name, int value) {
	var_value[name] = value;
	return true;
}

std::map<std::string, int> State::getVarValue() {
	return var_value;
}

bool State::setVarValue(std::map<std::string, int> var_value) {
	this->var_value = var_value;
	return true;
}