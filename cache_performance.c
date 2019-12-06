/*
 * 	counters_&_performance.c
 *
 * 	Author: Todd
 *
 *
 */


#include "cache_performance.h"

#include "cache_operation.h"

void HitCount(void)
{
	debugLog(1, __func__, "operation HIT_COUNT");
	++hitCount;
}

void HitModifiedLineCount(void)
{
	debugLog(1, __func__, "operation HIT_COUNT");
	++hitModifiedLineCount;
}

void HitEvictCount(void)
{
	debugLog(1, __func__, "operation HIT_COUNT");
	++hitEvictCount;
}

void MissCount(void)
{
	debugLog(1, __func__, "operation MISS_COUNT");
	++missCount;
	//printf("miss count = %d",missCount);
}

void CachePerformance(void)
{
	debugLog(1, __func__, "operation CACHE_PREFORMANCE");
	hit_percentage = hitCount/(hitCount + hitModifiedLineCount + hitEvictCount + missCount) * 100;
	hit_modified_percentage = hitModifiedLineCount/(hitCount + hitModifiedLineCount + hitEvictCount + missCount) * 100;
	hit_evict_percentage = hitEvictCount/(hitCount + hitModifiedLineCount + hitEvictCount + missCount) * 100;
	miss_percentage = missCount/(hitCount + hitModifiedLineCount + hitEvictCount + missCount) * 100;
	printf("Performance Hits = %d Percent, HitModifiedLine = %d Percent, Hit&Evict = %d Percent, Miss = %d Percent\n",hit_percentage,hit_modified_percentage,hit_evict_percentage,miss_percentage);
	//return 0;
}
