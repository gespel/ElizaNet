#include "paket.h"

int main() {
    ElizaPaket* test = new ElizaPaket();
    test->createPaket(SenderType::SERVER, MessageType::GENERIC, "blabla");
    std::cout << test->toNetworkPaket() << std::endl;
    return 0;
}