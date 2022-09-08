#include "paket.h"

void ElizaPaket::createPaket(SenderType st, MessageType mt, std::string message) {
    this->st = st;
    this->mt = mt;
    this->message = message;
}

void ElizaPaket::parsePaket(std::string input) {
    char st = input.at(0);
    char mt = input.at(1);
    std::string msg = input.substr(2, strlen(input.c_str())-1);
    //std::cout << "Sendertype: " << ststr << " Messagetype: " << mtstr << " Message: " << msg << std::endl;

    if(st == '0') {
        this->st = SenderType::SERVER;
    }
    else if(st == '1') {
        this->st = SenderType::BOT;
    }
    else if(st == '2') {
        this->st = SenderType::HEAD;
    }
    else {
        this->st = SenderType::UNDEFINED;
    }

    if(mt == '0') {
        this->mt = MessageType::GENERIC;
    }
    else if(mt == '1') {
        this->mt = MessageType::STATUS;
    }
    else if(mt == '2') {
        this->mt = MessageType::ATTACK;
    }
    else if(mt == '3') {
        this->mt = MessageType::COMMAND;
    }
    else if(mt == '4') {
        this->mt = MessageType::OUTPUT;
    }
    else {
        this->mt = MessageType::UNDEFINED;
    }
    this->message = msg;
}

SenderType ElizaPaket::getSenderType() {
    return this->st;
}

MessageType ElizaPaket::getMessageType() {
    return this->mt;
}

std::string ElizaPaket::getMessage() {
    return this->message;
}
std::string ElizaPaket::senderTypeToString() {
    if(this->getSenderType() == SenderType::SERVER) {
        return "Server";
    }
    else if(this->getSenderType() == SenderType::BOT) {
        return "Bot";
    }
    else if(this->getSenderType() == SenderType::HEAD) {
        return "Head";
    }
    else {
        return "Undefined";
    }
}
std::string ElizaPaket::messageTypeToString() {
    if(this->getMessageType() == MessageType::GENERIC) {
        return "Generic";
    }
    else if(this->getMessageType() == MessageType::STATUS) {
        return "Status";
    }
    else if(this->getMessageType() == MessageType::ATTACK) {
        return "Attack";
    }
    else if(this->getMessageType() == MessageType::COMMAND) {
        return "Command";
    }
    else if(this->getMessageType() == MessageType::OUTPUT) {
        return "Output";
    }
    else {
        return "Undefined";
    }
}
/*std::string ElizaPaket::toString() { //DEPRECATED
    std::string out = this->getSenderType() + ";" + this->getMessageType() + ";" + this->getMessage() + ";";
    return out;
}*/
std::string ElizaPaket::toNetworkPaket() {
    std::string st;
    std::string mt;

    if(this->getSenderType() == SenderType::SERVER) {
        st = "0";
    }
    else if(this->getSenderType() == SenderType::BOT) {
        st = "1";
    }
    else if(this->getSenderType() == SenderType::HEAD) {
        st = "2";
    }
    else {
        st = "3";
    }

    /*GENERIC,
    STATUS,
    ATTACK,
    COMMAND,
    OUTPUT,
    UNDEFINED*/

    if(this->getMessageType() == MessageType::GENERIC) {
        mt = "0";
    }
    else if(this->getMessageType() == MessageType::STATUS) {
        mt = "1";
    }
    else if(this->getMessageType() == MessageType::ATTACK) {
        mt = "2";
    }
    else if(this->getMessageType() == MessageType::COMMAND) {
        mt = "3";
    }
    else if(this->getMessageType() == MessageType::OUTPUT) {
        mt = "4";
    }
    else {
        mt = "5";
    }

    return st + mt + this->message;
}