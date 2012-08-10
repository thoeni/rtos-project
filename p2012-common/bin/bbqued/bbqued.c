#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <ctype.h>
#include <pthread.h>
#include <unistd.h>
#include <cutils/logger.h>
#include <cutils/log.h>
#include	<errno.h>

#define NAME "BBQUED DAEMON"
#define SERVER_PORT 1313
#define MESSAGE_LENGTH 8
#define MAX_CORE 16

int core_number = MAX_CORE;

void *talker( void *arg )
{
int 	fd = (int) arg;
char 	inputline[MESSAGE_LENGTH];
int 	i;
	LOGI("Thread %d: handling communication with client\n", fd);
	/* send confirmation to client, and read from the given socket */
	send (fd, "ok", 2, 0);
   recv (fd, inputline, MESSAGE_LENGTH, 0);

	if ( ( strncmp(inputline,"core",4) ) == 0) {
			sprintf(inputline, "%d", core_number);
      	send (fd, inputline, 4, 0);
   }
   else if ( ( strncmp(inputline,"more",4) ) == 0){
   		/* use a mutex to update the global service counter */
   		if (core_number > 0)
				core_number--;
			sprintf(inputline, "%d", core_number);
      	send (fd, inputline, 4, 0);
   }
   else if ( ( strncmp(inputline,"less",4) ) == 0){
   		/* use a mutex to update the global service counter */
   		if (core_number < MAX_CORE)
				core_number++;
			sprintf(inputline, "%d", core_number);
      	send (fd, inputline, 4, 0);
   }
   else if ( ( strncmp(inputline,"free",4) ) == 0){
   		/* use a mutex to update the global service counter */
			core_number = MAX_CORE;
			sprintf(inputline, "%d", core_number);
      	send (fd, inputline, 4, 0);
   }
   else
   	send (fd, inputline, 27, 0);

	/* close the socket and exit this thread */
	close(fd);
	LOGI("Thread %d: closed communication with client\n", fd);
	return 0;
}

int main (int argc, char **argv)
{
	int sock, client_len, fd, len;
	char inputline[MESSAGE_LENGTH];
	struct sockaddr_in server, client;
	pthread_t thread[50];
	int i = 1;
	/* transport end point */
	if ((sock = socket (AF_INET, SOCK_STREAM, 0)) == -1)
	{
		LOGE("Socket creation failed %s:", NAME);
		return -1;
	}
	server.sin_family = AF_INET;
	server.sin_addr.s_addr = INADDR_ANY;
	server.sin_port = htons (SERVER_PORT);
	/* address binding */
	if (bind (sock, (struct sockaddr *) &server, sizeof server) == -1)
	{
		LOGE("Bind failed %s", NAME);
		return 1;
	}
	listen (sock, 1);
	/* gestione delle connessioni dei client */
	while (1)
	{
		client_len = sizeof (client);
		if ((fd = accept (sock, (struct sockaddr *) &client, &client_len)) < 0) 
		{
			LOGE("%s - accepting connection error", NAME);
			return 1;
		}
		/* create a new thread to process the incomming request */
		LOGI("Connection accepted - creating thread...\n");
		pthread_create( &(thread[i++]), NULL, talker, (void*)fd );
		//If core_number less than 5, signal to app.
	}
	return 0;
}
