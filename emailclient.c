#include <stdio.h> 
#include <netdb.h> 
#include <stdlib.h>
#include <netinet/in.h> 
#include <stdlib.h> 
#include <string.h> 
#include <sys/socket.h> 
#include <sys/types.h> 
#include <dirent.h>
#define MAX 80 
#define PORT 8080 
#define SA struct sockaddr 
#define MAX_USER_LENGTH 20
#define MAX_USER_LIST 100

void subprompt(int sockfd){
	char user_id[MAX_USER_LENGTH];
	char buff[MAX];
	bzero(buff, sizeof(buff)); 
	scanf("%s",user_id);
	write(sockfd, user_id, sizeof(user_id)); 
	read(sockfd,buff,sizeof(buff));
	puts(buff);
	while(1 < 2){
		printf("Sub­-Prompt­-%s>",user_id);
		if(strcmp(buff,"Read") == 0){
			strcpy(buff,"READM");
			write(sockfd, buff, sizeof(buff));
			bzero(buff, sizeof(buff)); 
			read(sockfd, buff, sizeof(buff));
			puts(buff);
		}
	}
}

void command_processor(int sockfd){
	char buff[MAX];
	while(1 < 2){
		printf("Main-prompt> ");
		scanf("%s",buff);
		if(strcmp(buff,"Listusers") == 0){
			bzero(buff,MAX);
			strcpy(buff,"LSTU");
			write(sockfd, buff, sizeof(buff)); 
			bzero(buff, sizeof(buff)); 
			read(sockfd,buff,sizeof(buff));
			puts(buff);
		}
		
		else if(strcmp(buff,"Adduser") == 0){
			strcpy(buff,"ADDU");
			write(sockfd, buff, sizeof(buff));
			bzero(buff, sizeof(buff)); 
			scanf("%s",buff);
			write(sockfd, buff, sizeof(buff));
			bzero(buff, sizeof(buff)); 
			read(sockfd,buff,sizeof(buff));
			puts(buff);
		}
		
		else if(strcmp(buff,"SetUser") == 0){
			strcpy(buff,"USER");
			write(sockfd, buff, sizeof(buff));
			subprompt(sockfd);
		}
		
		else if(strcmp(buff,"exit") == 0){
			break;
		}
	}
}

void func(int sockfd){
	char buff[MAX];
	printf("correctly 1");
	bzero(buff,MAX);
	printf("correctly 2");
	read(sockfd,buff,sizeof(buff));
	puts("read from server\n");
	printf("%s",buff);
	bzero(buff,MAX);
	strcpy(buff,"server");
	write(sockfd,buff,sizeof(buff));
}

int main(){
		int sockfd, connfd; 
	struct sockaddr_in servaddr, cli; 

	// socket create and varification 
	sockfd = socket(AF_INET, SOCK_STREAM, 0); 
	if (sockfd == -1) { 
		printf("socket creation failed...\n"); 
		exit(0); 
	} 
	else
		printf("Socket successfully created..\n"); 
	bzero(&servaddr, sizeof(servaddr)); 

	// assign IP, PORT 
	servaddr.sin_family = AF_INET; 
	servaddr.sin_addr.s_addr = inet_addr("127.0.0.1"); 
	servaddr.sin_port = htons(PORT); 

	// connect the client socket to server socket 
	if (connect(sockfd, (SA*)&servaddr, sizeof(servaddr)) != 0) { 
		printf("connection with the server failed...\n"); 
		exit(0); 
	} 
	else
		printf("connected to the server..\n"); 
	// command_processor(sockfd);
	func(sockfd);
	close(sockfd);
}
