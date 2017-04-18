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