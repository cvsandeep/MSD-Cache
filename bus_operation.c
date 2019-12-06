/*
 * bus_operation.c
 *
 *  Created on: Nov 23, 2019
 *      Author: cvssa
 */

#include "bus_operation.h"
#include "logger.h"

char msgOut[2048];
/*
 * Used to simulate a bus operation and to capture the snoop results of last
 * level caches of other processors
 */
void BusOperation(int BusOp, unsigned int Address, unsigned int SnoopResult)
{
	//SnoopResult = GetSnoopResult(Address);
	sprintf(msgOut, "BusOp: %d, Address:0x%x, Snoop Result:%d", BusOp, Address,SnoopResult);
	debugLog(0,__func__, msgOut);
}

/*
 * Used to simulate the reporting of snoop results by other caches
 */
unsigned int GetSnoopResult(unsigned int Address)
{
	const char *res_string[] = {"NOHIT","HIT","HITM"};
	int result = NOHIT;
	if((Address & 0x3) == 0x00) {
		result = HIT;
	} else if((Address & 0x3) == 0x01) {
		result = HITM;
	}
	sprintf(msgOut, "Address 0x%x,result %s ",Address,res_string[result]);
	debugLog(0,__func__, msgOut);
	return result;
}

/*
Used to report the result of our snooping bus operations performed by other
caches
*/
void PutSnoopResult(unsigned int Address, unsigned int SnoopResult)
{
	sprintf(msgOut, "SnoopResult: Address 0x%x SnoopResult: %d", Address, SnoopResult);
	debugLog(0,__func__, msgOut);
}

/*
Used to simulate communication to our upper level cache
*/
void MessageToCache(char Message, unsigned int Address)
{
	sprintf(msgOut, "L2: %d 0x%x", Message, Address);
	debugLog(0,__func__, msgOut);
}
