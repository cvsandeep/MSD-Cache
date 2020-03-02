/*
 * 	counters_&_performance.c
 *   Created on: Feb 23, 2020
 *      Author: Todd Townsend
 *
 *
 */


#include "cache_performance.h"
#include "logger.h"
#include "cache_operation.h"

char msgOut[1024];

static int IreadHitCount, DreadHitCount, DwriteHitCount;
static int IreadMissCount, DreadMissCount, DwriteMissCount;
static int IreadMissEvictCount, DreadMissEvictCount, DwriteMissEvictCount;
static int IreadCount, DreadCount, DwriteCount;
int reads_parsed, writes_parsed;

/*
 * Instruction read counter
 */
void IReadCount(void)
{
	++IreadCount;
	sprintf(msgOut, "%d",IreadCount);
	debugLog(PERFORMANCE, __func__, msgOut);
}

/*
 * Data read counter
 */
void DReadCount(void)
{
	++DreadCount;
	sprintf(msgOut, "%d",DreadCount);
	debugLog(PERFORMANCE, __func__, msgOut);
}

/*
 * Data Write Counter
 */
void DWriteCount(void)
{
	++DwriteCount;
	sprintf(msgOut, "%d",DwriteCount);
	debugLog(PERFORMANCE, __func__, msgOut);
}

/*
 * Different Hit counters based on operation.
 */
void HitCount(void){
	switch(op){
		case READ_DATA:
			++DreadHitCount;
			sprintf(msgOut, "%d",DreadHitCount);
			break;
		case WRITE_DATA:
			++DwriteHitCount;
			sprintf(msgOut, "%d",DwriteHitCount);
			break;
		case READ_INSTRUCTION:
			++IreadHitCount;
			sprintf(msgOut, "%d",IreadHitCount);
			break;
	}
	debugLog(PERFORMANCE, __func__, msgOut);

}

/*
 * Different Miss counters based on operation.
 */
void MissCount(void){
	switch(op){
			case READ_DATA:
				++DreadMissCount;
				sprintf(msgOut, "%d",DreadMissCount);
				break;
			case WRITE_DATA:
				++DwriteMissCount;
				sprintf(msgOut, "%d",DwriteMissCount);
				break;
			case READ_INSTRUCTION:
				++IreadMissCount;
				sprintf(msgOut, "%d",IreadMissCount);
				break;
		}
		debugLog(PERFORMANCE, __func__, msgOut);
}

/*
 * Different Evict counters based on operation.
 */
void EvictCount(void){
	switch(op){
			case READ_DATA:
				++DreadMissEvictCount;
				sprintf(msgOut, "%d",DreadMissEvictCount);
				break;
			case WRITE_DATA:
				++DwriteMissEvictCount;
				sprintf(msgOut, "%d",DwriteMissEvictCount);
				break;
			case READ_INSTRUCTION:
				++IreadMissEvictCount;
				sprintf(msgOut, "%d",IreadMissEvictCount);
				break;
		}
		debugLog(PERFORMANCE, __func__, msgOut);
}

/*
 * Reopens the trace file for validating read and write counts
 */
void parse_read_write(void){
	while(UpdateTraceOperation()){
		if(op == 0 || op == 2)
			++reads_parsed;
		else if(op == 1)
			++writes_parsed;
	}
}

/*
 * Calculates various counts and performance percentages
 *
 */
