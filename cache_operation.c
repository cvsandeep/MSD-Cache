/*
 * cache_operation.c
 *
 *  Created on: Nov 22, 2019
 *      Author: sandeep
 */
#include "cache_operation.h"

void UpdatePLRU(int set, int w)
{

}

int WhichWay(int set)
{
	return 1;
}

void readData(void)
{
	printf("operation READ_DATA");
}

void writeData(void)
{
	printf("operation WRITE_DATA");
}

void ReadInstruction(void)
{
	printf("operation READ_INSTRUCTION");
}

void SnoopedInvalidate(void)
{
	printf("operation SNOOPED_INVALIDATE");
}

void SnoopedRead(void)
{
	printf("operation SNOOPED_READ");
}

void SnoopedWrite(void)
{
	printf("operation SNOOPED_WRITE");
}

void SnoopedReadX(void)
{
	printf("operation SNOOPED_READ_X");
}

void ClearAndSet(void)
{
	printf("operation CLEAR_AND_RESET");
}

void PrintCacheLine(void)
{
	printf("operation PRINT_CACHE_LINE");
}
