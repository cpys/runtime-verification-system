//
// Created by chenkuan on 2017/4/18.
//

#include <iostream>
#include "Module.h"
#include <z3++.h>

using namespace z3;

void demorgan() {
	std::cout << "de-Morgan example\n";

	context c;

	expr x = c.bool_const("x");
	expr y = c.bool_const("y");
	expr conjecture = (!(x && y)) == (!x || !y);

	solver s(c);
	// adding the negation of the conjecture as a constraint.
	s.add(!conjecture);
	std::cout << s << "\n";
	std::cout << s.to_smt2() << "\n";
	switch (s.check()) {
		case unsat:
			std::cout << "de-Morgan is valid\n";
			break;
		case sat:
			std::cout << "de-Morgan is not valid\n";
			break;
		case unknown:
			std::cout << "unknown\n";
			break;
	}
}

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

	demorgan();

	return 0;
}