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

FILE *trace_file, *config_file;

void main(int argc ,char *argv[]) {
	if (argc < 2) {
		printf("Wrong number of arguments:\n please provide the file paths for trace file and config file\n");
		exit(1);
	}

	trace_file = fopen(argv[1],"r");
	if (trace_file == 0) {
		printf("Wrong Trace file path exiting ..\n");
		exit(1);
	}
	config_file = fopen(argv[2],"r");
	if (config_file == 0) {
		printf("Wrong config file path exiting ..\n");
		exit(1);
	}
return;
}
