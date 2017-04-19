//
// Created by chenkuan on 2017/4/18.
//

#include "Trans.h"

bool Trans::addTrans(std::string name, int value0, int value1) {
	var_trans[{name, value0}] = value1;
	return true;
}

bool Trans::addDefaultTrans(std::string name, int value) {
	default_trans[name] = value;
	return true;
}

bool Trans::getNextState(State &state) {
	std::map<std::string, int> var_value = state.getVarValue();
	for (auto &vv : var_value) {
		if (var_trans.find({vv.first, vv.second}) != var_trans.end()) {
			vv.second = var_trans[{vv.first, vv.second}];
		} else if (default_trans.find(vv.first) != default_trans.end()) {
			vv.second = default_trans[vv.first];
		}
	}
	state.setVarValue(var_value);
	return true;
}