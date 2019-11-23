/*
 * cache_control.h
 *
 *  Created on: Nov 20, 2019
 *      Author: venksand
 */

#ifndef CACHE_CONTROL_H_
#define CACHE_CONTROL_H_

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "cache_operation.h"

#define READ_DATA 0
#define WRITE_DATA 1
#define READ_INSTRUCTION 2
#define SNOOPED_INVALIDATE 3
#define SNOOPED_READ 4
#define SNOOPED_WRITE 5
#define SNOOPED_READ_X 6
#define CLEAR_AND_RESET 8
#define PRINT_CACHE_LINE 9

FILE *trace_file, *config_file;
unsigned int op, addr;
unsigned int debug;
unsigned int cache_lines, associativity,sets,line_size;

int UpdateTraceOperation(void);
void UpdateConfig(void);

#endif /* CACHE_CONTROL_H_ */
