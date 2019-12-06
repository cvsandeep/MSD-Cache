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

void HitCount(void)
{
	++hitCount;
	sprintf(msgOut, "%d",hitCount);
	debugLog(1, __func__, msgOut);
}

void HitModifiedLineCount(void)
{
	++hitModifiedLineCount;
	sprintf(msgOut, "%d",hitModifiedLineCount);
	debugLog(1, __func__, msgOut);
}

void HitEvictCount(void)
{
	++hitEvictCount;
	sprintf(msgOut, "%d",hitEvictCount);
	debugLog(1, __func__, msgOut);
}

void MissCount(void)
{
	++missCount;
	sprintf(msgOut, "%d",missCount);
	debugLog(1, __func__, msgOut);
}

void CachePerformance(void)
{
	hit_percentage = hitCount/(hitCount + hitModifiedLineCount + hitEvictCount + missCount) * 100;
	hit_modified_percentage = hitModifiedLineCount/(hitCount + hitModifiedLineCount + hitEvictCount + missCount) * 100;
	hit_evict_percentage = hitEvictCount/(hitCount + hitModifiedLineCount + hitEvictCount + missCount) * 100;
	miss_percentage = missCount/(hitCount + hitModifiedLineCount + hitEvictCount + missCount) * 100;
	sprintf(msgOut, "Performance Hits = %d Percent, HitModifiedLine = %d Percent, Hit&Evict = %d Percent, Miss = %d Percent\n",hit_percentage,hit_modified_percentage,hit_evict_percentage,miss_percentage);
	debugLog(1, __func__, msgOut);
	//return 0;
}
