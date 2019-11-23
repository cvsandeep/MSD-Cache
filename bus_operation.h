/*
 * bus_operation.h
 *
 *  Created on: Nov 23, 2019
 *      Author: cvssa
 */

#ifndef BUS_OPERATION_H_
#define BUS_OPERATION_H_

#include <stdio.h>
/*
 * These defines are from project description
 */

/*
* Bus Operation types
*/
#define READ 1 /* Bus Read */
#define WRITE 2 /* Bus Write */
#define INVALIDATE 3 /* Bus Invalidate */
#define RWIM 4 /* Bus Read With Intent to Modify */
/*
* Snoop Result types
*/
#define NOHIT 0 /* No hit */
#define HIT 1 /* Hit */
#define HITM 2 /* Hit to modified line */
/*
* L2 to L1 message types
*/
#define GETLINE 1 /* Request data for modified line in L1 */
#define SENDLINE 2 /* Send requested cache line to L1 */
#define INVALIDATELINE 3 /* Invalidate a line in L1 */
#define EVICTLINE 4 /* Evict a line from L1 */

void BusOperation(int BusOp, unsigned int Address, unsigned SnoopResult);
unsigned int GetSnoopResult(unsigned int Address);
void PutSnoopResult(unsigned int Address, unsigned SnoopResult);
void MessageToCache(char Message, unsigned int Address);



#endif /* BUS_OPERATION_H_ */
