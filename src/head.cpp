#include "head.h"

void ElizaNetHead::setupHead(std::string serverIp, unsigned int serverPort) {
    this->serverPort = serverPort;
    this->server.sin_family = AF_INET;
    this->server.sin_addr.s_addr = inet_addr(serverIp.c_str());
    this->server.sin_port = htons(serverPort);
}
void ElizaNetHead::startHead() {
    while(1) {
        
        ElizaPaket *toserver = new ElizaPaket();
        ElizaPaket *fromserver = new ElizaPaket();
        char buf[1024];
        memset(&buf[0], 0, sizeof(buf));

        std::string input;
        std::cout << "ElizaNet> ";
        std::cin >> input;

        if(input == "test") {
            toserver->createPaket(SenderType::HEAD, MessageType::GENERIC, "TEST");
        }
        if(input == "sendcommand") {
            std::string target;
            std::string command;
            std::cout << "Enter target IP: ";
            std::cin >> target;
            std::getline(std::cin, command);
            std::string snd = target + " " + command + " ";

            toserver->createPaket(SenderType::HEAD, MessageType::COMMAND, snd);
        }

        std::cout << "paket created, trying to send now..." << std::endl;
        this->sockClient = socket(AF_INET, SOCK_STREAM, 0);
        if(connect(sockClient, (struct sockaddr*)&server, sizeof(server)) == 0) {
            std::cout << "connection successfull, sending now..." << std::endl;
        }
        send(sockClient,  toserver->toNetworkPaket().c_str(), strlen(toserver->toNetworkPaket().c_str()), 0);
        read(sockClient, buf, 1024);
        std::cout << "answer recieved..." << std::endl << "===========" << std::endl;
        fromserver->parsePaket(std::string(buf));

        if(fromserver->getSenderType() == SenderType::SERVER) {
            if(fromserver->getMessageType() == MessageType::GENERIC) {
                if(fromserver->getMessage() == "CMDRECIEVED") {
                    std::cout << "Command recieved and waiting for client callback..." << std::endl << std::endl;
                }
                else if(fromserver->getMessage() == "ALLOK") {
                    std::cout << "Server online and everything running" << std::endl << std::endl;
                }
            }
        }

        delete toserver;
        delete fromserver; 
    }
}

int main() {
    ElizaNetHead* head = new ElizaNetHead();
    head->setupHead("127.0.0.1", 8082);
    head->startHead();
}