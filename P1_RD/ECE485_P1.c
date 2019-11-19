#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <unistd.h>
#include <errno.h>
#include <sys/types.h>
#include <fcntl.h>
#include <sys/stat.h>

#define BUFFSIZE 32768
#define RDWR 8196

//Todd Townsend
//Email Address:tnt7@pdx.edu
//ECE 485-001
//Final Project
//ECE485_P1
void parameters(int log_level, char function_name, char message[]);
{
	
}
int main(int argc, char * argv[])
{
	char buf[BUFFSIZE];	//Initialize Buffer
	char buf1[BUFFSIZE];	//Initialize Buffer
	int fd,fd1,fd2,fd3 = 0;
	int i,j,k = 0;
	int choice,count = 0;
	int Rd_count[RDWR];
	int Wr_count[RDWR];
	int log_level = 0;
	char function_name;
	char message[];
	
	if (argc != 2)	//Error check for the correct number of necessary arguements
	{
		write(STDERR_FILENO,"\nPlease enter two file names as an Arguements!\n\n",53);	
		exit(EXIT_SUCCESS);
	} 
	
	if (access(argv[1],F_OK))	//Error check to make sure that the File Exists
	{
		write(STDERR_FILENO,"\nThe Trace File you entered Does Not Exist! Please Run the Program Again With A Valid Trace File!\n\n",93);
		exit(EXIT_SUCCESS);
	}	
	
	if (access(argv[2],F_OK))	//Error check to make sure that the File Exists
	{
		write(STDERR_FILENO,"\nThe Config File you entered Does Not Exist! Please Run the Program Again With A Valid Config File!\n\n",93);
		exit(EXIT_SUCCESS);
	}
	
	fd = open(argv[1], O_RDONLY, S_IRUSR | O_TRUNC | S_IWUSR |S_IRWXG);		//Open Trace File
	fd1 = open(argv[2], O_RDONLY, S_IRUSR | O_TRUNC | S_IWUSR |S_IRWXG);	//Open Config File
	
	fd2 = read(fd,buf,BUFFSIZE);	//Read Trace File into the Buffer 0
	fd3 = read(fd1,buf1,BUFFSIZE);	//Read Trace File into the Buffer 1
	int len_rd = strlen("Read");
	int len_wr = strlen("Write");	
	
	for(i=0;i<strlen(buf);++i)	//Loop to Find Reads and Writes in Trace File 
	{
		if (strncmp(buf,"Read",len_rd))
			++Rd_count;
		if (strncmp(buf,"Write",len_wr))
			++Wr_count;
			
	}
	for(i=0;i<strlen(buf1);++i)	//Loop to Find Desired configurations
	{
		if (strncmp(buf1,"Debugging",len_rd) || strncmp(buf1,"debugging",len_rd) || strncmp(buf1,"debug",len_rd) || strncmp(buf1,"Debug",len_rd))
			print(buf);
		else
			parameters(log_level, function_name, message);
			
	}
}