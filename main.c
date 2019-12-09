/******************************************
 ********* ECE 485/585 Final Project ******
 ********* Simulate L2 unified cache ******
 * main .c
 * 
 *  Author: Team 2
 *
 *
 ******************************************/

#include <stdio.h>
//#include <math.h>
#include "cache_operation.h"
#include "cache_performance.h"

/*
 * External variables which are controlled in main.
 */
extern FILE *trace_file, *config_file;
extern unsigned int op;

/*
 * Main project call
 */
int main(int argc ,char *argv[]) {
	//debugLog(0, "Function Name", "Messages\n");
	if (argc < 2) {
		debugLog(0, __func__, "Wrong number of arguments:\n Please provide the file paths for trace file and config file\n");
		exit(EXIT_FAILURE);
	}

	trace_file = fopen(argv[1],"r");
	if (trace_file == 0) {
		debugLog(0, __func__, "Wrong Trace file path. Exiting ..\n");
		exit(EXIT_FAILURE);
	}
	config_file = fopen(argv[2],"r");
	if (config_file == 0) {
		debugLog(0, __func__, "Wrong config file path. Exiting ..\n");
		exit(EXIT_FAILURE);
	}

	UpdateConfig();
	ReIntializeCache();

	while(UpdateTraceOperation()){
		DecodeAddress();
		switch (op) {
			case READ_DATA:
				readData();
				DReadCount();	//Count Reads
				break;
			case WRITE_DATA:
				writeData();
				DWriteCount();	//Count Writes
				break;
			case READ_INSTRUCTION:
				IReadCount();
				ReadInstruction();
				break;
			case SNOOPED_INVALIDATE:
				SnoopedInvalidate();
				break;
			case SNOOPED_READ:
				SnoopedRead();
				break;
			case SNOOPED_WRITE:
				SnoopedWrite();
				break;
			case SNOOPED_READ_X:
				SnoopedReadX();
				break;
			case CLEAR_AND_RESET:
				ClearAndSet();
				break;
			case PRINT_CACHE_LINE:
				PrintCacheLine();
				break;
			default:
				printf("Invalid");
		}

	}
	trace_file = fopen(argv[1],"r");
	CachePerformance();		//function call to Performance report
	return EXIT_SUCCESS;
}