void CachePerformance(void)
{
	int TotalHitCount = IreadHitCount + DreadHitCount + DwriteHitCount;
	int ToatalMissCount = IreadMissCount + DreadMissCount + DwriteMissCount;
	int TotalEvictMissCount = IreadMissEvictCount + DreadMissEvictCount + DwriteMissEvictCount;
	int TotalReadOperations = IreadCount + DreadCount;
	int TotalWriteOperations = DwriteCount;
	int TotalOperations = IreadCount + DreadCount + DwriteCount;

	float hit_percentage = (TotalHitCount/(1.0*TotalOperations))*100;
	float miss_percentage = (ToatalMissCount/(1.0*TotalOperations))*100;
	float missEvict_percentage = (TotalEvictMissCount/(1.0*TotalOperations))*100;

	debugLog(0, __func__, "");
	parse_read_write();
	if(reads_parsed == TotalReadOperations){
		sprintf(msgOut,"Total Number of Reads	      = %d",TotalReadOperations);
		debugLog(0, __func__, msgOut);
	}
	else{
		sprintf(msgOut,"Total Number of Parsed Reads not equal to Read Operations");
		debugLog(0, __func__, msgOut);
		sprintf(msgOut,"Total Number of Reads = %d",TotalReadOperations);
		debugLog(0, __func__, msgOut);
		sprintf(msgOut,"Total Parsed Reads = %d",reads_parsed);
		debugLog(0, __func__, msgOut);
	}

	if(writes_parsed == TotalWriteOperations){
		sprintf(msgOut,"Total Number of Writes	      = %d",TotalWriteOperations);
		debugLog(0, __func__, msgOut);
	}
	else{
		sprintf(msgOut,"Total Number of Parsed Writes not equal to Write Operations");
		debugLog(0, __func__, msgOut);
		sprintf(msgOut,"Total Number of Writes   = %d",TotalWriteOperations);
		debugLog(0, __func__, msgOut);
		sprintf(msgOut,"Total Parsed Write = %d",writes_parsed);
		debugLog(0, __func__, msgOut);
	}

	sprintf(msgOut,"Total Number Cache Accesses  = %d",(TotalHitCount + ToatalMissCount+TotalEvictMissCount));
	debugLog(0, __func__, msgOut);

	sprintf(msgOut,"Total Number of Cache hits   = %d",TotalHitCount);
	debugLog(0, __func__, msgOut);

	sprintf(msgOut,"Total Number of Cache misses = %d",(ToatalMissCount+TotalEvictMissCount));
	debugLog(0, __func__, msgOut);

	sprintf(msgOut,"Cache Hit ratio              = %03.02f%c",hit_percentage,'%');
	debugLog(0, __func__, msgOut);
	sprintf(msgOut,"Cache Miss ratio             = %03.02f%c",(missEvict_percentage + miss_percentage),'%');
	debugLog(0, __func__, msgOut);
	debugLog(0, __func__, "");

	sprintf(msgOut,"\t ReadI \t ReadD \t Write \t TOTAL");
	debugLog(0, __func__, msgOut);

	sprintf(msgOut,"HITS :\t %d %d \t %d \t %d (%03.02f%c)", IreadHitCount, DreadHitCount, DwriteHitCount, TotalHitCount,hit_percentage,'%');
	debugLog(0, __func__, msgOut);


	sprintf(msgOut,"MISS :\t %d \t %d \t %d \t %d \t (%03.02f%c)", IreadMissCount, DreadMissCount, DwriteMissCount,ToatalMissCount, miss_percentage,'%');
	debugLog(0, __func__, msgOut);

	sprintf(msgOut,"EVICT:\t %d \t %d \t %d \t %d \t (%03.02f%c)", IreadMissEvictCount, DreadMissEvictCount, DwriteMissEvictCount,TotalEvictMissCount,missEvict_percentage,'%');
	debugLog(0, __func__, msgOut);


	sprintf(msgOut,"TOTAL:\t %d %d \t %d \t %d", IreadCount, DreadCount, DwriteCount,TotalOperations);
	debugLog(0, __func__, msgOut);

	float AMAT = (hit_percentage/100.0) * 5 + ((miss_percentage+missEvict_percentage)/100.0) * 100;
	debugLog(0, __func__, "If we assume Hit time is 5 cycles & Miss time is 100 Cycles");
	sprintf(msgOut,"Average Memory Access Time(AMAT) = %f cycles",AMAT);
	debugLog(0, __func__, msgOut);



	return;
}
