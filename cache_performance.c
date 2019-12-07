/*
 * 	counters_&_performance.c
 *
 * 	Author: Todd
 *
 *
 */


#include "cache_performance.h"
#include "logger.h"
//#include "cache_operation.h"

char msgOut[1024];
static int readCount, writeCount;
static int readHitCount, readMissCount, writeHitCount, hitCount, readMissEvictCount, writeMissEvictCount, missCount, hitModifiedLineCount, miss_evict;
float hit_percentage, hit_modified_percentage,miss_evict_percentage,miss_percentage;
static int writeMissCount;

void ReadCount(void)
{
	++readCount;
	sprintf(msgOut, "%d",readCount);
	debugLog(PERFORMANCE, __func__, msgOut);
}

void WriteCount(void)
{
	++writeCount;
	sprintf(msgOut, "%d",writeCount);
	debugLog(PERFORMANCE, __func__, msgOut);
}

void ReadHitCount(void)
{
	++readHitCount;
	sprintf(msgOut, "%d",readHitCount);
	debugLog(PERFORMANCE, __func__, msgOut);
}

void ReadMissCount(void)
{
	++readMissCount;
	sprintf(msgOut, "%d",readMissCount);
	debugLog(PERFORMANCE, __func__, msgOut);
}

void WriteHitCount(void)
{
	++writeHitCount;
	sprintf(msgOut, "%d",writeHitCount);
	debugLog(PERFORMANCE, __func__, msgOut);
}

void WriteMissCount(void)
{
	++writeMissCount;
	sprintf(msgOut, "%d",writeMissCount);
	debugLog(PERFORMANCE, __func__, msgOut);
}

void HitCount(void)
{
	++hitCount;
	sprintf(msgOut, "%d",hitCount);
	debugLog(PERFORMANCE, __func__, msgOut);
}

void HitModifiedLineCount(void)
{
	++hitModifiedLineCount;
	sprintf(msgOut, "%d",hitModifiedLineCount);
	debugLog(PERFORMANCE, __func__, msgOut);
}

void ReadMissEvictCount(void)
{
	++readMissEvictCount;
	sprintf(msgOut, "%d",readMissEvictCount);
	debugLog(PERFORMANCE, __func__, msgOut);
}

void WriteMissEvictCount(void)
{
	++writeMissEvictCount;
	sprintf(msgOut, "%d",writeMissEvictCount);
	debugLog(PERFORMANCE, __func__, msgOut);
}
void MissCount(void)
{
	++missCount;	// = Miss + Evict
	sprintf(msgOut, "%d",missCount);
	debugLog(PERFORMANCE, __func__, msgOut);
}

void CachePerformance(void)
{
	//miss_evict = (readMissEvictCount+writeMissEvictCount);
	//hit_percentage = hitCount/(hitCount + hitModifiedLineCount + miss_evict + missCount) * 100;
	//hit_modified_percentage = hitModifiedLineCount/(hitCount + hitModifiedLineCount + miss_evict + missCount) * 100;
	//miss_evict_percentage = miss_evict/(hitCount + hitModifiedLineCount + miss_evict + missCount) * 100;
	//miss_percentage = missCount/(hitCount + hitModifiedLineCount + miss_evict + missCount) * 100;
	sprintf(msgOut,"Total Number of: Read Hits = %d, Read Misses = %d, Write Hits = %d, Write Misses = %d",(int)readHitCount,(int)readMissCount,(int)writeHitCount,(int)writeMissCount);
	debugLog(0, __func__, msgOut);
	sprintf(msgOut,"Total Number of Miss&Evict: Read Misses = %d, Write Misses = %d",(int)readMissEvictCount,(int)writeMissEvictCount);
	debugLog(0, __func__, msgOut);
	sprintf(msgOut,"Read + Write: Hits Reads + Writes = %d, Misses Reads + Writes = %d",(int)(readHitCount+readMissCount),(int)(writeMissCount+writeHitCount));
	debugLog(0, __func__, msgOut);
	sprintf(msgOut,"Total Number of Cache: Reads = %d, Writes = %d, Hits = %d, Misses = %d",(int)readCount,(int)writeCount,(int)hitCount,(int)missCount);
	debugLog(0, __func__, msgOut);
	//sprintf(msgOut, "Performance: Hits = %d Percent, HitModifiedLine = %d Percent, Miss&Evict = %d Percent, Miss = %d Percent",hit_percentage,hit_modified_percentage,miss_evict_percentage,miss_percentage);
	//debugLog(0, __func__, msgOut);
	//return 0;
}
