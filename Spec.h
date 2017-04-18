//
// Created by chenkuan on 2017/4/18.
//

#ifndef RUNTIME_VERIFICATION_SYSTEM_SPEC_H
#define RUNTIME_VERIFICATION_SYSTEM_SPEC_H


#include <utility>
#include <string>
#include <map>
#include <climits>

class Spec {
private:
	std::map<std::string, std::pair<int, int>> var_range;
public:
	bool addSpec(std::string, std::string, int);

	bool negate(int, int);  // 在限定的范围内取反
};


#endif //RUNTIME_VERIFICATION_SYSTEM_SPEC_H
