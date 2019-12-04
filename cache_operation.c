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
	int evict = 1, way=0;
	sprintf(msgOut, "Reading at address 0x%x\n ",addr);
	debugLog(1,__func__, msgOut);
	for(int w = 0; w < associativity; w++){
		if(L2.set[set_index].way[w].valid == 1) { //Check data is valid
			if(L2.set[set_index].way[w].tag == tag) { //Check tag
				debugLog(1,__func__, "Data found");
				UpdatePLRU(set_index,w);
				if(op == WRITE_DATA)
					UpdateMESIstate(RWIM, w);
				else
					UpdateMESIstate(READ, w);
				return;
			}
		} else {
			if (evict == 1) {
				evict = 0;
				way = w;
			}
		}
	}
	debugLog(1,__func__, "Data not found");

	if(evict) {
		way = WhichWay(set_index);
	}
	L2.set[set_index].way[way].valid = 1;
	L2.set[set_index].way[way].tag = tag;
	UpdateMESIstate(READ, way);

	UpdatePLRU(set_index,way);
}

void writeData(void)
{
	char msgOut[1024];
	int w;
	debugLog(1,__func__,"operation WRITE_DATA");
	debugLog(1,__func__, msgOut);
	for(w = 0; w < associativity; w++){
		if(L2.set[set_index].way[w].valid == 1) { //Check data is valid
			if(L2.set[set_index].way[w].tag == tag) { //Check tag
				debugLog(1,__func__, "Data found");
				break; // Return data
			}
		}
	}
	if ( w == associativity){
		readData();
	} else {
		UpdatePLRU(set_index,w);
		UpdateMESIstate(WRITE, w);
	}
	// PutSnoopResult
}

void ReadInstruction(void)
{
	debugLog(1,__func__,"operation READ_INSTRUCTION");
	readData();
}

void SnoopedInvalidate(void)
{
	debugLog(2, __func__, "operation SNOOPED_INVALIDATE");
	for(int w = 0; w < associativity; w++){
		if(L2.set[set_index].way[w].valid == 1) { //Check data is valid
			if(L2.set[set_index].way[w].tag == tag) { //Check tag
				debugLog(1,__func__, "Data found");
				UpdateMESIstateSnoop(INVALIDATE,w);
				//UpdatePLRU(set_index,w);
				return; // Return data
			}
		}
	}
}

void SnoopedRead(void)
{
	debugLog(2, __func__, "operation SNOOPED_READ");
	for(int w = 0; w < associativity; w++){
		if(L2.set[set_index].way[w].valid == 1) { //Check data is valid
			if(L2.set[set_index].way[w].tag == tag) { //Check tag
				debugLog(1,__func__, "Data found");
				UpdateMESIstateSnoop(READ,w);
				//UpdatePLRU(set_index,w);
				return; // Return data
			}
		}
	}
}

void SnoopedWrite(void)
{
	debugLog(2, __func__, "operation SNOOPED_WRITE");
	for(int w = 0; w < associativity; w++){
		if(L2.set[set_index].way[w].valid == 1) { //Check data is valid
			if(L2.set[set_index].way[w].tag == tag) { //Check tag
				debugLog(1,__func__, "Data found");
				UpdateMESIstateSnoop(WRITE,w); // No need as there are no any operations for write.
				//UpdatePLRU(set_index,w);
				return; // Return data
			}
		}
	}
}

void SnoopedReadX(void)
{
	debugLog(2, __func__, "operation SNOOPED_READ_X");
	for(int w = 0; w < associativity; w++){
		if(L2.set[set_index].way[w].valid == 1) { //Check data is valid
			if(L2.set[set_index].way[w].tag == tag) { //Check tag
				debugLog(1,__func__, "Data found");
				L2.set[set_index].way[w].valid = 0; //Invalidating
				UpdateMESIstateSnoop(RWIM,w);
				//UpdatePLRU(set_index,w);
				return; // Return data
			}
		}
	}
}

void ClearAndSet(void)
{
	debugLog(2, __func__, "operation CLEAR_AND_RESET");
	for (int set = 0; set < sets; set++)
	for(int w = 0; w < associativity; w++){
		L2.set[set].way[w].valid = 0; //Clearing all
		L2.set[set].way[w].MESI_state = 0;
		L2.set[set].way[w].dirty = 0;
	}
}

void PrintCacheLine(void)
{
	char msgOut[1024];
	debugLog(2, __func__, "operation PRINT_CACHE_LINE");
	for (int set = 0; set < sets; set++) {
		for(int w = 0; w < associativity; w++){
			if(L2.set[set].way[w].valid == 1) { //Check data is valid
				sprintf(msgOut, "Data at address 0x%x is valid ",L2.set[set].way[w].tag);
			}
			else {
				sprintf(msgOut, "Data not valid ");
			}
			debugLog(1,__func__, msgOut);
		}
		debugLog(1,__func__, "\n");
	}
}


void UpdatePLRU(int set, int w)
{

}

int WhichWay(int set)
{
	return 1;
}

void UpdateMESIstate(int type, int way)
{
	int state = L2.set[set_index].way[way].MESI_state;
	switch (state) {
		case INVALID:
			if(type == READ) {
				BusOperation(READ, addr, GetSnoopResult(addr)); //Send read command to bus
				int res = GetSnoopResult(addr);
				if ( res == HIT) {
					L2.set[set_index].way[way].MESI_state = SHARED;
				} else if ( res == NOHIT) {
					L2.set[set_index].way[way].MESI_state = EXCLUSIVE;
				}
			} else if(type == WRITE){
				L2.set[set_index].way[way].MESI_state = MODEFIED;
				BusOperation(RWIM, addr, GetSnoopResult(addr)); //Send readX command to bus
			}
			break;
		case SHARED:
			if(type == WRITE){
				L2.set[set_index].way[way].MESI_state = MODEFIED;
				BusOperation(INVALIDATE, addr, GetSnoopResult(addr)); //Send BusUpgr command to bus
			}
			break;
		case EXCLUSIVE:
			if(type == WRITE){
				L2.set[set_index].way[way].MESI_state = MODEFIED;
			}
			break;
		case MODEFIED:
			break;
	}
}

void VoidWay(int way) {
	BusOperation(INVALIDATE, addr, GetSnoopResult(addr));
	L2.set[set_index].way[way].valid = 0; //Invalidating
	L2.set[set_index].way[way].dirty = 0; //Invalidating
}

void Flush(int way) {
	BusOperation(WRITE, addr, GetSnoopResult(addr));
}

void UpdateMESIstateSnoop(int type, int way)
{
	int state = L2.set[set_index].way[way].MESI_state;
	switch (state) {
		case INVALID:
			break;
		case SHARED:
			PutSnoopResult(addr,HIT);
			if(type == RWIM || type == INVALIDATE ){
				L2.set[set_index].way[way].MESI_state = INVALID;
			}
			break;
		case EXCLUSIVE:
			PutSnoopResult(addr,HIT);
			if(type == RWIM){
				L2.set[set_index].way[way].MESI_state = INVALID;
				VoidWay(way);
			} else if(type == READ){
				L2.set[set_index].way[way].MESI_state = SHARED;
			}
			break;
		case MODEFIED:
			PutSnoopResult(addr,HITM);
			Flush(way);
			if(type == READ) {
				L2.set[set_index].way[way].MESI_state = SHARED;
			} else if(type == RWIM || type == INVALIDATE ){
				L2.set[set_index].way[way].MESI_state = INVALID;
				VoidWay(way);
			}

			break;
	}
}
