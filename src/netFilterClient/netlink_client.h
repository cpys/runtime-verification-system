//
// Created by chenkuan on 17-6-14.
//

#ifndef RUNTIME_VERIFICATION_SYSTEM_NETLINK_CLIENT_H
#define RUNTIME_VERIFICATION_SYSTEM_NETLINK_CLIENT_H

#define NETLINK_TEST 20 // 自定义的netlink协议号
#define NETLINK_TEST_CONNECT 0x10  // 自定义的netlink客户端发送连接请求时type
#define NETLINK_TEST_DISCONNECT 0x11   // 自定义的netlink客户端发送断开连接请求时type
#define NETLINK_TEST_COMMAND 0x12  // 自定义的netlink客户端发送的指令
#define NETLINK_TEST_REPLY  0x13   // 自定义的netlink内核回复的消息类型

#define MAXMSG 100000

struct packet_info{
    // 可更改的消息结构体，表示内核与用户态通信的内容，暂定为字符串内容
    //int size;
    char data[MAXMSG];
};

void quitNetLink();
bool netLinkInit();
int getMessage(char*);

#endif //RUNTIME_VERIFICATION_SYSTEM_NETLINK_CLIENT_H