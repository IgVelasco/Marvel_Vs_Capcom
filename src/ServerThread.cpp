/*
 * serverThread.cpp
 *
 *  Created on: 12 may. 2019
 *      Author: caropistillo
 */

#include "ServerThread.h"
#include <pthread.h>

ServerThread::ServerThread(TCPServer* server)
{
	this->server = server;
}

bool ServerThread::create()
{
	return(pthread_create(&(this->serverThread), NULL, loopStatic, this)==0);
}

void* ServerThread::loop()
{
/*    int i = 0;
	pthread_detach(pthread_self());
	    while (1)
	    {
	        string str = this->server->getMessage();
	        if (!str.empty()) {
	            cout << "Message:" << str << endl;
	            if(str == "Im connected!")
	                server->Send(to_string(i++));
	            if(str == "salir")
	                break;
	            this->server->clean();
	        }
	    }
	    this->server->detach();
*/

}

void* ServerThread::loopStatic(void *arg)
{
	ServerThread* obj = (ServerThread *)arg;
	obj->loop();
}
/*
void ServerThread::join()
{
	pthread_join(&serverThread,NULL);
}*/



