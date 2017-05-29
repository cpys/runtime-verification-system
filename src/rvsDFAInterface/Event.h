//
// Created by chenkuan on 17-5-29.
//

#ifndef RUNTIME_VERIFICATION_SYSTEM_EVENT_H
#define RUNTIME_VERIFICATION_SYSTEM_EVENT_H

#include <string>
#include "../../api/c++/z3++.h"

using std::string;
using z3::expr;

class Event {

public:
    Event();
    virtual ~Event();

    /*
     * 设置事件名称
     * @param 事件名称
     */
    virtual void setEventName(const string&) = 0;

    /*
     * 添加expr
     * @param expr
     */
    virtual void addExpr(expr&) = 0;

};


#endif //RUNTIME_VERIFICATION_SYSTEM_EVENT_H
