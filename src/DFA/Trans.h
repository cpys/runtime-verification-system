//
// Created by yingzi on 2017/5/9.
//

/*
 * 转移集，记录所有转移关系
 */

#ifndef RUNTIME_VERIFICATION_SYSTEM_TRANS_H
#define RUNTIME_VERIFICATION_SYSTEM_TRANS_H

#include <vector>
#include <map>
#include "Tran.h"

class Trans {
private:
    std::map<int, std::vector<Tran> > trans;    // 状态编号对应的转移列表

public:
    bool addTran(Tran& tran);    // 向转移集中添加一条转移

};


#endif //RUNTIME_VERIFICATION_SYSTEM_TRANS_H
