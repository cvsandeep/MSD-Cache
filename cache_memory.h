/*
 * cache_memory.h
 *
 *  Created on: Nov 19, 2019
 *      Author: venksand
 */

struct CACHE_LINE
{
	int valid;
	int dirty;
	int tag;
	//int index;
	int offset[64];
};

struct CACHE_SET
{
	struct CACHE_LINE way[4]; //Associativity
	int LRU[3]; //May need to change depends on per way and set
	int MESI[3];//Stores the state of MESI
				//May need to change depends on per way and set
};

struct L1_CACHE
{
	struct CACHE_SET set[255]
};

struct L2_CACHE
{
	struct CACHE_SET set[512]
};
