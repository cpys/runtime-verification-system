//
// Created by yingzi on 2017/5/9.
//

/*
 * 状态集，记录所有状态，并提供状态到编号的转换
 */

#ifndef RUNTIME_VERIFICATION_SYSTEM_STATES_H
#define RUNTIME_VERIFICATION_SYSTEM_STATES_H

#include <map>
#include "State.h"

class States {
private:
    std::map<State, int> states_num;    // 状态到编号
    std::map<int, State> states;    // 编号到状态

public:
    int getStateNum(State state);   // 获取状态对应的编号，如果状态不存在则添加状态
    State getState(int state_num);  // 获取状态编号对应的状态
};


#endif //RUNTIME_VERIFICATION_SYSTEM_STATES_H
