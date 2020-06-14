#ifndef SOCKET_H
#define SOCKET_H
#include <sys/socket.h> //socket library
#include <netinet/in.h> //internet protocol family
#include <stdlib.h> 
#include <iostream>
#include <unistd.h>
#include <string>
#include <arpa/inet.h> 
using namespace std;
class Socket
{
    public:
        Socket(int domain = AF_INET, int type = SOCK_STREAM, int protocol=0); //domain specifies what protocol and addresse we can communicate with, type is TCP or UDP
    
        int startListening(int port);

        int connectToSocket(const char *address, int port);

        int readData(string &buff); //great functions for 
        int sendData(const char *data);
    private:
        int socket_fd; //socket file descriptor for THIS socket object
        sockaddr_in address;
        int address_length;
        bool isServer;
        int opt;
        int domain;
        int type;
        int protocol;

        
        int connectedSocket_fd; //socket file descriptor for the socket THIS socket connects to
        sockaddr_in connectedSocketAddress;
        int connectedSocketAddress_length;
        bool isClient;

};
#endif
