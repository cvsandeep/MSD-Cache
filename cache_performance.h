/*
 * counters_&_performance.h
 *
 */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
//#include "cache_operation.h"

float readHitCount,readMissCount,writeHitCount,writeMissCount,readCount, writeCount, hitCount, readMissEvictCount,writeMissEvictCount,missCount,hitModifiedLineCount;
int miss_evict,hit_percentage, hit_modified_percentage,miss_evict_percentage,miss_percentage;

void ReadHitCount(void);
void ReadMissCount(void);
void WriteHitCount(void);
void WriteMissCount(void);
void ReadCount(void);
void WriteCount(void);
void HitCount(void);
void MissCount(void);
void ReadMissEvictCount(void);
void WriteMissEvictCount(void);
void CachePerformance(void);
void HitModifiedLineCount(void);
