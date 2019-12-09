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
#include "cache_performance.h"

unsigned int tag, set_index, offset;
extern unsigned int cache_lines, associativity,sets,line_size, op;
char msgOut[2048];
static char *MesiState[] = { "I", "S", "E", "M"};
static char *dirty_str[] = { " ", "D"};

void DecodeAddress(void){

	unsigned int lines = log2(line_size);
	unsigned int set = log2(sets);
	tag = addr; set_index = addr; offset = addr;

	offset = offset & ((1 << lines) -1);
	set_index = set_index >> lines & ((1<< set) -1);
	tag = tag >> (lines + set) & ((1<< (32-(lines+set))) -1);
	debugLog(CACHEOP,__func__,"*******************************************************************");
	sprintf(msgOut, "Address 0x%x ; Offset 0x%x; set_index 0x%x; tag 0x%x  ",addr,offset,set_index,tag);
	debugLog(CACHEOP,__func__, msgOut);
	debugLog(CACHEOP,__func__,"*******************************************************************");
}

void ReIntializeCache(void){
	debugLog(CACHEOPX,__func__,"");
	L2.set = malloc(sizeof(struct CACHE_SET_8_WAY)*sets);
	for (int set = 0; set < sets; set++){
			for(int plru =0 ; plru < 7; plru++){
				L2.set[set].PLRU[plru] = 0;
			}
		}
}
// Level 1
void readData(void)
{
	int evict = 1, way=0;
	debugLog(CACHEOPX,__func__,"");
	for(int w = 0; w < associativity; w++){
		if(L2.set[set_index].way[w].valid == 1) { //Check data is valid
			if(L2.set[set_index].way[w].tag == tag) { //Check tag
				debugLog(CACHEOP,__func__, "Data found");
				HitCount();
				if(op == WRITE_DATA)
					UpdateMESIstate(RWIM, w);
				else
					UpdateMESIstate(READ, w);
				UpdatePLRU(set_index,w);
				return;
			}
		} else {
			if (evict == 1) {
				evict = 0;
				way = w;
			}
		}
	}
	debugLog(CACHEOP,__func__, "Data not found in the cache line");

	if(evict) {
		debugLog(CACHEOPX,__func__, "Evicting");
		way = WhichWay(set_index);
		VoidWay(way);
		EvictCount();
	} else {
		MissCount();
	}

	sprintf(msgOut, "Set-%d; Way-%d; Tag-0x%08x",set_index,way,tag);
	debugLog(CACHEOP,__func__,msgOut);
	L2.set[set_index].way[way].valid = 1;
	L2.set[set_index].way[way].dirty = 0;
	L2.set[set_index].way[way].tag = tag;
	L2.set[set_index].way[way].MESI_state = INVALID;
	if(op == WRITE_DATA) {
		UpdateMESIstate(RWIM, way);
		//MessageToCache(GETLINE,addr);
		L2.set[set_index].way[way].dirty = 1;
	} else {
		UpdateMESIstate(READ, way);
	}
	UpdatePLRU(set_index,way);
}

void writeData(void)
{
	int w;
	debugLog(CACHEOPX,__func__,"");
	//debugLog(1,__func__, msgOut);
	for(w = 0; w < associativity; w++){
		if(L2.set[set_index].way[w].valid == 1) { //Check data is valid
			if(L2.set[set_index].way[w].tag == tag) { //Check tag
				debugLog(CACHEOP,__func__, "Data found");
				break; // Return data
			}
		}
	}
	if ( w == associativity){
		readData();
	} else {
		HitCount();
		UpdatePLRU(set_index,w);
		UpdateMESIstate(WRITE, w);
		L2.set[set_index].way[w].dirty = 1;
	}
}

void ReadInstruction(void)
{
	debugLog(2,__func__,"");
	readData();
}

void SnoopedInvalidate(void)
{
	for(int w = 0; w < associativity; w++){
		if(L2.set[set_index].way[w].valid == 1) { //Check data is valid
			if(L2.set[set_index].way[w].tag == tag) { //Check tag
				debugLog(CACHEOP,__func__, "Data found");
				UpdateMESIstateSnoop(INVALIDATE,w);
				//UpdatePLRU(set_index,w);
				return; // Return data
			}
		}
	}

}

void SnoopedRead(void)
{
	for(int w = 0; w < associativity; w++){
		if(L2.set[set_index].way[w].valid == 1) { //Check data is valid
			if(L2.set[set_index].way[w].tag == tag) { //Check tag
				debugLog(CACHEOP,__func__, "Data found");
				UpdateMESIstateSnoop(READ,w);
				//UpdatePLRU(set_index,w);

				return; // Return data
			}
		}
	}
	debugLog(CACHEOPX, __func__, "Data not Found");
}

void SnoopedWrite(void)
{
	for(int w = 0; w < associativity; w++){
		if(L2.set[set_index].way[w].valid == 1) { //Check data is valid
			if(L2.set[set_index].way[w].tag == tag) { //Check tag
				debugLog(CACHEOP,__func__, "Data found");
				UpdateMESIstateSnoop(WRITE,w); // No need as there are no any operations for write.
				//UpdatePLRU(set_index,w);
				return; // Return data
			}
		}
	}
	debugLog(CACHEOPX, __func__, "Data not Found");
}

