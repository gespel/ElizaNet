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

class ElizaNetBot {
public:
    void setupBot(std::string serverIp, unsigned int serverPort);
    void startBot();
private:    
    unsigned int serverPort;
    struct sockaddr_in server;
    int sockClient;
};