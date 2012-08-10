#define LOG_TAG "LIBBBQUE"

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

int send_message_to_bbqued (char* cmd, int* nest) {
	char* command = cmd;
	int sockfd;
	struct sockaddr_in server;
	server.sin_family = AF_INET;
	server.sin_port = htons(SERVER_PORT);
	server.sin_addr.s_addr = htonl(INADDR_ANY);
	int i = 0, len;
	char buf[MAXLENGTH] = "", c;
	if ((sockfd = socket(AF_INET, SOCK_STREAM, 0)) == -1)
	{
		LOGE("Socket opening failed!");
		return -1;
	}
	//Connection
	if (connect(sockfd, (struct sockaddr *) &server, sizeof server) == -1)
	{
		LOGE("Socket connection failed!");
		return -1;
	}
	//Receiving ack from the server
	if (recv(sockfd, buf, 2, 0) > 0)
	{
		printf("%s", buf);
	}
	else
	{
		LOGE("Connection to bbqued interrupted!");
		return -1;
	}
	len = strlen(command);
	//Sending command to the server
	if (send(sockfd, command, len, 0) == -1)
	{
		LOGE("Error while sending command to bbqued server!");
		return -1;
	}
	//Receiving response from the server
	if (recv(sockfd, buf, len, 0) > 0)
		*nest = atoi(buf);
	else
	{
		LOGE("Connection to bbqued interrupted!");
		return -1;
	}
	close(sockfd);
	return 0;
}

extern int get_core_availability() {
	int core_number = -1;
	if (send_message_to_bbqued("core", &core_number) >= 0)
		LOGI("get_core_availability() received: %d", core_number);
	return core_number;
}

extern int ask_more_core() {
	int core_number;
	if (send_message_to_bbqued("more", &core_number) >= 0)
		printf("ask_more_core() received: %d", core_number);
	return core_number;
}

extern int ask_les_core() {
	int core_number;
	if (send_message_to_bbqued("less", &core_number) >= 0)
		printf("ask_less_core() received: %d", core_number);
	return core_number;
}

extern int free_core() {
	int core_number;
	if (send_message_to_bbqued("free", &core_number) >= 0)
		printf("free_core() received: %d", core_number);
	return core_number;
}

extern int send_message_to_app(char *c) {
	LOGI("%s - Called bbq_send_message_to_app with message: %s", LOG_TAG, c);
	return 0;
}
