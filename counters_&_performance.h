/*
 *
 *
 */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "cache_operation.h"

unsigned int hitCount, hitEvictCount, missCount,hitModifiedLineCount;
unsigned int hit_percentage, hit_modified_percentage,hit_evict_percentage, miss_percentage;

void HitCount(void);
void MissCount(void);
void HitEvictCount(void);
int CachePerformance(void);
void HitModifiedLineCount(void);
