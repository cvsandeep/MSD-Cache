/*
 * cache_operation.h
 *
 *  Created on: Nov 22, 2019
 *      Author: sandeep
 */

#ifndef CACHE_OPERATION_H_
#define CACHE_OPERATION_H_

#include <stdio.h>
#include <stdlib.h>
#include "logger.h"
#include "cache_control.h"

unsigned int hitCount, hitEvictCount, missCount;
unsigned int hit_percentage, hit_evict_percentage, miss_percentage;
void DecodeAddress(void);
void readData(void);
void writeData(void);
void ReadInstruction(void);
void SnoopedInvalidate(void);
void SnoopedRead(void);
void SnoopedWrite(void);
void SnoopedReadX(void);
void ClearAndSet(void);
void PrintCacheLine(void);
void UpdatePLRU(int set, int w);
int WhichWay(int set);
int HitCount(void);
int MissCount(void);
int HitEvictCount(void);
int CachePerformance(void);

#endif /* CACHE_OPERATION_H_ */
