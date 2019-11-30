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
#include <math.h>
#include "cache_operation.h"

extern FILE *trace_file, *config_file;
extern unsigned int op;

int main(int argc ,char *argv[]) {
	debugLog(0, "Function Name", "Messages\n");
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
	printf("Debug level is %d\n",debug);
	//L2.set->way = malloc(sizeof(struct  CACHE_LINE) * associativity);
	//L2.set->PLRU = malloc(sizeof(struct  int) *7);
	L2.set = malloc(sizeof(struct CACHE_SET_8_WAY)*sets);
	//Info to use structures
	//struct CACHE_LINE w0[4];
	//Iterate through ways from 0 t0 sizeof(w0)/sizeof(struct CACHE_LINE)
	//printf("Number of CACHE_LINE=%d",sizeof(w0)/sizeof(struct CACHE_LINE));
	//printf("Number of offsets in CACHE_LINE=%d",sizeof(w0[0].offset)/sizeof(int));

	while(UpdateTraceOperation()){
		DecodeAddress();
		switch (op) {
			case READ_DATA:
				readData();
				break;
			case WRITE_DATA:
				writeData();
				break;
			case READ_INSTRUCTION:
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
	//Counters and Calculate the performance
	int HitCount(void)
	{
		debugLog(1, __func__, "operation HIT_COUNT");
		++hitCount;
		return hitCount;
	}
	int HitEvictCount(void)
	{
		debugLog(1, __func__, "operation HIT_COUNT");
		++hitEvictCount;
		return hitEvictCount;
	}
	int MissCount(void)
	{
		debugLog(1, __func__, "operation MISS_COUNT");
		++missCount;
		return missCount;
	}
	int CachePerformance(void)
	{
		debugLog(1, __func__, "operation CACHE_PREFORMANCE");
		hit_percentage = (hitCount + hitEvictCount + missCount)/hitCount;
		hit_evict_percentage = (hitCount + hitEvictCount + missCount)/hitEvictCount;
		miss_percentage = (hitCount + hitEvictCount + missCount)/missCount;
		printf("Performance Hits = %d, Hit&Evict = %d, Miss = %d\n",hit_percentage,hit_evict_percentage,miss_percentage);
		return 0;
	}
	return EXIT_SUCCESS;
}
