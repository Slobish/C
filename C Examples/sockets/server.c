#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <string.h>

void main(void) {

int newSocket,conSocket;
char writingBuffer[256], readingBuffer[256];
struct sockaddr_in serverAddr;
socklen_t addr_size;

newSocket = socket(PF_INET,SOCK_STREAM,0);

serverAddr.sin_family = AF_INET;
serverAddr.sin_port = htons(7999);
serverAddr.sin_addr.s_addr  = INADDR_ANY;
memset( (void *) &(serverAddr.sin_zero), 0, 8); //pads 0's

if ( bind(newSocket, (struct sockaddr *) &serverAddr, sizeof(serverAddr)) < 0) puts("Error binding");

if (!listen(newSocket, 1)) puts("Listening");
else printf("Error");

conSocket = accept(newSocket, (struct sockaddr *) &serverAddr, &addr_size);
puts("Conexion aceptada");

memset( (void *) readingBuffer, 0 , 256);
if ( read(conSocket, readingBuffer, 256) < 0 ) puts("Error reading");
else printf("This is your message %s", readingBuffer);

if( write(conSocket, "Hola mostro", 11)) < 0 ) puts("Error writing");
else puts("Respond succesfully");

close(conSocket);
close(newSocket);
}
