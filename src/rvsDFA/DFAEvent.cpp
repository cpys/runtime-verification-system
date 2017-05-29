//
// Created by chenkuan on 17-5-29.
//

#include "DFAEvent.h"

DFAEvent::DFAEvent() {

}

DFAEvent::~DFAEvent() {

}

void DFAEvent::setEventName(const string & eventName) {
    this->eventName = eventName;
}

void DFAEvent::addExpr(expr & exp) {
    this->exps.insert(exp);
}