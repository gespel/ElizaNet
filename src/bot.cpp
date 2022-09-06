#include "elizaNet.h"

int main() {
    ElizaNet *bot = new ElizaNet();
    bot->setupBot("144.91.85.101", 8082);
    bot->startBot();
}