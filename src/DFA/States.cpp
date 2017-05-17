//
// Created by yingzi on 2017/5/9.
//

#include <iostream>
#include "States.h"

States::States(){
    this->next_state_num = 1;
}

int States::addState(State state) {
    if (this->states_num.find(state) != this->states_num.end()) {
        return this->states_num[state];
    }

    std::cout << "添加状态" << this->next_state_num << ":" << state.getStateString() << std::endl;
    this->states[this->next_state_num] = state;
    this->states_num[state] = this->next_state_num;
    this->next_state_num++;

    return this->next_state_num - 1;
}

int States::getStateNum(State &state) {
    return this->addState(state);
}

State States::getState(int state_num) {
    return this->states[state_num];
}