/*
 * counters_&_performance.h
 *
 */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
//#include "cache_operation.h"

void IReadCount(void);
void DReadCount(void);
void DWriteCount(void);
void IHitCount(void);
void DHitCount(void);
void IMissCount(void);
void DMissCount(void);

void HitCount(void);
void MissCount(void);
void EvictCount(void);

void parse_read_write(void);

void CachePerformance(void);

