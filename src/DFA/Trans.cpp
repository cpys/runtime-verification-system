//
// Created by yingzi on 2017/5/9.
//

#include <iostream>
#include "Trans.h"

bool Trans::addTran(Tran& tran) {
    std::cout << "添加转移条件, 从结点" << tran.getStateFrom() << "到结点" << tran.getStateTo() << ": " << tran.getCondition() << std::endl;
    this->trans[tran.getStateFrom()].push_back(tran);
    return true;
}