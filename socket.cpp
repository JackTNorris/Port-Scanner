#include "socket.h"

Socket::Socket(int domain, int type, int protocol)
{
    this->socket_fd = socket(domain, type, protocol);
    this->domain = domain, this->type = type, this->protocol = protocol;
    this->address.sin_family = AF_INET; 
    this->address.sin_addr.s_addr = INADDR_ANY; 
    isClient = false;
    isServer = false;
    opt = 1;
    if(socket_fd == -1)
    {
        cerr << "Error constructing socket" << endl;
        exit(EXIT_FAILURE);
    }
    
    if (setsockopt(socket_fd, SOL_SOCKET, SO_KEEPALIVE , &opt, sizeof(opt)))
    { 
        perror("setsockopt"); 
        exit(EXIT_FAILURE); 
    } 
    address_length = sizeof(address);
}

int Socket::startListening(int port)
{
    if(!isClient){
        isServer = true;
        this->address.sin_port = htons(port);
        if(bind(socket_fd, (sockaddr *)&address, address_length) < 0){cerr << "Error binding to port" << endl; exit(EXIT_FAILURE);}
        if(listen(socket_fd, 3)){cerr << "Couldn't start listening" << endl; exit(EXIT_FAILURE);}
        if ((connectedSocket_fd = accept(socket_fd, (struct sockaddr *)&address, (socklen_t*)&address_length)) < 0) 
        { 
            return -1;
        }
        return 1;
    }
    else
    {
        return -1;
    }
    

}

int Socket::readData(string &buff)
{
    if(isServer)
    {
        char buffer[1024] = {'\0'};
        recv(connectedSocket_fd, buffer, 1024,  0);
        buff = buffer;
        if(listen(socket_fd, 3)){return -1;}
        return 1;
    }
    if(isClient)
    {
        char buffer[1024] = {'\0'};
        recv(socket_fd, buffer, 1024,  0);
        buff = buffer;
        return 1;
    }
    else
    {
        return -1;
    }
    
}

int Socket::connectToSocket(const char *address, int port)
{
    if(!isServer)
    {
        isClient = true;
        connectedSocketAddress.sin_family = AF_INET; 
        connectedSocketAddress.sin_port = htons(port); 
        
        // Convert IPv4 and IPv6 addresses from text to binary form 
        if(inet_pton(AF_INET, address, &connectedSocketAddress.sin_addr)<=0)  
        { 
            return -1;
            //exit(EXIT_FAILURE); 
        } 
    
        if (connect(socket_fd, (struct sockaddr *)&connectedSocketAddress, sizeof(connectedSocketAddress)) < 0) 
        { 
            return -1;
            //exit(EXIT_FAILURE); 
        }
        return 1;

    }
    else
    {
        return -1;
    }
    

}

int Socket::sendData(const char data[1024])
{
    if(isServer)
    {
        return send(connectedSocket_fd, data, 1024, 0);
    }
    else if(isClient)
    {
        return send(socket_fd, data, 1024, 0);
    }
    else
    {
        return -1;
    }
    
}





