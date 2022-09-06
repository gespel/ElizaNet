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

class ElizaNet {
public:
    void setupServer(unsigned int serverPort);
    void startServer();
    void stopServer();
    void handleClients(int sock);

    void setupBot(std::string serverIp, unsigned int serverPort);
    void startBot();

    void setupHead(std::string serverIp, unsigned int serverPort);
    void startHead();
    std::vector<std::string> split(std::string s, std::string delimiter);
private:
    int sockServer, sockClient;
    unsigned int serverPort;
    struct sockaddr_in server, client;
    bool targetDefined = false;
    std::string targetIp = "127.0.0.1";
    std::string targetCommand;
    int paketcount = 0;
    std::map<std::string, std::string> commandMap;
    ElizaPaket* handleHead(ElizaPaket* fromServer);
    ElizaPaket* handleBot(ElizaPaket* fromServer, std::string clientIp);
};