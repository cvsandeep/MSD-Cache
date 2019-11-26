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
#include "bus_operation.h"
#include <stdio.h>
#include <math.h>

unsigned int tag, set_index, offset;
extern unsigned int cache_lines, associativity,sets,line_size;

void DecodeAddress(void){
	int lines = log2(line_size);
	int set = log2(sets);
	tag = addr; set_index = addr; offset = addr;

	offset = offset & ((1 << lines) -1);
	set_index = set_index >> lines & ((1<< set) -1);
	tag = tag >> (lines + set) & ((1<< (32-lines+set)) -1);
	printf("\n Address 0x%x ; Offset 0x%x; set_index 0x%x; tag 0x%x\n  ",addr,offset,set_index,tag);
}

void ReIntializeCache(void){
	L2.set = malloc(sizeof(struct CACHE_SET_8_WAY)*sets);
}
// Level 1
void readData(void)
{
	char msgOut[1024];
	int evict = 0, way=0;
	sprintf(msgOut, "Reading at address 0x%x\n ",addr);
	debugLog(1,__func__, msgOut);
	for(int w = 0; w < associativity; w++){
		if(L2.set[set_index].way[w].valid == 1) { //Check data is valid
			if(L2.set[set_index].way[w].tag == tag) { //Check tag
				debugLog(1,__func__, "Data found");
				UpdatePLRU(set_index,w);
				return; // Return data
			}
		} else {
			if (evict == 0) {
				evict = 1;
				way = w;
			}
		}
	}
	debugLog(1,__func__, "Data not found");

	if(evict) {
		BusOperation(READ, addr, GetSnoopResult(addr)); //Send read command to bus
		L2.set[set_index].way[way].valid = 1;
		L2.set[set_index].way[way].tag = tag;
	} else {
		way = WhichWay(set_index);
	}
	UpdatePLRU(set_index,way);
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
