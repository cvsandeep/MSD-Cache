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

struct CACHE_SET_4_WAY
{
	struct CACHE_LINE way[4]; //Associativity
	int PLRU[3]; //May need to change depends on per way and set
	int MESI[3];//Stores the state of MESI
				//May need to change depends on per way and set
};

struct CACHE_SET_8_WAY
{
	struct CACHE_LINE way[8]; //Associativity
	int PLRU[7]; //May need to change depends on per way and set
	int MESI[3];//Stores the state of MESI
				//May need to change depends on per way and set
};

struct L1_CACHE
{
	struct CACHE_SET_4_WAY set[255];
};

struct L2_CACHE
{
	struct CACHE_SET_8_WAY set[512];
};
