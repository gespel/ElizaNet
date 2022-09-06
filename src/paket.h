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
    std::string getSenderType();
    std::string getMessageType();
    std::string getMessage();
    std::string toString();
private:
    SenderType st;
    MessageType mt;
    std::string message;
    std::vector<std::string> messageVec;
};