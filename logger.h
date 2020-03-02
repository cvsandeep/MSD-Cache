/*
 * logger.h
 *
 *  Created on: Nov 23, 2019
 *      Author: Team
 */
#include <stdio.h>

#define BUSOP 1
#define CACHEOP 2
#define CACHEOPX 3
#define PERFORMANCE 4
#define CONTROL 5
void debugLog(int log_level, const char *function_name, char *message);

