#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <ctype.h>
#include   <cutils/logger.h>
#include   <cutils/log.h>
#include	  <errno.h>

#define LOG_DAEMON_TAG "skbbqued"
#define SERVER_PORT 1313
#define MESSAGE_LENGTH 8
 
int main (int argc, char **argv)
{
  int sock, client_len, fd, len;
  char inputline[MESSAGE_LENGTH];
  int core_number = 16;
  struct sockaddr_in server, client;
 
  /* transport end point */
  if ((sock = socket (AF_INET, SOCK_STREAM, 0)) == -1)
    {
      LOGE("Socket creation failed %s: %s", LOG_DAEMON_TAG, strerror(errno));
      return 1;
    }
 
  server.sin_family = AF_INET;
  server.sin_addr.s_addr = INADDR_ANY;
  server.sin_port = htons (SERVER_PORT);
 
  /* address binding */
  if (bind (sock, (struct sockaddr *) &server, sizeof server) == -1)
    {
      LOGE("Bind failed %s: %s", LOG_DAEMON_TAG, strerror(errno));
      return 1;
    }
 
  listen (sock, 1);
 
  /* gestione delle connessioni dei client */
  while (1)
    {
      client_len = sizeof (client);
      if ((fd = accept (sock, (struct sockaddr *) &client, &client_len)) < 0)
    {
      LOGE("%s - accepting connection error", LOG_DAEMON_TAG);
      return 1;
    }
      LOGI("%s - Connection accepted", LOG_DAEMON_TAG);
      send (fd, "ok", 2, 0);
      len = recv (fd, inputline, MESSAGE_LENGTH, 0);
      //create switch case with different options depending on the input string
      if ( ( strncmp(inputline,"core",4) ) == 0) {
			sprintf(inputline, "%d", core_number);
      	send (fd, inputline, 4, 0);
      }
      else
      	send (fd, inputline, 27, 0);
      close (fd);
      LOGI("%s - Connection closed", LOG_DAEMON_TAG);
    }
}
