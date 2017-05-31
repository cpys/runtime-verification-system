//
// Created by chenkuan on 17-5-29.
//

#include <DFAEvent.h>

void DFAEvent::setEventName(const string & eventName) {
    this->eventName = eventName;
}

void DFAEvent::addExpr(expr & exp) {
    this->exps.push_back(exp);
}

const string &DFAEvent::getEventName() const {
    return eventName;
}

const vector<expr> &DFAEvent::getExps() const {
    return this->exps;
}
