//
// Created by IgVelasco on 5/4/19.
//
#ifndef TCP_CLIENT_H
#define TCP_CLIENT_H

#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <netdb.h>
#include <vector>
#include "../Socket.h"

using namespace std;

class TCPClient
{
private:
    Socket* socketClient;

    int sock;
    std::string address;
    int port;
    struct sockaddr_in server;

public:
    TCPClient();
    bool setup(string address, int listenPort);
    bool Send(string data);

    string read();
    void exit();

    int getNewPort();
};

#endif
