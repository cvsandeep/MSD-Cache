/*
 * cache_control.h
 *
 *  Created on: Nov 20, 2019
 *      Author: venksand
 */

#ifndef CACHE_CONTROL_H_
#define CACHE_CONTROL_H_

#include <stdio.h>

FILE *trace_file, *config_file;

int UpdateTraceOperation(void);
void UpdateConfig(void);

#endif /* CACHE_CONTROL_H_ */
