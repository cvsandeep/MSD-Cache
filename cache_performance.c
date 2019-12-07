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
static int IreadCount, DreadCount, IwriteCount, DwriteCount, IwriteMissCount,DwriteMissCount;;
static int IreadHitCount, DreadHitCount, IreadMissCount, DreadMissCount,IwriteHitCount, DwriteHitCount,IhitCount, DhitCount, IreadMissEvictCount, DreadMissEvictCount, IwriteMissEvictCount, DwriteMissEvictCount, ImissCount, DmissCount, IhitModifiedLineCount, DhitModifiedLineCount, Imiss_evict, Dmiss_evict;
float hit_percentage, hit_modified_percentage,miss_evict_percentage,miss_percentage;
static int writeMissCount;

void IReadCount(void)
{
	++IreadCount;
	sprintf(msgOut, "%d",IreadCount);
	debugLog(PERFORMANCE, __func__, msgOut);
}

void DReadCount(void)
{
	++DreadCount;
	sprintf(msgOut, "%d",DreadCount);
	debugLog(PERFORMANCE, __func__, msgOut);
}

void IWriteCount(void)
{
	++IwriteCount;
	sprintf(msgOut, "%d",IwriteCount);
	debugLog(PERFORMANCE, __func__, msgOut);
}

void DWriteCount(void)
{
	++DwriteCount;
	sprintf(msgOut, "%d",DwriteCount);
	debugLog(PERFORMANCE, __func__, msgOut);
}

void IReadHitCount(void)
{
	++IreadHitCount;
	sprintf(msgOut, "%d",IreadHitCount);
	debugLog(PERFORMANCE, __func__, msgOut);
}

void DReadHitCount(void)
{
	++DreadHitCount;
	sprintf(msgOut, "%d",DreadHitCount);
	debugLog(PERFORMANCE, __func__, msgOut);
}

void IReadMissCount(void)
{
	++IreadMissCount;
	sprintf(msgOut, "%d",IreadMissCount);
	debugLog(PERFORMANCE, __func__, msgOut);
}

void DReadMissCount(void)
{
	++DreadMissCount;
	sprintf(msgOut, "%d",DreadMissCount);
	debugLog(PERFORMANCE, __func__, msgOut);
}
void IWriteHitCount(void)
{
	++IwriteHitCount;
	sprintf(msgOut, "%d",IwriteHitCount);
	debugLog(PERFORMANCE, __func__, msgOut);
}

void DWriteHitCount(void)
{
	++DwriteHitCount;
	sprintf(msgOut, "%d",DwriteHitCount);
	debugLog(PERFORMANCE, __func__, msgOut);
}

void IWriteMissCount(void)
{
	++IwriteMissCount;
	sprintf(msgOut, "%d",IwriteMissCount);
	debugLog(PERFORMANCE, __func__, msgOut);
}

void DWriteMissCount(void)
{
	++DwriteMissCount;
	sprintf(msgOut, "%d",DwriteMissCount);
	debugLog(PERFORMANCE, __func__, msgOut);
}

void IHitCount(void)
{
	++IhitCount;
	sprintf(msgOut, "%d",IhitCount);
	debugLog(PERFORMANCE, __func__, msgOut);
}

void DHitCount(void)
{
	++DhitCount;
	sprintf(msgOut, "%d",DhitCount);
	debugLog(PERFORMANCE, __func__, msgOut);
}

void IHitModifiedLineCount(void)
{
	++IhitModifiedLineCount;
	sprintf(msgOut, "%d",IhitModifiedLineCount);
	debugLog(PERFORMANCE, __func__, msgOut);
}

void DHitModifiedLineCount(void)
{
	++DhitModifiedLineCount;
	sprintf(msgOut, "%d",DhitModifiedLineCount);
	debugLog(PERFORMANCE, __func__, msgOut);
}

void IReadMissEvictCount(void)
{
	++IreadMissEvictCount;
	sprintf(msgOut, "%d",IreadMissEvictCount);
	debugLog(PERFORMANCE, __func__, msgOut);
}

void DReadMissEvictCount(void)
{
	++DreadMissEvictCount;
	sprintf(msgOut, "%d",DreadMissEvictCount);
	debugLog(PERFORMANCE, __func__, msgOut);
}

void IWriteMissEvictCount(void)
{
	++IwriteMissEvictCount;
	sprintf(msgOut, "%d",IwriteMissEvictCount);
	debugLog(PERFORMANCE, __func__, msgOut);
}

void DWriteMissEvictCount(void)
{
	++DwriteMissEvictCount;
	sprintf(msgOut, "%d",DwriteMissEvictCount);
	debugLog(PERFORMANCE, __func__, msgOut);
}

void IMissCount(void)
{
	++ImissCount;	// = Miss + Evict
	sprintf(msgOut, "%d",ImissCount);
	debugLog(PERFORMANCE, __func__, msgOut);
}

void DMissCount(void)
{
	++DmissCount;	// = Miss + Evict
	sprintf(msgOut, "%d",DmissCount);
	debugLog(PERFORMANCE, __func__, msgOut);
}

void CachePerformance(void)
{
	Imiss_evict = (IreadMissEvictCount+IwriteMissEvictCount);
	Dmiss_evict = (IreadMissEvictCount+IwriteMissEvictCount);
	//hit_percentage = hitCount/(hitCount + hitModifiedLineCount + miss_evict + missCount) * 100;
	//hit_modified_percentage = hitModifiedLineCount/(hitCount + hitModifiedLineCount + miss_evict + missCount) * 100;
	//miss_evict_percentage = miss_evict/(hitCount + hitModifiedLineCount + miss_evict + missCount) * 100;
	//miss_percentage = missCount/(hitCount + hitModifiedLineCount + miss_evict + missCount) * 100;
	//sprintf(msgOut,"Total Number of: Read Hits = %d, Read Misses = %d, Write Hits = %d, Write Misses = %d",(int)readHitCount,(int)readMissCount,(int)writeHitCount,(int)writeMissCount);
	//debugLog(0, __func__, msgOut);
	//sprintf(msgOut,"Total Number of Miss&Evict: Read Misses = %d, Write Misses = %d",(int)readMissEvictCount,(int)writeMissEvictCount);
	//debugLog(0, __func__, msgOut);
	//sprintf(msgOut,"Read + Write: Hits Reads + Writes = %d, Misses Reads + Writes = %d",(int)(readHitCount+readMissCount),(int)(writeMissCount+writeHitCount));
	//debugLog(0, __func__, msgOut);
	//sprintf(msgOut,"Total Number of Cache: Reads = %d, Writes = %d, Hits = %d, Misses = %d",(int)readCount,(int)writeCount,(int)hitCount,(int)missCount);
	//debugLog(0, __func__, msgOut);
	//sprintf(msgOut, "Performance: Hits = %d Percent, HitModifiedLine = %d Percent, Miss&Evict = %d Percent, Miss = %d Percent",hit_percentage,hit_modified_percentage,miss_evict_percentage,miss_percentage);
	//debugLog(0, __func__, msgOut);
	//return 0;
}
