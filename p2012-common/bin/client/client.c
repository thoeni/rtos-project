//TODO: Gestire questo metodo in modo che il codice di comunicazione esegua nella libreria, e il client (usato solo da me come test) possa importare la libreria e chiamare il metodo di comunicazione passando la stringa per il server come parametro. Di conseguenza, gestire il server in modo che possa leggere direttamente il parametro del client, gestendo in silenzio la cominicazione con la libreria.
//L'effetto per l'utente deve essere una chiamata ad un metodo della libreria, del tipo message_to_bbqued("core") che, ad esempio, risponda con "16". In tal caso il metodo della libreria verrà poi esposto tramite JNI, e l'applicazione Java potrà invocarlo direttamente passando il messaggio.
//L'idea è quella di prevedere i messaggi core, more, less, free ed un eventuale auto, che lascia al demone il gioco.

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
 
#define MAXLENGTH 8
#define SERVER_PORT 1313
 
int main (int argc, char **argv) {
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
      return 1;
    }
 
  /* connessione al server */
  if (connect(sockfd, (struct sockaddr *) &server, sizeof server) == -1)
    {
      perror("connessione al server fallita");
      return 2;
    }
 
  /* ricezione e stampa a video del messaggio di benvenuto del server */
  if (recv(sockfd, buf, 2, 0) > 0)
    {
      printf("%s", buf);
    }
  else
    {
      perror("Connessione al server interrotta");
      return 3;
    }
 
  /* acquisizione della stringa da standard input */
  printf("\nDigita una stringa:");
  while ((c = getchar()) != '\n' && i < MAXLENGTH)
    buf[i++] = c;
 
  buf[i] = '\0';
  len = strlen(buf);
  
  printf("Invio la stringa %s di lunghezza %d sul socket %d...\n",buf,len,sockfd);
 
  /* invio e ricezione della stringa */
  if (send(sockfd, buf, len, 0) == -1)
    {
      perror("Errore nell'invio della stringa al server");
      return 4;
    }
    
 
  if (recv(sockfd, buf, len, 0) > 0)
    {
      printf("%s\n", buf);
    }
  else
    {
      perror("Connessione al server interrotta");
      return 5;
    }
 
  /* chiusura della connessione */
  close(sockfd);
  return 0;
}
