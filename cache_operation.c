/*
 * cache_operation.c
 *
 *  Created on: Nov 22, 2019
 *      Author: sandeep
 */
/*
 * 00 - Bus Operations
 * 01 - Cache Operations
 * 02 - Cache Internal Operations
 * 03 - Control Operations
 * 04 - Cache Line Print
 * 05 - Cache File
 * 06 - Cache File + Print
 * 07 - Counter Print
 * 08 - Counter File
 * 09 - Counter File + Print
 * 10 - ALL
 */

#include "cache_operation.h"
#include "logger.h"

void UpdatePLRU(int set, int w)
{

}

int WhichWay(int set)
{
	return 1;
}
// Level 1
void readData(void)
{
	debugLog(0,__func__,"                      operation READ_DATA");
	//printf("operation READ_DATA");
}

void writeData(void)
{
	debugLog(0,__func__,"                     operation WRITE_DATA");
	//printf("operation WRITE_DATA");
}

void ReadInstruction(void)
{
	debugLog(1,__func__,"               operation READ_INSTRUCTION");
	//printf("operation READ_INSTRUCTION");
}

void SnoopedInvalidate(void)
{
	debugLog(2, __func__, "           operation SNOOPED_INVALIDATE");
	//printf("operation SNOOPED_INVALIDATE");
}

void SnoopedRead(void)
{
	debugLog(2, __func__, "                 operation SNOOPED_READ");
	//printf("operation SNOOPED_READ");
}

void SnoopedWrite(void)
{
	debugLog(2, __func__, "                operation SNOOPED_WRITE");
	//printf("operation SNOOPED_WRITE");
}

void SnoopedReadX(void)
{
	debugLog(2, __func__, "               operation SNOOPED_READ_X");
	//printf("operation SNOOPED_READ_X");
}

void ClearAndSet(void)
{
	debugLog(2, __func__, "               operation CLEAR_AND_RESET");
	//printf("operation CLEAR_AND_RESET");
}

void PrintCacheLine(void)
{
	debugLog(2, __func__, "              operation PRINT_CACHE_LINE");
	//printf("operation PRINT_CACHE_LINE");
}
