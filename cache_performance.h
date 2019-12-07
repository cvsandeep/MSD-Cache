/*
 * counters_&_performance.h
 *
 */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
//#include "cache_operation.h"

void IReadHitCount(void);
void DReadHitCount(void);
void IReadMissCount(void);
void DReadMissCount(void);
void WriteHitCount(void);
void IWriteMissCount(void);
void DWriteMissCount(void);
void IReadCount(void);
void DReadCount(void);
void IWriteCount(void);
void DWriteCount(void);
void IHitCount(void);
void DHitCount(void);
void IMissCount(void);
void DMissCount(void);
void IReadMissEvictCount(void);
void DReadMissEvictCount(void);
void IWriteMissEvictCount(void);
void DWriteMissEvictCount(void);
void CachePerformance(void);
void IHitModifiedLineCount(void);
void DHitModifiedLineCount(void);
