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
struct User{
	char name[MAX_USER_LENGTH];
	int number_of_mails;
};

struct User user_list[MAX_USER_LIST];
// To point the user to which it should be added 
int user_pointer =0; 

int check(char user_id[],int flg){
	for(int i=0;i<user_pointer;i++){
		if(strcmp(user_list[i].name,user_id) == 0){
			if(flg == 1){
				printf("User with the Userid %s exists and has %d mails in the spoolfie\n",user_id,user_list[i].number_of_mails);
			}
			return i+1;
		}
	}
	return 0;
}

void LSTU(int sockfd){
		char buff[MAX] = "";
		for(int i=0;i<user_pointer-1;i++){
			strcat(buff,user_list[i].name);
			strcat(buff," ");
		}
		strcat(buff,user_list[user_pointer-1].name);
		strcat(buff,"\n");
		write(sockfd,buff,sizeof(buff));
}

void ADDU(int sockfd){
	char user_id[MAX_USER_LENGTH];
	char buff[MAX]="";
	read(sockfd,user_id,sizeof(user_id));
	if(check(user_id,0) == 1){
		strcpy(buff,"Userid Already present\n");
	}
	else{
		// add new user to user_list
		strcpy(user_list[user_pointer].name,user_id);
		user_list[user_pointer].number_of_mails =0;
		user_pointer++;
		strcpy(buff,"Created ");
		strcat(buff,user_list[user_pointer-1].name);
		FILE *fptr;
		fptr = fopen(user_id,"w");
		fclose(fptr);
	}
	write(sockfd,buff,sizeof(buff));
}

void usercommand(int sockfd){
	
	char current_user_id[MAX_USER_LENGTH];
	scanf("%s",current_user_id);
	
	int check_num = check(current_user_id,1);
	
	if(check_num == 0){
		printf("username does not exists\n");
	}
	
	else{
		
		int currentptr=0;
		
		while(1 < 2){
			
			printf("Enter User-Commad: ");
			char buff[MAX];
			
			if(strcmp(buff,"READM") == 0){
				
				int num_mails = user_list[check_num-1].number_of_mails;
				
				if(num_mails == 0){
					printf("No More Mail");
					continue;
				}
				
				else if(currentptr == num_mails){
					currentptr =0;
				}
				
				// open file and precess till currentptr number of mails.
				FILE *curr_fptr;
				FILE *temp_fptr;
				
				curr_fptr = fopen(current_user_id,"r");
				temp_fptr = fopen("temp","w");
				
				char c;
				int cnt =0;
				for(int i=0;i<currentptr;i++){
					// dont need these strings
					cnt =0;
					c = fgetc(curr_fptr);
					while( cnt < 3){
						if(c == '#'){
							cnt++;
						}
						
						if( cnt != 3){
							c = fgetc(curr_fptr);
						}
					}
				}
				
				int n=0;
				char messagebuffer[200];
				cnt=0;
				if(currentptr != 0)
					c = fgetc(curr_fptr); // to absorb new line.
				c = fgetc(curr_fptr);
				while( cnt < 3){
					
					if(c == '#'){
						cnt++;
					}
					
					messagebuffer[n]=c;
					n++;
					
					if(cnt != 3){
						c = fgetc(curr_fptr);
					}
					
				}
				
				messagebuffer[n] = '\n';
				n++;
				
				fputs(messagebuffer,temp_fptr);
				fclose(temp_fptr);
				fclose(curr_fptr);
				currentptr++;
			}
			
			else if(strcmp(buff,"DELM") == 0){
				
			}
			
			else if(strcmp(buff,"SEND") == 0){
				char receiver_user_id[MAX_USER_LENGTH];
				scanf("%s",receiver_user_id);
				// check for receiver user-id
				int check_num = check(receiver_user_id,0) ;
				if(check_num == 0){
					printf("Userid is invalid ..\n");
					continue;
				}
				else{
					FILE *fptr;
					fptr = fopen(receiver_user_id,"a+");
					// open a receiver file and append the message at end.
					fputs("From: ",fptr);
					fputs(current_user_id,fptr);
					
					fputs("\nTo: ",fptr);
					fputs(receiver_user_id,fptr);
					
					fputs("\nSubject: ",fptr);
					
					char messagebuffer[200];
					char c;
					int n=0,cnt=0;
					c = getchar();
					c = getchar();
					while(cnt < 3){
						if(c == '#')
							cnt++;
						
						messagebuffer[n] = c;
						n++;
						
						if(cnt != 3)
							c = getchar();
					}
					
					messagebuffer[n] = '\0';
					fputs(messagebuffer,fptr);
					fputs("\n",fptr);
					fclose(fptr);
					user_list[check_num-1].number_of_mails++;
				}
			}
			
			else if(strcmp(buff,"DONEU") == 0){
				break;
			}
			
			else{
				continue;
			}
			
		}
	}
	
}

void command_processor(int sockfd)
{
		char buff[MAX];
		while(1 < 2){
			bzero(buff,MAX);
			read(sockfd,buff,sizeof(buff));
			puts(buff);
			if(strncmp("LSTU",buff,4) == 0){
				LSTU(sockfd);
			}	
			else if(strncmp("ADDU",buff,4) == 0){
				ADDU(sockfd);
			}
			else if(strncmp("USER",buff,4) == 0){
				usercommand(sockfd);
			}
			else if(strncmp("QUIT",buff,4) == 0){
				break;
			}
		}	
}

int main(){
	int sockfd, connfd, len; 
	struct sockaddr_in servaddr, cli; 

	// socket create and verification 
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
	servaddr.sin_addr.s_addr = htonl(INADDR_ANY); 
	servaddr.sin_port = htons(PORT); 

	// Binding newly created socket to given IP and verification 
	if ((bind(sockfd, (SA*)&servaddr, sizeof(servaddr))) != 0) { 
		printf("socket bind failed...\n"); 
		exit(0); 
	} 
	else
		printf("Socket successfully binded..\n"); 

	// Now server is ready to listen and verification 
	if ((listen(sockfd, 5)) != 0) { 
		printf("Listen failed...\n"); 
		exit(0); 
	} 
	else
		printf("Server listening..\n"); 
	len = sizeof(cli); 

	// Accept the data packet from client and verification 
	connfd = accept(sockfd, (SA*)&cli, &len); 
	if (connfd < 0) { 
		printf("server acccept failed...\n"); 
		exit(0); 
	} 
	else
		printf("server acccept the client...\n"); 

	// function for chat 
	command_processor(sockfd);
	// close the socket 
	close(sockfd); 
	
}

