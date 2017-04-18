//
// Created by chenkuan on 2017/4/18.
//

#ifndef RUNTIME_VERIFICATION_SYSTEM_TRANS_H
#define RUNTIME_VERIFICATION_SYSTEM_TRANS_H

#include <vector>
#include <utility>
#include <string>
#include <map>

class Trans {
private:
	std::map<std::pair<std::string, int>, int> var_trans;
	std::map<std::string, int> default_trans;
public:
	bool addTrans(std::string, int, int);

	bool addDefaultTrans(std::string, int);
};


#endif //RUNTIME_VERIFICATION_SYSTEM_TRANS_H
