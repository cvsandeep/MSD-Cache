/*
 * logger.c
 *
 *  Created on: Nov 23, 2019
 *      Author: Todd N Townsend
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
#include "logger.h"

void debugLog(int log_level, char *function_name, char *message)
{
	switch(log_level)
	{
		case 0:
		{
			printf("%s:%s\n",function_name,message);
			break;
		}
		case 1:
		{
			printf("%s:%s\n",function_name,message);
			break;
		}
		case 2:
		{
			printf("%s:%s\n",function_name,message);
			break;
		}
		case 3:
		{
			printf("%s:%s\n",function_name,message);
			break;
		}
		case 4:
		{
			printf("%s:%s\n",function_name,message);
			break;
		}
		case 5:
		{
			//printf("%s:%s\n",function_name,message);
			break;
		}
		case 6:
		{
			printf("%s:%s\n",function_name,message);
			break;
		}
		case 7:
		{
			printf("%s:%s\n",function_name,message);
			break;
		}
		case 8:
		{
			//printf("%s:%s\n",function_name,message);
			break;
		}
		case 9:
		{
			printf("%s:%s\n",function_name,message);
			break;
		}
		case 10:
		{
			printf("%s:%s\n",function_name,message);
			break;
		}
		default:
			printf("Error in Logging Level\n");
	}
}
