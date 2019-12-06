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

void ReadCount(void)
{
	debugLog(PERFORMANCE, __func__, "operation HIT_COUNT");
	++readCount;
}

void WriteCount(void)
{
	debugLog(PERFORMANCE, __func__, "operation HIT_COUNT");
	++writeCount;
}

void HitCount(void)
{
	++hitCount;
	sprintf(msgOut, "%lf",hitCount);
	debugLog(PERFORMANCE, __func__, msgOut);
}

void HitModifiedLineCount(void)
{
	++hitModifiedLineCount;
	sprintf(msgOut, "%lf",hitModifiedLineCount);
	debugLog(PERFORMANCE, __func__, msgOut);
}

void HitEvictCount(void)
{
	++hitEvictCount;
	sprintf(msgOut, "%lf",hitEvictCount);
	debugLog(PERFORMANCE, __func__, msgOut);
}

void MissCount(void)
{
	++missCount;
	sprintf(msgOut, "%lf",missCount);
	debugLog(PERFORMANCE, __func__, msgOut);
}

void CachePerformance(void)
{
	hit_percentage = hitCount/(hitCount + hitModifiedLineCount + hitEvictCount + missCount) * 100;
	hit_modified_percentage = hitModifiedLineCount/(hitCount + hitModifiedLineCount + hitEvictCount + missCount) * 100;
	hit_evict_percentage = hitEvictCount/(hitCount + hitModifiedLineCount + hitEvictCount + missCount) * 100;
	miss_percentage = missCount/(hitCount + hitModifiedLineCount + hitEvictCount + missCount) * 100;
	sprintf(msgOut,"Number of Cache Reads = %d, Writes = %d, Hits = %d, Misses = %d",(int)readCount,(int)writeCount,(int)(hitCount+hitModifiedLineCount+hitEvictCount),(int)missCount);
	debugLog(0, __func__, msgOut);
	sprintf(msgOut, "Performance Hits = %d Percent, HitModifiedLine = %d Percent, Hit&Evict = %d Percent, Miss = %d Percent",hit_percentage,hit_modified_percentage,hit_evict_percentage,miss_percentage);
	debugLog(0, __func__, msgOut);
	//return 0;
}
