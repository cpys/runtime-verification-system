//
// Created by yingzi on 2017/5/9.
//

#include "Tran.h"

Tran::Tran(int state_from, int state_to) {
    this->state_from = state_from;
    this->state_to = state_to;
}

bool Tran::addCondition(std::string condition) {
    this->condition = condition;
    return true;
}

int Tran::getStateFrom() {
    return this->state_from;
}

int Tran::getStateTo() {
    return this->state_to;
}