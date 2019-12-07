/*
 * counters_&_performance.h
 *
 */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
//#include "cache_operation.h"

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
