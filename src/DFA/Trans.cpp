//
// Created by yingzi on 2017/5/9.
//

#include "Trans.h"

bool Trans::addTran(Tran& tran) {
    this->trans[tran.getStateFrom()].push_back(tran);
    return true;
}