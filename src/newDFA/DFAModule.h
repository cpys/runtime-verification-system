//
// Created by yingzi on 2017/5/22.
//

#ifndef RUNTIME_VERIFICATION_SYSTEM_DFAMODULE_H
#define RUNTIME_VERIFICATION_SYSTEM_DFAMODULE_H

#include <string>
#include <map>
#include "../DFAInterface/Module.h"
using namespace std;

class DFAModule : Module{
public:
    void initVarType(const map<string, string>&);

private:
    DFAVar vars;
};


#endif //RUNTIME_VERIFICATION_SYSTEM_DFAMODULE_H
