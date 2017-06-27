//
// Created by yingzi on 2017/6/27.
//

#ifndef RUNTIME_VERIFICATION_SYSTEM_NETLINK_H
#define RUNTIME_VERIFICATION_SYSTEM_NETLINK_H

#include <string>
#include <linux/netlink.h>

using std::string;

class NetLink {
  public:
    bool init();    // 初始化连接到内核
    bool quit();    // 关闭连接
    string recvMessage();   // 接收来自内核的消息
    bool sendMessage(const string &msg, int protocol);    // 向内核发送消息

    static const int NETLINK_TEST_ACCPT = 0x13;  // 自定义的netlink客户端发送的指令，允许数据包通过
    static const int NETLINK_TEST_DISCARD = 0x14;   // 丢弃数据包

  private:
    int clientSocket;   // 客户端套接字
    struct sockaddr_nl clientAddr;  // 客户端地址

    struct sockaddr_nl serverAddr;  // 内核目的地址

    static const int MAX_MSG_SIZE = 100000; // 消息主体的最大长度

    // netlink消息主体
    struct PacketInfo {
        // int size;
        char data[MAX_MSG_SIZE];
    };

    // netlink消息结构
    struct netLinkMsgStruct {
        struct nlmsghdr hdr;    // netlink的消息首部
        struct PacketInfo body; // netlink的消息主体
    };

    netLinkMsgStruct buffer;    // netlink消息

    static const int NETLINK_TEST = 20; // 自定义的netlink协议号
    static const int NETLINK_TEST_CONNECT = 0x10;  // 自定义的netlink客户端发送连接请求时type
    static const int NETLINK_TEST_DISCONNECT = 0x11;   // 自定义的netlink客户端发送断开连接请求时type
    static const int NETLINK_TEST_REPLY = 0x12;   // 自定义的netlink内核回复的消息类型

};


#endif //RUNTIME_VERIFICATION_SYSTEM_NETLINK_H