void SnoopedReadX(void)
{
	for(int w = 0; w < associativity; w++){
		if(L2.set[set_index].way[w].valid == 1) { //Check data is valid
			if(L2.set[set_index].way[w].tag == tag) { //Check tag
				debugLog(CACHEOP,__func__, "Data found");
				UpdateMESIstateSnoop(RWIM,w);
				//UpdatePLRU(set_index,w);
				return; // Return data
			}
		}
	}
	debugLog(CACHEOPX, __func__, "Data not Found");
}

void ClearAndSet(void)
{
	debugLog(CACHEOPX, __func__, "");
	for (int set = 0; set < sets; set++){
		set_index = set;
		for(int w = 0; w < associativity; w++){
				VoidWay(w);
		}
		for(int plru =0 ; plru < 7; plru++){
			L2.set[set].PLRU[plru] = 0;
		}
	}

}

void PrintCacheLine(void)
{
	char buf[2048];
	int set_filled = 0;
	sprintf(msgOut, " ");
	debugLog(CACHEOPX, __func__, "");
	for (int set = 0; set < sets; set++) {
		set_filled = 0;
		sprintf(msgOut, "Set-%d:PLRU-",set);
		for(int plru =0 ; plru < 7; plru++){
			sprintf(buf, "%d",L2.set[set].PLRU[plru]);
			strcat(msgOut,buf);
		}
		for(int w = 0; w < associativity; w++){
			if(L2.set[set].way[w].valid == 1) { //Check data is valid
				//len += sizeof(msgOut);
				sprintf(buf, " Way-%d: 0x%08x,%s %s;",w,L2.set[set].way[w].tag, dirty_str[L2.set[set].way[w].dirty], MesiState[L2.set[set].way[w].MESI_state]);
				set_filled = 1;
			}
			else {
				sprintf(buf, " Way-%d:  -------- ,  I;",w);
			}
			strcat(msgOut,buf);
		}
		if(set_filled)
			debugLog(0,__func__, msgOut);
	}
}


void UpdatePLRU(int set, int w)
{
	char buf[2048];
	sprintf(msgOut, "PLRU Bits ");
	for(int plru =0 ; plru < 7; plru++){
		sprintf(buf, "%d",L2.set[set].PLRU[plru]);
		strcat(msgOut,buf);
	}
	if(associativity == 8)
		switch(w){
			case 0: L2.set[set].PLRU[0] = 0; L2.set[set].PLRU[1] = 0; L2.set[set].PLRU[3] = 0; break;
			case 1: L2.set[set].PLRU[0] = 0; L2.set[set].PLRU[1] = 0; L2.set[set].PLRU[3] = 1; break;
			case 2: L2.set[set].PLRU[0] = 0; L2.set[set].PLRU[1] = 1; L2.set[set].PLRU[4] = 0; break;
			case 3: L2.set[set].PLRU[0] = 0; L2.set[set].PLRU[1] = 1; L2.set[set].PLRU[4] = 1; break;
			case 4: L2.set[set].PLRU[0] = 1; L2.set[set].PLRU[2] = 0; L2.set[set].PLRU[5] = 0; break;
			case 5: L2.set[set].PLRU[0] = 1; L2.set[set].PLRU[2] = 0; L2.set[set].PLRU[5] = 1; break;
			case 6: L2.set[set].PLRU[0] = 1; L2.set[set].PLRU[2] = 1; L2.set[set].PLRU[6] = 0; break;
			case 7: L2.set[set].PLRU[0] = 1; L2.set[set].PLRU[2] = 1; L2.set[set].PLRU[6] = 1; break;
		}

	if(associativity == 4)
		switch(w){
			case 0: L2.set[set].PLRU[0] = 0; L2.set[set].PLRU[1] = 0; break;
			case 1: L2.set[set].PLRU[0] = 0; L2.set[set].PLRU[1] = 1; break;
			case 2: L2.set[set].PLRU[0] = 1; L2.set[set].PLRU[2] = 0; break;
			case 3: L2.set[set].PLRU[0] = 1; L2.set[set].PLRU[2] = 1; break;
		}

	strcat(msgOut," Updated To ");
	for(int plru =0 ; plru < 7; plru++){
		sprintf(buf, "%d",L2.set[set].PLRU[plru]);
		strcat(msgOut,buf);
	}
	debugLog(CACHEOPX,__func__, msgOut);
}

