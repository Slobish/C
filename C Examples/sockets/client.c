#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <netdb.h>
#include <string.h>
#include <unistd.h>
#include <signal.h>
#include <pthread.h>
#include <semaphore.h>


int set_get_socket(int option){
	static int socket = 0;
	if(option < 0)	return socket;
	else {
	socket = option;
	return -1;
	}
}


void *flushBuffer(void *arg){
	while(1);
}
void *readMessages(void *arg){
	int socket = set_get_socket(-1);
	char buffer[256];
	while(1) {
		memset(buffer, 0, 256);
		if(read(socket, buffer, 255) <= 0) raise(SIGINT);
		puts("Él:");
		puts(buffer);
		putc('\n',stdout);
	}
}

static void sig_handler(int signumber){
	close(set_get_socket(-1));
	printf("Closed file: %d",set_get_socket(-1));
	exit(1);
}

void main (int argn, char **args){
	pthread_t main_thr, thread_write, thread_read;
	main_thr = pthread_self();
	int conSocket;
	int i;
	struct sockaddr_in serv_addr;
	struct hostent *server;
	char writingBuffer[256];
	signal(SIGINT, sig_handler);

	conSocket = socket(AF_INET, SOCK_STREAM, 0);
	set_get_socket(conSocket);
	if(argn<3){
		puts("Missing parameter");
		exit(0);
	}

	server = gethostbyname(args[1]);

	memset ( (void*) &serv_addr, 0, sizeof(serv_addr));
	serv_addr.sin_family = AF_INET;
	bcopy( (char *) server->h_addr, (char *) &serv_addr.sin_addr.s_addr, server->h_length);
	serv_addr.sin_port = htons(atoi(args[2]));

	if(connect(conSocket, (struct sockaddr*) &serv_addr, sizeof(serv_addr)) < 0)  puts("Error connecting");
	pthread_create(&thread_read, NULL, readMessages, NULL);
	pthread_create(&thread_write, NULL, flushBuffer, NULL);	

	while (1){

	memset( (void*) writingBuffer, 0, 256);
	printf("Vos:");
	fgets(writingBuffer,256,stdin);
	write(conSocket, writingBuffer, strlen(writingBuffer));
	}


}
