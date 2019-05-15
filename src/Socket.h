/*
 * Socket.h
 *
 *  Created on: 11 may. 2019
 *      Author: caropistillo
 */

#ifndef SOCKET_H_
#define SOCKET_H_

#include <iostream>
#include <cstring>
#include "tools/logger/Logger.h"
#include <arpa/inet.h>
#include <sys/socket.h>

class Socket
{
private:
	 //fileDescriptor
	int port;

public:
	int fd;

	Socket();

	bool create(Logger* logger);

	bool bindToAddress(int port, Logger* logger);

	int get_fd();

	void listenConnection(int maxConnections, Logger* logger);

    bool connectTo(string adressToConnect, int portToConnect);

    void shutdownSocket();

    string receive(size_t length);

    int acceptConnection();

};



#endif /* SOCKET_H_ */
