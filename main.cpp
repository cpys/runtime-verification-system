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

	Module module();
	module().setFile(argv[1]);
	module().readSMVFromFile();
	module().generateStates();


}