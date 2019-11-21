/*
 * cache_control.c
 *
 *  Created on: Nov 20, 2019
 *      Author: Sandeep
 */

#include "cache_control.h"

/*
 * Read each line from trace file and decode the operation and address
 */
int UpdateTraceOperation(void){
	char *line;
	size_t len=0;
	if(getline(&line,&len, trace_file) != -1 ){
		printf("\n%s",line);
		return 1;
	} else {
		fclose(trace_file);
		return 0;
	}
}

/*
 * Updates the Configuration by reading the config file.
 */
void UpdateConfig(void){
	char *line;
	size_t len=0;
	while(getline(&line,&len, config_file) != -1 ){
		printf("\n%s",line);
	}
}
