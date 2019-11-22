/*
 * cache_operation.c
 *
 *  Created on: Nov 22, 2019
 *      Author: sandeep
 */
#include "cache_operation.h"

/*
 * Used to simulate a bus operation and to capture the snoop results of last
 * level caches of other processors
 */
void BusOperation(int BusOp, unsigned int Address, unsigned int SnoopResult)
{
	SnoopResult = GetSnoopResult(Address);
	printf("BusOp: %d, Address:0x%x, Snoop Result:%d, \n", BusOp, Address,SnoopResult);
}

/*
 * Used to simulate the reporting of snoop results by other caches
 */
unsigned int GetSnoopResult(unsigned int Address)
{
	printf("SnoopResult: Address 0x%x",Address);
	return NOHIT;
}

/*
Used to report the result of our snooping bus operations performed by other
caches
*/
void PutSnoopResult(unsigned int Address, unsigned int SnoopResult)
{
	printf("SnoopResult: Address 0x%x SnoopResult: %d\n", Address, SnoopResult);
}

/*
Used to simulate communication to our upper level cache
*/
void MessageToCache(char Message, unsigned int Address)
{
	printf("L2: %d 0x%x\n", Message, Address);
}

void UpdatePLRU(int set, int w)
{

}

int WhichWay(int set)
{
	return 1;
}
