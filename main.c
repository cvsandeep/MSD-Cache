/******************************************
 ********* ECE 485/585 Final Project ******
 ********* Simulate L2 unified cache ******
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
#include "cache_operation.h"
#include "logger.h"

extern FILE *trace_file, *config_file;
extern unsigned int op, addr;

int main(int argc ,char *argv[]) {
	debugLog(0, "", "Function Name \t \t Message\n");
	//debugLog("---------------------------------------------------\n");
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
	readData();
	printf("Debug level is %d\n",debug);
	//L2.set->way = malloc(sizeof(struct  CACHE_LINE) * associativity);
	//L2.set->PLRU = malloc(sizeof(struct  int) *7);
	//L2.set = malloc(sizeof(struct CACHE_SET_8_WAY)*sets);
	//Info to use structures
	//struct CACHE_LINE w0[4];
	//Iterate through ways from 0 t0 sizeof(w0)/sizeof(struct CACHE_LINE)
	//printf("Number of CACHE_LINE=%d",sizeof(w0)/sizeof(struct CACHE_LINE));
	//printf("Number of offsets in CACHE_LINE=%d",sizeof(w0[0].offset)/sizeof(int));

	while(UpdateTraceOperation()){
		printf("\n operation %d address 0x%x\n ",op,addr);
		switch (op) {
			case READ_DATA:
				printf("operation READ_DATA");
				readData();
				break;
			case WRITE_DATA:
				printf("operation WRITE_DATA");
				writeData();
				break;
			case READ_INSTRUCTION:
				printf("operation READ_INSTRUCTION");
				ReadInstruction();
				break;
			case SNOOPED_INVALIDATE:
				printf("operation SNOOPED_INVALIDATE");
				SnoopedInvalidate();
				break;
			case SNOOPED_READ:
				printf("operation SNOOPED_READ");
				SnoopedRead();
				break;
			case SNOOPED_WRITE:
				printf("operation SNOOPED_WRITE");
				SnoopedWrite();
				break;
			case SNOOPED_READ_X:
				printf("operation SNOOPED_READ_X");
				SnoopedReadX();
				break;
			case CLEAR_AND_RESET:
				printf("operation CLEAR_AND_RESET");
				ClearAndSet();
				break;
			case PRINT_CACHE_LINE:
				printf("operation PRINT_CACHE_LINE");
				PrintCacheLine();
				break;
			default:
				printf("Invalid");
		}

		//Counters and Calculated the performance
	}
return EXIT_SUCCESS;
}
