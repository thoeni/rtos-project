//TODO: Gestire questo metodo in modo che il codice di comunicazione esegua nella libreria, e il client (usato solo da me come test) possa importare la libreria e chiamare il metodo di comunicazione passando la stringa per il server come parametro. Di conseguenza, gestire il server in modo che possa leggere direttamente il parametro del client, gestendo in silenzio la cominicazione con la libreria.
//L'effetto per l'utente deve essere una chiamata ad un metodo della libreria, del tipo message_to_bbqued("core") che, ad esempio, risponda con "16". In tal caso il metodo della libreria verrà poi esposto tramite JNI, e l'applicazione Java potrà invocarlo direttamente passando il messaggio.
//L'idea è quella di prevedere i messaggi core, more, less, free ed un eventuale auto, che lascia al demone il gioco.

#include   <stdio.h>
#include   <stdlib.h>
#include   <string.h>
#include	  <libbbque.h>
 
int main (int argc, char **argv) {
//	printf("Numero core: %s\n",(int)get_core_availability());
	get_core_availability();
	/*if (argc != 2) {
		fprintf(stderr, "Usage: %s <command core more less auto>\n", argv[0]);
		return -1;
	} else {
		char* command = argv[1];
	return send_message_to_bbqued(command);
	}*/
	return 0;
}
