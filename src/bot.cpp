#include "elizaNet.h"

int main() {
    ElizaNet *bot = new ElizaNet();
    bot->setupBot("127.0.0.1", 8082);
    bot->startBot();
}