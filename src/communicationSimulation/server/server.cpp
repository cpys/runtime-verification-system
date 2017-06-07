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

int serverSocket, clientSocket;

void quit(int signum) {
    close(serverSocket);
    close(clientSocket);
    exit(0);
}

int main() {
    serverSocket = socket(AF_INET, SOCK_STREAM, 0);

    struct sockaddr_in serverAddr;

    serverAddr.sin_family = AF_INET;
    serverAddr.sin_addr.s_addr = htonl(INADDR_ANY);
    serverAddr.sin_port = htons(8899);

    bind(serverSocket, (struct sockaddr*)&serverAddr, sizeof(serverAddr));

    listen(serverSocket, 5);

    cout << "server waiting for client connect" << endl;

    clientSocket = accept(serverSocket, NULL, NULL);
    if (clientSocket < 0) {
        cerr << "accept error" << endl;
        return 1;
    }

    signal(SIGINT, quit);

    char charRecv[100];
    int recvNum;
    while (true) {
        if ((recvNum = recv(clientSocket, charRecv, 100, 0)) < 0) {
            cerr << "recv error" << endl;
            break;
        }
        cout << charRecv << endl;
    }

    quit(SIGINT);

    return 0;
}