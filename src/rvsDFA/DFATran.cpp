//
// Created by chenkuan on 17-5-29.
//

#include "DFATran.h"

DFATran::DFATran() {

}

DFATran::~DFATran() {

}

void DFATran::setName(const string & tranName) {
    this->tranName = tranName;
}

void DFATran::setSourceStateNum(int sourceStateNum) {
    this->sourceStateNum = sourceStateNum;
}

void DFATran::setDestStateNum(int destStateNum) {
    this->destStateNum = destStateNum;
}

void DFATran::addExpr(expr & exp) {
    this->exps.insert(exp);
}