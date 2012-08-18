#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <ctype.h>
#include <pthread.h>
#include <unistd.h>
#include <android/log.h>
#include	<errno.h>
#include  <libbbque.h>

#define LOG_TAG "BBQUED DAEMON"
#define SERVER_PORT 1313
#define MESSAGE_LENGTH 8
#define MAX_CORE 16

int core_number = MAX_CORE;

void *talker( void *arg )
{
int 	fd = (int) arg;
char 	inputline[MESSAGE_LENGTH];
int 	i;
	__android_log_write(ANDROID_LOG_INFO, LOG_TAG, "Thread - handling communication with client.");
	//LOGI("Thread %d: handling communication with client\n", fd);
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
	//LOGI("Thread %d: closed communication with client\n", fd);
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
		__android_log_write(ANDROID_LOG_INFO, LOG_TAG, "Socket creation failed.");
		//LOGE("Socket creation failed.");
		return -1;
	}
	server.sin_family = AF_INET;
	server.sin_addr.s_addr = INADDR_ANY;
	server.sin_port = htons (SERVER_PORT);
	/* address binding */
	if (bind (sock, (struct sockaddr *) &server, sizeof server) == -1)
	{
		__android_log_write(ANDROID_LOG_INFO, LOG_TAG, "Bind failed.");
		//LOGE("Bind failed");
		return 1;
	}
	listen (sock, 1);
	/* gestione delle connessioni dei client */
	while (1)
	{
		client_len = sizeof (client);
		if ((fd = accept (sock, (struct sockaddr *) &client, &client_len)) < 0) 
		{
			__android_log_write(ANDROID_LOG_INFO, LOG_TAG, "Accepting connection error.");
			//LOGE("Accepting connection error.");
			return 1;
		}
		/* create a new thread to process the incomming request */
		__android_log_write(ANDROID_LOG_INFO, LOG_TAG, "Connection accepted, creating thread...");
		//LOGI("Connection accepted - creating thread...\n");
		pthread_create( &(thread[i++]), NULL, talker, (void*)fd );
		//If core_number less than 5, signal to app.
	}
	return 0;
}
