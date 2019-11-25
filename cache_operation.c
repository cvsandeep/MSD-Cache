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
#include <stdio.h>
#include <math.h>

unsigned int tag, set_index, offset;

void DecodeAddress(void){
	int lines = log2(line_size);
	int sets = log2(cache_lines/associativity);
	tag = addr; set_index = addr; offset = addr;

	offset = offset & ((1 << lines) -1);
	set_index = set_index >> lines & ((1<< sets) -1);
	tag = tag >> (lines + sets) & ((1<< (32-lines+sets)) -1);
	printf("\n Address 0x%x ; Offset 0x%x; set_index 0x%x; tag 0x%x\n  ",addr,offset,set_index,tag);
}

// Level 1
void readData(void)
{
	char msgOut[1024];
	sprintf(msgOut, "Reading at address 0x%x\n ",addr);
	debugLog(1,__func__, msgOut);
}

void writeData(void)
{
	debugLog(1,__func__,"operation WRITE_DATA");
}

void ReadInstruction(void)
{
	debugLog(1,__func__,"operation READ_INSTRUCTION");
}

void SnoopedInvalidate(void)
{
	debugLog(2, __func__, "operation SNOOPED_INVALIDATE");
}

void SnoopedRead(void)
{
	debugLog(2, __func__, "operation SNOOPED_READ");
}

void SnoopedWrite(void)
{
	debugLog(2, __func__, "operation SNOOPED_WRITE");
}

void SnoopedReadX(void)
{
	debugLog(2, __func__, "operation SNOOPED_READ_X");
}

void ClearAndSet(void)
{
	debugLog(2, __func__, "operation CLEAR_AND_RESET");
}

void PrintCacheLine(void)
{
	debugLog(2, __func__, "operation PRINT_CACHE_LINE");
}


void UpdatePLRU(int set, int w)
{

}

int WhichWay(int set)
{
	return 1;
}
