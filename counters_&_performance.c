/*
 * 	counters_&_performance.c
 *
 * 	Author: Todd
 *
 *
 */


#include "counters_&_performance.h"

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
}

int CachePerformance(void)
{
	debugLog(1, __func__, "operation CACHE_PREFORMANCE");
	hit_percentage = (hitCount + hitModifiedLineCount + hitEvictCount + missCount)/hitCount;
	hit_modified_percentage = (hitCount + hitModifiedLineCount + hitEvictCount + missCount)/hitModifiedLineCount;
	hit_evict_percentage = (hitCount + hitModifiedLineCount + hitEvictCount + missCount)/hitEvictCount;
	miss_percentage = (hitCount + hitModifiedLineCount + hitEvictCount + missCount)/missCount;
	printf("Performance Hits = %d Percent, HitModifiedLine = %d Percent, Hit&Evict = %d Percent, Miss = %d Percent\n",hit_percentage,hit_modified_percentage,hit_evict_percentage,miss_percentage);
	return 0;
}
