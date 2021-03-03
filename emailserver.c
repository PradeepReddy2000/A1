#include <stdio.h> 
#include <netdb.h> 
#include <netinet/in.h> 
#include <stdlib.h> 
#include <string.h> 
#include <sys/socket.h> 
#include <sys/types.h> 
#include <dirent.h>
#define MAX 80 
#define PORT 8080 
#define SA struct sockaddr 

void LSTU(){
	DIR *d;
	struct dirent *dir;
	d = opendir(".");
	if(d){
		while(dir = readdir(d) != NULL){
			// if(strncmp("emailserver.c",dir->d_name,13) == 0){
				// printf()
			// }
			// if(strcmp( dir->d_name, "." ))
			// fails at this step.
				printf("%s\n", dir->d_name);
			// printf("Test\n");
		}
		closedir(d);
	}
}

void command_processor()
{
		char buff[MAX];
		printf("Enter the command :");
		scanf("%s",buff);
		printf("Command read Sucessfully\n");
		if(strncmp("LSTU",buff,4) == 0){
			printf("Entered LSTU command :- ");
			LSTU();
		}	
}
int main(){
	command_processor();
}

