/*
 * cache_memory.h
 *
 *  Created on: Nov 19, 2019
 *      Author: venksand
 *
 */

#define BYTE_LINES 64

struct CACHE_LINE
{
	int valid;
	int dirty;
	int MESI_state;
	int tag;
	//int offset; //int offset[BYTE_LINES]; to store 64 Bytes of data
};

struct CACHE_SET_4_WAY
{
	struct CACHE_LINE way[4]; //Associativity
	int PLRU[3]; //May need to change depends on per way and set
};

struct CACHE_SET_8_WAY
{
	struct CACHE_LINE way[8]; //Associativity
	int PLRU[7]; //May need to change depends on per way and set
	//int MESI[3];//Stores the state of MESI
				//May need to change depends on per way and set
};

struct CACHE_SET_N_WAY
{
	struct CACHE_LINE* way; //Associativity
	int* PLRU; //May need to change depends on per way and set
};

/*
 * Assuming the name as L2 as we consider two level caches
 * Last level Cache Capacity = 16MB = 2^4 * 2^20/2^6 = 2^18 cache lines
 * 8 way set associative = 2^15 sets = 32768 sets
 * Write allocate policy with PLRU replacement
 * MESI Protocol for cache coherence
 */

struct N_CACHE
{
	//struct CACHE_SET_N_WAY *set; For now 8 way
	struct CACHE_SET_8_WAY *set;

}L2;

/*
 * 4 way set associative
 * Write once policy:
 * 		The first write to a line is write through
 * 		Subsequent writes to the same line is write back.
 */
struct L1_CACHE
{
	struct CACHE_SET_4_WAY *set;
};
