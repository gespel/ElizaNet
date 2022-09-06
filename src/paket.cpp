#include "paket.h"

void ElizaPaket::createPaket(SenderType st, MessageType mt, std::string message) {
    this->st = st;
    this->mt = mt;
    this->message = message;
}

void ElizaPaket::parsePaket(std::string input) {
    std::string delimiter = ";";

    size_t pos = 0;
    std::string token;
    while ((pos = input.find(delimiter)) != std::string::npos) {
        token = input.substr(0, pos);
        messageVec.push_back(token);
        input.erase(0, pos + delimiter.length());
    }

    if(messageVec[0] == "SERVER") {
        this->st = SenderType::SERVER;
    }
    else if(messageVec[0] == "BOT") {
        this->st = SenderType::BOT;
    }
    else if(messageVec[0] == "HEAD") {
        this->st = SenderType::HEAD;
    }
    else {
        this->st = SenderType::UNDEFINED;
    }

    if(messageVec[1] == "GENERIC") {
        this->mt = MessageType::GENERIC;
    }
    else if(messageVec[1] == "STATUS") {
        this->mt = MessageType::STATUS;
    }
    else if(messageVec[1] == "ATTACK") {
        this->mt = MessageType::ATTACK;
    }
    else if(messageVec[1] == "COMMAND") {
        this->mt = MessageType::COMMAND;
    }
    else if(messageVec[1] == "OUTPUT") {
        this->mt = MessageType::OUTPUT;
    }
    else {
        this->mt = MessageType::UNDEFINED;
    }

    this->message = messageVec[2];
}

std::string ElizaPaket::getSenderType() {
    if(st == SenderType::SERVER) {
        return "SERVER";
    }
    else if(st == SenderType::BOT) {
        return "BOT";
    }
    else if(st == SenderType::HEAD) {
        return "HEAD";
    }
    else if(st == SenderType::UNDEFINED) {
        return "UNDEFINED";
    }
    else {
        return "Error";
    }
}

std::string ElizaPaket::getMessageType() {
    if(mt == MessageType::GENERIC) {
        return "GENERIC";
    }
    else if(mt == MessageType::STATUS) {
        return "STATUS";
    }
    else if(mt == MessageType::ATTACK) {
        return "ATTACK";
    }
    else if(mt == MessageType::COMMAND) {
        return "COMMAND";
    }
    else if(mt == MessageType::OUTPUT) {
        return "OUTPUT";
    }
    else if(mt == MessageType::UNDEFINED) {
        return "UNDEFINED";
    }
    else {
        return "Error";
    }
}

std::string ElizaPaket::getMessage() {
    return this->message;
}

std::string ElizaPaket::toString() {
    std::string out = this->getSenderType() + ";" + this->getMessageType() + ";" + this->getMessage() + ";";
    return out;
}