/*
 * cache_control.c
 *
 *   Created on: Feb 24, 2020
 *      Author: Todd Townsend
 */

#include "cache_control.h"
#include "logger.h"
/*
 * Read each line from trace file and decode the operation and address
 */
int UpdateTraceOperation(void){
	char line[256];

	if(fgets(line, sizeof(line), trace_file) ){
		if (line[0] == '\n'){
			op = 10;
		} else {
			op = (unsigned int) strtol(strtok(line," "), 0, 16);
		}
		addr = (unsigned int) strtoul(strtok(0 ," "), 0, 16);
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
	char line[256];
	char *config;
	char msgOut[1024];

	while(fgets(line, sizeof(line), config_file)){
		config = strtok(line," ");
		if(strcmp(config,"debug") == 0){
			debug = (unsigned int) strtol(strtok(0 ," "), 0, 0);
			sprintf(msgOut,"Debug level is %d\n",debug);
			debugLog(CONTROL,__func__, msgOut);
		}

		if(strcmp(config,"line_size") == 0) {
			line_size = (unsigned int) strtol(strtok(0 ," "), 0, 0);
			sprintf(msgOut, "line size is %d",line_size);
			debugLog(CONTROL,__func__, msgOut);
		}

		if(strcmp(config,"associativity") == 0) {
			associativity = (unsigned int) strtol(strtok(0 ," "), 0, 0);
			sprintf(msgOut, "associativity is %d",associativity);
			debugLog(CONTROL,__func__, msgOut);
		}

		if(strcmp(config,"cache_lines") == 0) {
			cache_lines = (unsigned int) strtol(strtok(0 ," "), 0, 0);
			sprintf(msgOut, "cache_lines is %d",cache_lines);
			debugLog(CONTROL,__func__, msgOut);
			sets = cache_lines/associativity;
		}

	}
	fclose(config_file);
}

