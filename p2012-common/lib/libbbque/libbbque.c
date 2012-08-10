#define LOG_TAG "libbbque"

#include   <stdio.h>
#include   <stdlib.h>
#include   <string.h>
#include   <ctype.h>
#include   <sys/types.h>
#include   <sys/socket.h>
#include   <netinet/in.h>
#include   <cutils/logger.h>
#include   <cutils/log.h>
#include	  <errno.h>
#include   "libbbque.h"
 
#define MAXLENGTH 8
#define SERVER_PORT 1313

extern int get_core_availability() {
	//Add some controls
	send_message_to_bbqued("core", &core_number);
	printf("Core number in get_core_availability(): %d", core_number);
	return core_number;
}

extern int send_message_to_bbqued (char* cmd, int* nest) {
	char* command = cmd;
	int sockfd;
	//struct sockaddr_in server={AF_INET,htons(SERVER_PORT),INADDR_ANY};
	struct sockaddr_in server;
	server.sin_family = AF_INET;
	server.sin_port = htons(SERVER_PORT);
	server.sin_addr.s_addr = htonl(INADDR_ANY);
	int i = 0, len;
	char buf[MAXLENGTH] = "", c;
	if ((sockfd = socket(AF_INET, SOCK_STREAM, 0)) == -1)
	{
		perror("chiamata alla system call socket fallita");
		return -1;
	}
	/* connessione al server */
	if (connect(sockfd, (struct sockaddr *) &server, sizeof server) == -1)
	{
		perror("connessione al server fallita");
		return -1;
	}
	/* ricezione e stampa a video del messaggio di benvenuto del server */
	if (recv(sockfd, buf, 2, 0) > 0)
	{
		printf("%s", buf);
	}
	else
	{
		perror("Connessione al server interrotta");
		return -1;
	}
	/* acquisizione della stringa da standard input */
	/*printf("\nDigita una stringa:");
	while ((c = getchar()) != '\n' && i < MAXLENGTH)
	buf[i++] = c;
	buf[i] = '\0';
	len = strlen(buf);*/
	len = strlen(command);
	printf("Invio la stringa %s di lunghezza %d sul socket %d...\n",command,len,sockfd);
	/* invio e ricezione della stringa */
	if (send(sockfd, command, len, 0) == -1)
	{
		perror("Errore nell'invio della stringa al server");
		return -1;
	}
	 
	if (recv(sockfd, buf, len, 0) > 0)
	{
		printf("Il server risponde %s\n", buf);
		*nest = atoi(buf);
	}
	else
	{
		perror("Connessione al server interrotta");
		return -1;
	}

	/* chiusura della connessione */
	close(sockfd);
	return 0;
}

extern int send_message_to_app(char *c) {
	LOGI("%s - Called bbq_send_message_to_app with message: %s", LOG_TAG, c);
	return 0;
}
