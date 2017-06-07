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
//#include "../../xmlParser/tinyxml2.h"
#include "../../tinyxml2/tinyxml2.h"
#include "server.h"
using namespace std;
using namespace tinyxml2;

int serverSocket, clientSocket;

void quit(int signum) {
    close(serverSocket);
    close(clientSocket);
    exit(0);
}

void Server (){
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

    char charRecv[100] = {0};
    int recvNum;
    XMLDocument xmlDocument;
    while (true) {
        if ((recvNum = recv(clientSocket, charRecv, 100, 0)) < 0) {
            cerr << "recv error" << endl;
            break;
        }
        string message = charRecv;


        XMLError xmlError = xmlDocument.Parse(charRecv);
        if (xmlError != XML_SUCCESS) {
            cerr << "Cannot parse " << charRecv << endl;
            continue;
        }
        XMLElement* root = xmlDocument.FirstChildElement();
        cout << root->Attribute("name") << " " << root->Attribute("value") << endl;


//        cout << charRecv << endl;
    }

    quit(SIGINT);

    return 0;
}