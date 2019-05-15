//
// Created by IgVelasco on 5/4/19.
//

#include "TCPServer.h"

string TCPServer::Message;
const int maxConnections = 4;
const string ERROR = "ERROR";
const string INFO = "INFO";
const string DEBUG = "DEBUG";

TCPServer::TCPServer() {
    this->numberOfConnections = 0;
    this->port = 0;
    this->sockfd = 0;
    this->listenSockFD = 0;
    this->newsockfd = 0;
    this->serverSocket = new Socket();
}

void *TCPServer::Task(void *arg) {
    int n;
    int newsockfd = (long) arg;
    char msg[MAXPACKETSIZE];
    pthread_detach(pthread_self());
    while (1) {
        n = recv(newsockfd, msg, MAXPACKETSIZE, 0);
        if (n == 0) {
            close(newsockfd);
            break;
        }
        msg[n] = 0;
        //send(newsockfd,msg,n,0);
        Message = string(msg);
    }
    return 0;
}

bool TCPServer::setup(int portToListen, Logger *logger) {

    logger->log("Comienza a iniciarse el servidor", INFO);
    logger->log("Se crea el socket de escucha del servidor", INFO);
    port = portToListen;
    this->setSockfd(this->serverSocket->create(logger));
    if(this->serverSocket->fd == -1)
        return false;
    listenSockFD = sockfd = serverSocket->fd;

    string msgInfo = "El numero de puerto es: " + to_string(this->port);
    logger->log(msgInfo, INFO);

    if(!this->serverSocket->bindToAddress(port, logger))
        return false;

    this->serverSocket->listenConnection(maxConnections, logger);

    running = true;

    return true;
}

string TCPServer::receive() {
    Logger* logger = Logger::getInstance();
    string str;
    serverSocket->listenConnection(MAXPLAYERS, logger);
    if(this->numberOfConnections == MAXPLAYERS)
        return NULL;
    int fd = serverSocket->acceptConnection();
    serverSocket->fd = fd;
    int portToConnect = port;

    Socket *newSock = new Socket();
    newSock->create(logger);


    while(!newSock->bindToAddress(portToConnect,logger)){
        portToConnect++;
    }

    this->sendMessage(to_string(portToConnect));
    cout << portToConnect << endl;

    newSock->listenConnection(MAXPLAYERS, logger);
    int fdd = newSock->acceptConnection();
    //Linea 244
    newSock->fd = fdd;

    shutdown(fd,SHUT_RDWR);

    return str;
}

string TCPServer::getMessage() {
    return Message;
}

void TCPServer::Send(string msg) {
    send(newsockfd, msg.c_str(), msg.length(), 0);
}

void TCPServer::clean() {
    Message = "";
    memset(msg, 0, MAXPACKETSIZE);
}

void TCPServer::detach() {
    close(this->serverSocket->get_fd());
    close(newsockfd);
}

void TCPServer::setSockfd(int sockfd) {
    this->sockfd = sockfd;
}

bool TCPServer::maxNumberReached() {
    return numberOfConnections == MAXPLAYERS;
}

void TCPServer::sendMessage(string basicString) {

}
