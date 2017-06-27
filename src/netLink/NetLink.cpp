//
// Created by yingzi on 2017/6/27.
//

#include "NetLink.h"
#include <sys/stat.h>
#include <unistd.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <asm/types.h>
#include <linux/socket.h>
#include <errno.h>
#include <signal.h>
#include <cstring>
#include <iostream>

using std::cout;
using std::cerr;
using std::endl;
using std::string;

bool NetLink::init() {
    // 创建客户端原始套接字，协议为NETLINK_TEST
    if ((clientSocket = socket(PF_NETLINK, SOCK_RAW, NETLINK_TEST)) < 0) {
        cerr << "can't create netlink socket!" << endl;
        return false;
    }

    // 设置本地地址
    memset(&clientAddr, 0, sizeof(clientAddr));
    clientAddr.nl_family = AF_NETLINK;
    clientAddr.nl_pid = getpid();
    clientAddr.nl_groups = 0;

    // 将套接字与本地地址绑定
    if (bind(clientSocket, (struct sockaddr*)&clientAddr, sizeof(clientAddr)) != 0){
        cerr << "bind() error!" << endl;
        return false;
    }

    // 设置目标地址数据结构
    memset(&serverAddr, 0, sizeof(serverAddr));   //清空
    serverAddr.nl_family = AF_NETLINK;   // 设置协议簇
    serverAddr.nl_pid = 0;   // 接收或发送消息的进程的id，内核处理消息所以设置为0
    serverAddr.nl_groups = 0;    // 指定多播组，设置为0表示调用者不加入任何多播组

    // 发送连接消息
    if (!sendMessage("", NETLINK_TEST_CONNECT)) return false;
    else return true;
}

bool NetLink::quit() {
    if (!sendMessage("", NETLINK_TEST_DISCONNECT)) {
        cerr << "send disconnect message to kernel failed!" << endl;
        return false;
    }
    close(clientSocket);
    return true;
}

string NetLink::recvMessage() {
    int serverAddrLen = sizeof(struct sockaddr_nl);
    if (recvfrom(clientSocket, &buffer, sizeof(buffer), 0, (struct sockaddr*)&serverAddr, (socklen_t*)&serverAddrLen) < 0) {
        cerr << "recv message from kernel failed!" << endl;
        return "";
    }
    else {
        string msg(std::begin(buffer.body.data), std::end(buffer.body.data));
        cout << msg << endl;
        return msg;
    }
}

bool NetLink::sendMessage(const string &msg, int protocol) {
    // 设置消息头
    struct nlmsghdr netLinkMsgHeader;
    memset(&netLinkMsgHeader, 0, sizeof(netLinkMsgHeader)); // 清空该消息
    netLinkMsgHeader.nlmsg_len = NLMSG_LENGTH(msg.size());    // netlink消息的总长度,仅需提供发送数据的长度，由该宏自动计算对齐后的总长度
    netLinkMsgHeader.nlmsg_flags = 0;   // 用户应用内部定义消息的类型，大部分情况下设置为0
    netLinkMsgHeader.nlmsg_type = protocol;   // 设置消息标志，这里设置为连接时标志
    netLinkMsgHeader.nlmsg_pid = getpid();   // 设置发送者的PID

    if (sendto(clientSocket, &netLinkMsgHeader, netLinkMsgHeader.nlmsg_len, 0, (struct sockaddr*)&serverAddr, sizeof(serverAddr)) < 0) {
        cerr << "send message " << msg << " to kernel failed!" << endl;
        return false;
    }
    else {
        cout << "send message " << msg << " to kernel success!" << endl;
        return true;
    }
}