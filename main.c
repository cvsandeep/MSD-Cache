/******************************************
 ********* ECE 485/585 Final Project ******
 * main .c
 * 
 *  Author: Team
 *
 *
 ******************************************/

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "cache_memory.h"
#include "cache_control.h"

extern FILE *trace_file, *config_file;

int main(int argc ,char *argv[]) {
	if (argc < 2) {
		printf("Wrong number of arguments:\n Please provide the file paths for trace file and config file\n");
		exit(EXIT_FAILURE);
	}

	trace_file = fopen(argv[1],"r");
	if (trace_file == 0) {
		printf("Wrong Trace file path. Exiting ..\n");
		exit(EXIT_FAILURE);
	}
	config_file = fopen(argv[2],"r");
	if (config_file == 0) {
		printf("Wrong config file path. Exiting ..\n");
		exit(EXIT_FAILURE);
	}

	UpdateConfig();
	//Info to use structures
	struct CACHE_LINE w0[4];
	//Iterate through ways from 0 t0 sizeof(w0)/sizeof(struct CACHE_LINE)
	printf("Number of CACHE_LINE=%d",sizeof(w0)/sizeof(struct CACHE_LINE));
	printf("Number of offsets in CACHE_LINE=%d",sizeof(w0[0].offset)/sizeof(int));

	while(UpdateTraceOperation()){
		UpdateConfig();

	}
return EXIT_SUCCESS;
}
