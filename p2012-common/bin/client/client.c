#include   <stdio.h>
#include   <stdlib.h>
#include   <string.h>
#include	  <libbbque.h>
 
int main (int argc, char **argv) {
//	printf("Numero core: %s\n",(int)get_core_availability());
//	get_core_availability();
	int num;
	if (argc != 2) {
		fprintf(stderr, "Usage: %s <command core more less auto>\n", argv[0]);
		return -1;
	} else {
		char* command = argv[1];
	send_message_to_bbqued(command, &num);
	printf("current number of cores: %d\n", num);
	}
	return 0;
}
