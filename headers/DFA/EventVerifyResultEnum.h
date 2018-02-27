//
// Created by chenkuan on 2018/2/27.
//

#ifndef RUNTIME_VERIFICATION_SYSTEM_VERIFYRESULTENUM_H
#define RUNTIME_VERIFICATION_SYSTEM_VERIFYRESULTENUM_H

/**
 * 事件验证结果的几种状态
 * accept, 指该事件明确可以通过，将造成状态机的转移变化
 * undetermined, 指该事件可通过可不通过，不对状态机作转移变化
 * refuse, 指该事件不可通过，不对状态机作转移变化
 */
enum EventVerifyResultEnum {
    accept,
    undetermined,
    refuse
};

#endif //RUNTIME_VERIFICATION_SYSTEM_VERIFYRESULTENUM_H
