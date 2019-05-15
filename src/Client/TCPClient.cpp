//
// Created by IgVelasco on 5/4/19.
//

#include "TCPClient.h"

TCPClient::TCPClient() {
    sock = -1;
    port = 0;
    address = "";
    socketClient = new Socket();
}

bool TCPClient::setup(string addressToConnect, int listenPort) {
  Logger* logger = Logger::getInstance();
  this->address = addressToConnect;
  socketClient->create(logger);
  if(!socketClient->connectTo(address, listenPort)){
      //this failed
      return false;
  }
  this->port= getNewPort();
    socketClient->shutdownSocket();
  while(!socketClient->connectTo(address,port)){
      cout <<"Reintentando conexion"<<endl;
      sleep (1);
  }

  cout << "Connection succesfull" << endl;


  /*this->conectado = true;
  this->empezarRecibir();
  this->reconexion = true;*/
}

/*
void TCPClient::empezarRecibir() {
    this->threadRecibir.start();
    this->threadEnviar.start();
}

void TCPClient::dejarRecibir() {
    this->threadEnviar.join();
    this->threadRecibir.join();

}
*/


bool TCPClient::Send(string data) {

    this->socketClient;
    if (sock != -1) {
        if (send(sock, data.c_str(), strlen(data.c_str()), 0) < 0) {
            cout << "Send failed : " << data << endl;
            return false;
        }
    } else
        return false;
    return true;
}

string TCPClient::read() {
    char buffer[1] = {};
    string reply;
    while (buffer[0] != '\n') {
        if (recv(sock, buffer, sizeof(buffer), 0) < 0) {
            cout << "receive failed!" << endl;
            return nullptr;
        }
        reply += buffer[0];
    }
    return reply;
}

void TCPClient::exit() {
    close(sock);
}

int TCPClient::getNewPort() {
    /*Recibo 4 bytes en donde ya se que voy a recibir 4 bytes con el puerto nuevo*/
    string puerto = socketClient->receive(4);
    if (puerto == "0005") {
        cout << "El servidor ya esta ocupado con su maxima capacidad" << endl;
        return -1;
    }
    /*Cierro la conexion con el puerto del xml*/
    cout << "El puerto recibido es: " << puerto << endl;

    return stoi(puerto);



}
