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
		op = (unsigned int) strtol(strtok(line," "), 0, 16);
		addr = (unsigned int) strtol(strtok(0 ," "), 0, 16);
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
	char *config;
	size_t len=0;


	while(getline(&line,&len, config_file) != -1 ){
		//printf("%s\n",line);
		config = strtok(line," ");
		if(strcmp(config,"debug") == 0)
		debug = (unsigned int) strtol(strtok(0 ," "), 0, 16);

		if(strcmp(config,"line_size") == 0) {
			line_size = (unsigned int) strtol(strtok(0 ," "), 0, 16);
			printf("line size is %d\n",line_size);
		}

		if(strcmp(config,"associativity") == 0) {
			associativity = (unsigned int) strtol(strtok(0 ," "), 0, 16);
			printf("associativity is %d\n",associativity);
		}

		if(strcmp(config,"cache_lines") == 0) {
			cache_lines = (unsigned int) strtol(strtok(0 ," "), 0, 16);
			printf("cache_lines is %d\n",cache_lines);
			sets = cache_lines/associativity;
		}
	}
	fclose(config_file);
}

