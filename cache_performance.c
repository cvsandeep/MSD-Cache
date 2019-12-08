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

static int IhitCount,DhitCount,ImissCount,DmissCount;

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

void IHitCount(void)
{
	++IhitCount;
	sprintf(msgOut, "%d",IhitCount);
	debugLog(PERFORMANCE, __func__, msgOut);
}

void DHitCount(void)
{
	++DhitCount;
	sprintf(msgOut, "%d",DhitCount);
	debugLog(PERFORMANCE, __func__, msgOut);
}

void IMissCount(void)
{
	++ImissCount;	// = Miss + Evict
	sprintf(msgOut, "%d",ImissCount);
	debugLog(PERFORMANCE, __func__, msgOut);
}

void DMissCount(void)
{
	++DmissCount;	// = Miss + Evict
	sprintf(msgOut, "%d",DmissCount);
	debugLog(PERFORMANCE, __func__, msgOut);
}

void CachePerformance(void)
{
	//Imiss_evict = (IreadMissEvictCount+IwriteMissEvictCount);
	//Dmiss_evict = (IreadMissEvictCount+IwriteMissEvictCount);
	//hit_percentage = hitCount/(hitCount + hitModifiedLineCount + miss_evict + missCount) * 100;
	//hit_modified_percentage = hitModifiedLineCount/(hitCount + hitModifiedLineCount + miss_evict + missCount) * 100;
	//miss_evict_percentage = miss_evict/(hitCount + hitModifiedLineCount + miss_evict + missCount) * 100;
	//miss_percentage = missCount/(hitCount + hitModifiedLineCount + miss_evict + missCount) * 100;
	//sprintf(msgOut,"Total Number of: Read Hits = %d, Read Misses = %d, Write Hits = %d, Write Misses = %d",(int)readHitCount,(int)readMissCount,(int)writeHitCount,(int)writeMissCount);
	//debugLog(0, __func__, msgOut);
	//sprintf(msgOut,"Total Number of Miss&Evict: Read Misses = %d, Write Misses = %d",(int)readMissEvictCount,(int)writeMissEvictCount);
	//debugLog(0, __func__, msgOut);
	//sprintf(msgOut,"Read + Write: Hits Reads + Writes = %d, Misses Reads + Writes = %d",(int)(readHitCount+readMissCount),(int)(writeMissCount+writeHitCount));
	//debugLog(0, __func__, msgOut);
	//sprintf(msgOut,"Total Number of Cache: Reads = %d, Writes = %d, Hits = %d, Misses = %d",(int)readCount,(int)writeCount,(int)hitCount,(int)missCount);
	//debugLog(0, __func__, msgOut);
	//sprintf(msgOut, "Performance: Hits = %d Percent, HitModifiedLine = %d Percent, Miss&Evict = %d Percent, Miss = %d Percent",hit_percentage,hit_modified_percentage,miss_evict_percentage,miss_percentage);
	//debugLog(0, __func__, msgOut);
	sprintf(msgOut,"\t ReadI \t ReadD \t Write \t TOTAL");
	debugLog(0, __func__, msgOut);
	sprintf(msgOut,"HITS :\t %d \t %d \t %d \t %d", IreadHitCount, DreadHitCount, DwriteHitCount, (IreadHitCount + DreadHitCount + DwriteHitCount));
	debugLog(0, __func__, msgOut);
	sprintf(msgOut,"MISS :\t %d \t %d \t %d \t %d", IreadMissCount, DreadMissCount, DwriteMissCount,(IreadMissCount + DreadMissCount + DwriteMissCount + IreadMissEvictCount + DreadMissEvictCount + DwriteMissEvictCount));
	debugLog(0, __func__, msgOut);
	sprintf(msgOut,"EVICT:\t %d \t %d \t %d", IreadMissEvictCount, DreadMissEvictCount, DwriteMissEvictCount);
	debugLog(0, __func__, msgOut);
	sprintf(msgOut,"TOTAL:\t %d \t %d \t %d \t %d", IreadCount, DreadCount, DwriteCount,(IreadCount + DreadCount + DwriteCount));
	debugLog(0, __func__, msgOut);
	sprintf(msgOut,"IhitCount=%d, DhitCount=%d, ImissCount=%d, DmissCount=%d",IhitCount,DhitCount,ImissCount,DmissCount);
	debugLog(0, __func__, msgOut);

	// Hit Percentage = hits/read+write
	// Miss Percentage = misses/read+write



	return;
}
