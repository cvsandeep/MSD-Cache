/*
 * 	counters_&_performance.c
 *
 * 	Author: Todd
 *
 *
 */


#include "cache_performance.h"
#include "logger.h"
#include "cache_operation.h"

char msgOut[1024];
//static int IreadCount, DreadCount, IwriteCount, DwriteCount, IwriteMissCount,DwriteMissCount;;
//static int IreadHitCount, DreadHitCount, IreadMissCount, DreadMissCount,IwriteHitCount, DwriteHitCount,IhitCount, DhitCount, IreadMissEvictCount, DreadMissEvictCount, IwriteMissEvictCount, DwriteMissEvictCount, ImissCount, DmissCount, IhitModifiedLineCount, DhitModifiedLineCount, Imiss_evict, Dmiss_evict;
//float hit_percentage, hit_modified_percentage,miss_evict_percentage,miss_percentage;
//static int writeMissCount;

static int IreadHitCount, DreadHitCount, DwriteHitCount;
static int IreadMissCount, DreadMissCount, DwriteMissCount;
static int IreadMissEvictCount, DreadMissEvictCount, DwriteMissEvictCount;
static int IreadCount, DreadCount, DwriteCount;

void IReadCount(void)
{
	++IreadCount;
	sprintf(msgOut, "%d",IreadCount);
	debugLog(PERFORMANCE, __func__, msgOut);
}

void DReadCount(void)
{
	++DreadCount;
	sprintf(msgOut, "%d",DreadCount);
	debugLog(PERFORMANCE, __func__, msgOut);
}

void DWriteCount(void)
{
	++DwriteCount;
	sprintf(msgOut, "%d",DwriteCount);
	debugLog(PERFORMANCE, __func__, msgOut);
}

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

void CachePerformance(void)
{
	sprintf(msgOut,"\t ReadI \t ReadD \t Write \t TOTAL");
	debugLog(0, __func__, msgOut);
	int TotalHitCount = IreadHitCount + DreadHitCount + DwriteHitCount;
	int ToatalMissCount = IreadMissCount + DreadMissCount + DwriteMissCount;
	int TotalEvictMissCount = IreadMissEvictCount + DreadMissEvictCount + DwriteMissEvictCount;
	int TotalOperations = IreadCount + DreadCount + DwriteCount;

	float hit_percentage = (TotalHitCount/(1.0*TotalOperations))*100;
	float miss_percentage = (ToatalMissCount/(1.0*TotalOperations))*100;
	float missEvict_percentage = (TotalEvictMissCount/(1.0*TotalOperations))*100;

	sprintf(msgOut,"HITS :\t %d \t %d \t %d \t %d \t (%03.02f%c)", IreadHitCount, DreadHitCount, DwriteHitCount, TotalHitCount,hit_percentage,'%');
	debugLog(0, __func__, msgOut);


	sprintf(msgOut,"MISS :\t %d \t %d \t %d \t %d \t (%03.02f%c)", IreadMissCount, DreadMissCount, DwriteMissCount,ToatalMissCount, miss_percentage,'%');
	debugLog(0, __func__, msgOut);

	sprintf(msgOut,"EVICT:\t %d \t %d \t %d \t %d \t (%03.02f%c)", IreadMissEvictCount, DreadMissEvictCount, DwriteMissEvictCount,TotalEvictMissCount,missEvict_percentage,'%');
	debugLog(0, __func__, msgOut);


	sprintf(msgOut,"TOTAL:\t %d \t %d \t %d \t %d", IreadCount, DreadCount, DwriteCount,TotalOperations);
	debugLog(0, __func__, msgOut);

	float AMAT = (hit_percentage/100.0) * 5 + ((miss_percentage+missEvict_percentage)/100.0) * 100;
	debugLog(0, __func__, "If we assume Hit time is 5 cycles & Miss time is 100 Cycles");
	sprintf(msgOut,"Average Memory Access Time(AMAT) = %f cycles",AMAT);
	debugLog(0, __func__, msgOut);

	return;
}
