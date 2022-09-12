#include "bot.h"

void ElizaNetBot::setupBot(std::string serverIp, unsigned int serverPort) {
    this->serverPort = serverPort;
    this->server.sin_family = AF_INET;
    this->server.sin_addr.s_addr = inet_addr(serverIp.c_str());
    this->server.sin_port = htons(serverPort);
}
void ElizaNetBot::startBot() {
    while(1) {
        this->sockClient = socket(AF_INET, SOCK_STREAM, 0);
        connect(sockClient, (struct sockaddr*)&server, sizeof(server));
        ElizaPaket *toserver = new ElizaPaket();
        ElizaPaket *fromserver = new ElizaPaket();
        char buf[1024];
        memset(&buf[0], 0, sizeof(buf));

        toserver->createPaket(SenderType::BOT, MessageType::STATUS, "WHATSGOINGON?");
        //std::cout << toserver->toNetworkPaket();
        send(sockClient,  toserver->toNetworkPaket().c_str(), strlen(toserver->toNetworkPaket().c_str()), 0);
        read(sockClient, buf, 1024);
        fromserver->parsePaket(std::string(buf));
        if(fromserver->getMessageType() == MessageType::ATTACK) {
            std::cout << "Attack Signal recieved!!!!" << std::endl << "Target is " << fromserver->getMessage() << std::endl;
        }
        else if(fromserver->getMessageType() == MessageType::COMMAND) {
            std::cout << "Command recieved! " << fromserver->getMessage() << std::endl;
        }
        else {
            std::cout << "Nothing to do...." << std::endl;
        }
        std::this_thread::sleep_for(std::chrono::milliseconds(5000));
        delete toserver;
        delete fromserver; 
    }
}


int main() {
    ElizaNetBot *bot = new ElizaNetBot();
    bot->setupBot("127.0.0.1", 8082);
    bot->startBot();
}