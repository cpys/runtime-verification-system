//
// Created by yingzi on 2017/6/7.
//

#include <iostream>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <cstring>
#include <unistd.h>
#include <csignal>
#include <random>
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

    uniform_int_distribution<int> u(0, 10000);
    default_random_engine e;

    uniform_int_distribution<int> u2(0, 10);
    default_random_engine e2;

    for (int i = 1; i < 10000; i = i % 10 + 1) {
        if (u2(e2) != i) {
            string message = "<event name=\"event" + to_string(i) + "\" value=\"x = " + to_string(u(e)) + "\"/>";
            send(client, message.c_str(), message.size(), 0);
//        if (send(client, message.c_str(), message.size(), 0) < 0) {
//            cout << "send " << message << "failed!" << endl;
//            break;
//        }
            sleep(1);
        }
    }

    quit(SIGINT);
    return 0;
}