#include <iostream>
#include <vector>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h> 
#include <sys/socket.h>
#include <netinet/in.h>
#include <string.h>
#include <arpa/inet.h>
#include <pthread.h>
#include <thread>
#include <algorithm>
#include <cctype>
#include <mutex>
#include <chrono>
#include <map>
#include "paket.h"

class ElizaNetHead {
public:
    void setupHead(std::string serverIp, unsigned int serverPort);
    void startHead();
private:
    struct sockaddr_in server;
    unsigned int serverPort;
    int sockClient;
};