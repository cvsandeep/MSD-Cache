/******************************************/
/********* ECE 485/585 Final Project ******/
/* main .c
 * 
 *  Author: 
 *
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include "cache_memory.h"

FILE *trace_file, *config_file;

int main(int argc ,char *argv[]) {
	if (argc < 2) {
		printf("Wrong number of arguments:\n Please provide the file paths for trace file and config file\n");
		exit(EXIT_FAILURE);
	}

	trace_file = fopen(argv[1],"r");
	if (trace_file == 0) {
		printf("Wrong Trace file path exiting ..\n");
		exit(EXIT_FAILURE);
	}
	config_file = fopen(argv[2],"r");
	if (config_file == 0) {
		printf("Wrong config file path exiting ..\n");
		exit(EXIT_FAILURE);
	}

	while(1){

	}
return EXIT_SUCCESS;
}
