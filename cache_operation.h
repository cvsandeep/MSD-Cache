/*
 * cache_operation.h
 *
 *  Created on: Nov 22, 2019
 *      Author: sandeep
 */

#ifndef CACHE_OPERATION_H_
#define CACHE_OPERATION_H_
#include <stdio.h>

void UpdatePLRU(int set, int w);
int WhichWay(int set);
void readData(void);
void writeData(void);
void ReadInstruction(void);
void SnoopedInvalidate(void);
void SnoopedRead(void);
void SnoopedWrite(void);
void SnoopedReadX(void);
void ClearAndSet(void);
void PrintCacheLine(void);

#endif /* CACHE_OPERATION_H_ */
