/*
 * counters_&_performance.h
 *
 */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
//#include "cache_operation.h"

int hitCount, hitEvictCount, missCount,hitModifiedLineCount;
int hit_percentage, hit_modified_percentage,hit_evict_percentage, miss_percentage;

void HitCount(void);
void MissCount(void);
void HitEvictCount(void);
void CachePerformance(void);
void HitModifiedLineCount(void);
