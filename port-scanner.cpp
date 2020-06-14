#include "./socket.h"
#include <fstream>
#include <string>
#include <pthread.h>
#include <vector>

#define NUM_PORTS 100

string ip;
void *port_check_thread(void *thread_args);

int main(int argc, char* args[])
{
    Socket client;
    ip = args[1];
    int id[NUM_PORTS];
    pthread_t threads[NUM_PORTS];

    for(int port = 0; port < NUM_PORTS; port++)
    {
        id[port] = port;
        int er = pthread_create(&threads[port], NULL, &port_check_thread, &id[port]);
        if(er){cerr << "Failed to create thread"; exit(EXIT_FAILURE);}
    }
    for(int i = 0; i < NUM_PORTS; i++)
        pthread_join(threads[i], NULL);
    for(int i = 0; i < NUM_PORTS;  i++)
    {
        (id[i] == 1) ? cout << "Port " << i << " is open!" << endl : cout << "Port " << i << " is closed!" << endl;
    }


    cout << "Program finished" << endl;
}

void *port_check_thread(void *port)
{
        Socket client;
        int *port_num = (int *)port;
        int res = client.connectToSocket(ip.c_str(), *port_num);
        (res > 0) ? *port_num = 1 : *port_num = 0;
        //(res > 0) ? open_ports.push_back(port_num) : closed_ports.push_back(port_num);
        pthread_exit(NULL);
}
