//
// Created by chenkuan on 17-5-29.
//

#ifndef RUNTIME_VERIFICATION_SYSTEM_DFAEVENT_H
#define RUNTIME_VERIFICATION_SYSTEM_DFAEVENT_H

#include <set>
#include "../rvsDFAInterface/Event.h"

using std::set;

class DFAEvent : public Event {

public:
    DFAEvent();
    ~DFAEvent();

    void setEventName(const string&);
    void addExpr(expr&);

private:
    string eventName;
    set<expr> exps;
};


#endif //RUNTIME_VERIFICATION_SYSTEM_DFAEVENT_H
