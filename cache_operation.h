/*
 * cache_operation.h
 *
 *   Created on: Feb 19, 2020
 *      Author: Todd Townsend
 */

#ifndef CACHE_OPERATION_H_
#define CACHE_OPERATION_H_

#include <stdio.h>
#include <stdlib.h>
#include "logger.h"
#include "cache_control.h"
#include "cache_performance.h"

#define INVALID 0
#define SHARED 1
#define EXCLUSIVE 2
#define MODEFIED 3
#define SETS 31250

void DecodeAddress(void);
void ReIntializeCache(void);
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

void UpdateMESIstate(int type, int way);
void UpdateMESIstateSnoop(int type, int way);
void VoidWay(int way);
void Flush(int way);

#endif /* CACHE_OPERATION_H_ */
