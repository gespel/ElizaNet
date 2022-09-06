#include "elizaNet.h"

int main() {
    ElizaNet* head = new ElizaNet();
    head->setupHead("144.91.85.101", 8082);
    head->startHead();
}