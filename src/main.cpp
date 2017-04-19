//
// Created by chenkuan on 2017/4/18.
//

#include <iostream>
#include "Module.h"

int main(int argc, char **argv) {
	if (argc != 2) {
		std::cout << "useage: " << argv[0] << " filename" << std::endl;
		return 1;
	}

	Module module;
	module.setFile(argv[1]);
	module.readSMVFromFile();
	module.generateStates();

	std::vector<State> state_path = module.getStatePath();
	for (int i = 0; i < state_path.size(); i++) {
		std::cout << "------------state " << i << "----------" << std::endl;
		std::cout << state_path[i] << std::ends;
	}

	return 0;
}