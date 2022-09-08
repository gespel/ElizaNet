#include <string.h>
#include <iostream>
#include <stdlib.h>
#include <string.h>
#include <vector>
#include "enums.h"

class ElizaPaket {
public:
    void createPaket(SenderType st, MessageType mt, std::string message);
    void parsePaket(std::string input);
    SenderType getSenderType();
    MessageType getMessageType();
    std::string getMessage();
    std::string senderTypeToString();
    std::string messageTypeToString();
    std::string toNetworkPaket();
private:
    SenderType st;
    MessageType mt;
    std::string message;
    std::vector<std::string> messageVec;
};