#include "elizaNet.h"

int main() {
    ElizaNet* head = new ElizaNet();
    head->setupHead("127.0.0.1", 8082);
    head->startHead();
}