int WhichWay(int set)
{
	debugLog(CACHEOPX, __func__, "Evicting");
	if(associativity == 8) {
		if (L2.set[set].PLRU[0] == 0){
			if(L2.set[set].PLRU[2] == 0){
				if(L2.set[set].PLRU[6] == 0)
					return 7;
				else
					return 6;
			}
			else{
				if(L2.set[set].PLRU[5] == 0)
					return 5;
				else
					return 4;
			}
		}
		else{
			if(L2.set[set].PLRU[1] == 0){
				if(L2.set[set].PLRU[4] == 0)
					return 3;
				else
					return 2;
			}
			else{
				if(L2.set[set].PLRU[3] == 0)
					return 1;
				else
					return 0;

			}
		}
	} else if(associativity == 4){
		if (L2.set[set].PLRU[0] == 0){
			if(L2.set[set].PLRU[1] == 0){
				return 3;
			}
			else{
				return 2;
			}
		}
		else{
			if(L2.set[set].PLRU[1] == 0){
				return 1;
			}
			else{
				return 0;

			}
		}
	} else {
		debugLog(CACHEOP, __func__, "Not supported");
		return -1;
	}
}

void VoidWay(int way) {
	debugLog(CACHEOPX, __func__, "");
	if (L2.set[set_index].way[way].valid == 1) {
		if(op < 3) //Means Evicting
			MessageToCache(EVICTLINE,L2.set[set_index].way[way].tag);
		else {
			// May be need to do this only in Shared state.
			if(L2.set[set_index].way[way].MESI_state == MODEFIED) {
				MessageToCache(GETLINE,L2.set[set_index].way[way].tag); //Getting the line from L1 to check weather its dirty or not
			}
			MessageToCache(INVALIDATELINE,L2.set[set_index].way[way].tag);
		}
		if(L2.set[set_index].way[way].dirty == 1) {
			Flush(way);
		}
	}
	L2.set[set_index].way[way].valid = 0;
	L2.set[set_index].way[way].dirty = 0;
	L2.set[set_index].way[way].MESI_state = 0;
	L2.set[set_index].way[way].tag = 0;
}

void Flush(int way) {
	debugLog(CACHEOP, __func__, "");
	BusOperation(WRITE, addr, HITM);
	L2.set[set_index].way[way].dirty = 0;
}

void UpdateMESIstate(int type, int way)
{
	int state = L2.set[set_index].way[way].MESI_state;
	switch (state) {
		case INVALID:
			if(type == READ) {
				int res = GetSnoopResult(addr);
				BusOperation(READ, addr, res); //Read from DRAM
				if ( res == HIT || res == HITM) {
					L2.set[set_index].way[way].MESI_state = SHARED;
				} else if ( res == NOHIT) {
					L2.set[set_index].way[way].MESI_state = EXCLUSIVE;
				}
				MessageToCache(SENDLINE,addr);//Sends data to L1
			} else if(type == WRITE || type == RWIM){
				L2.set[set_index].way[way].MESI_state = MODEFIED;
				BusOperation(RWIM, addr, GetSnoopResult(addr)); //Send readX command to bus
				//First Time Write
			}
			break;
		case SHARED:
			if(type == READ) {
				MessageToCache(SENDLINE,addr);//Sends data to L1
			} else {
				L2.set[set_index].way[way].MESI_state = MODEFIED;
				BusOperation(INVALIDATE, addr, HITM); //Send BusUpgr command to bus
				//First Time Write
			}
			break;
		case EXCLUSIVE:
			if(type == WRITE){
				L2.set[set_index].way[way].MESI_state = MODEFIED;
				//First Time Write
			} else if(type == READ){
				MessageToCache(SENDLINE,addr);//Sends data to L1
			}
			break;
		case MODEFIED:
			if(type == READ){
				MessageToCache(SENDLINE,addr);//Sends data to L1
			}
			break;
	}
	sprintf(msgOut, "%s->%s",MesiState[state],MesiState[L2.set[set_index].way[way].MESI_state]);
	debugLog(CACHEOP,__func__, msgOut);
}

void UpdateMESIstateSnoop(int type, int way)
{
	int state = L2.set[set_index].way[way].MESI_state;
	switch (state) {
		case INVALID:
			PutSnoopResult(addr,NOHIT);
			break;
		case SHARED:
			PutSnoopResult(addr,HIT);
			//HitCount();
			if(type == WRITE  || type == RWIM || type == INVALIDATE ){
				VoidWay(way);
				L2.set[set_index].way[way].MESI_state = INVALID;
			}
			break;
		case EXCLUSIVE:
			PutSnoopResult(addr,HIT);
			//HitCount();
			if(type == RWIM || type == INVALIDATE ){
				VoidWay(way);
				L2.set[set_index].way[way].MESI_state = INVALID;
			} else if(type == READ){
				L2.set[set_index].way[way].MESI_state = SHARED;
			}
			break;
		case MODEFIED:
			PutSnoopResult(addr,HITM);
			//HitModifiedLineCount();
			if(type == READ) {
				Flush(way);
				L2.set[set_index].way[way].MESI_state = SHARED;
			} else if(type == RWIM || type == INVALIDATE ){
				VoidWay(way);
				L2.set[set_index].way[way].MESI_state = INVALID;
			}

			break;
	}
	sprintf(msgOut, "%s->%s",MesiState[state],MesiState[L2.set[set_index].way[way].MESI_state]);
	debugLog(CACHEOP,__func__, msgOut);
}
