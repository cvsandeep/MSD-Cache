/*
 * bus_operation.c
 *
 *  Created on: Nov 23, 2019
 *      Author: cvssa
 */

#include "bus_operation.h"
#include "logger.h"

char msgOut[2048];
char *res_string[] = {"NOHIT","HIT","HITM"};
char *BusOp_string[] = {"","READ","WRITE","INVALIDATE","RWIM"};
char *msg_string[] = {"", "GETLINE","SENDLINE", "INVALIDATELINE", "EVICTLINE"};
/*
 * Used to simulate a bus operation and to capture the snoop results of last
 * level caches of other processors
 */
void BusOperation(int BusOp, unsigned int Address, unsigned int SnoopResult)
{
	//SnoopResult = GetSnoopResult(Address);
	sprintf(msgOut, "BusOp: %s, Address:0x%08x, Snoop Result:%s", BusOp_string[BusOp], Address,res_string[SnoopResult]);
	debugLog(BUSOP,__func__, msgOut);
}

/*
 * Used to simulate the reporting of snoop results by other caches
 */
unsigned int GetSnoopResult(unsigned int Address)
{
	int result = NOHIT;
	if((Address & 0x3) == 0x00) {
		result = HIT;
	} else if((Address & 0x3) == 0x01) {
		result = HITM;
	}
	sprintf(msgOut, "Address 0x%08x,result %s ",Address,res_string[result]);
	debugLog(BUSOP,__func__, msgOut);
	return result;
}

/*
Used to report the result of our snooping bus operations performed by other
caches
*/
void PutSnoopResult(unsigned int Address, unsigned int SnoopResult)
{
	sprintf(msgOut, "SnoopResult: Address 0x%08x SnoopResult: %d", Address, SnoopResult);
	debugLog(BUSOP,__func__, msgOut);
}

/*
Used to simulate communication to our upper level cache
*/
void MessageToCache(char Message, unsigned int Address)
{
	sprintf(msgOut, "L2: %d 0x%08x", Message, Address);
	debugLog(BUSOP,__func__, msgOut);
}
