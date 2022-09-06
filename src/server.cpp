#include "elizaNet.h"

int main() {
    ElizaNet *server = new ElizaNet();
    server->setupServer(8082);
    server->startServer();
}