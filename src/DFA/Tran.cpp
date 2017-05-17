//
// Created by yingzi on 2017/5/9.
//

#include "Tran.h"

Tran::Tran() {
    this->state_from = this->state_to = 0;
}

Tran::Tran(const int& state_from, const int& state_to) {
    this->state_from = state_from;
    this->state_to = state_to;
}

bool Tran::addCondition(const std::string& condition) {
    this->condition = condition;
    return true;
}

int Tran::getStateFrom() {
    return this->state_from;
}

int Tran::getStateTo() {
    return this->state_to;
}

std::string Tran::getCondition() {
    return this->condition;
}