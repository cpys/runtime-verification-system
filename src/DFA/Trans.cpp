//
// Created by yingzi on 2017/5/9.
//

#include "Trans.h"

bool Trans::addTran(int state_from, Tran tran) {
    this->trans[state_from].push_back(tran);
    return true;
}