//
// Created by yingzi on 2017/6/7.
//

#include <iostream>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <cstring>
#include <unistd.h>
using namespace std;

int client;

void quit(int signum) {
    close(client);
    exit(0);
}

int main() {
    client = socket(AF_INET, SOCK_STREAM, 0);
    if (client < 0) {
        cout << "socket create failed!" << endl;
        return 1;
    }

    struct sockaddr_in clientAddr;

    clientAddr.sin_family = AF_INET;
    inet_pton(AF_INET, "127.0.0.1", &clientAddr.sin_addr);
    clientAddr.sin_port = htons(8899);

    if (connect(client, (struct sockaddr*)&clientAddr, sizeof(clientAddr)) < 0) {
        cout << "cannot connect to the server!" << endl;
        return 1;
    }

    for (int i = 1; i < 10000; i = (i + 1) % 1000) {
        string message = "x = " + i;
        if (send(client, message.c_str(), message.size(), 0) < 0) {
            cout << "send " << message << "failed!" << endl;
            break;
        }
        usleep(500000);
    }

    quit(SIGINT);
    return 0;
}