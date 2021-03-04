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

void LSTU(){
		for(int i=0;i<user_pointer-1;i++){
			printf("%s ",user_list[i].name);
		}
		printf("%s\n",user_list[user_pointer-1].name);
}

void ADDU(){
	char user_id[MAX_USER_LENGTH];
	scanf("%s",user_id);
	if(check(user_id,0) == 1){
		printf("Userid Already present\n");
	}
	else{
		// add new user to user_list
		strcpy(user_list[user_pointer].name,user_id);
		user_list[user_pointer].number_of_mails =0;
		user_pointer++;
		printf("Created %s\n",user_list[user_pointer-1].name);
		// ceate a new empty file with user name as its filename.
		FILE *fptr;
		fptr = fopen(user_id,"w");
		fclose(fptr);
	}
}

void usercommand(){
	
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
			scanf("%s",buff);
			
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
					while(c != EOF && cnt , 3){
						if(c == '#'){
							cnt++;
						}
						
						if(c != EOF && cnt != 3){
							c = fgetc(curr_fptr);
						}
					}
				}
				
				int n=0;
				char messagebuffer[200];
				cnt=0;
				c = fgetc(curr_fptr);
				while(c != EOF && cnt < 3){
					
					if(c == '#'){
						cnt++;
					}
					
					messagebuffer[n]=c;
					n++;
					
					if(c != EOF && cnt != 3){
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
					while(cnt < 3){
						if(c == '#')
							cnt++;
						
						messagebuffer[n] = c;
						n++;
						
						if(cnt != 3)
							c = getchar();
					}
					
					fputs(messagebuffer,fptr);
					messagebuffer[n] = '\0';
					// fputs("\n",fptr);
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

void command_processor()
{
		while(1 < 2){
			char buff[MAX];
			printf("Enter the command :");
			scanf("%s",buff);
			if(strncmp("LSTU",buff,4) == 0){
				LSTU();
			}	
			else if(strncmp("ADDU",buff,4) == 0){
				ADDU();
			}
			else if(strncmp("USER",buff,4) == 0){
				usercommand();
			}
			else if(strncmp("QUIT",buff,4) == 0){
				break;
			}
			else{
				printf("Invalid Command Try again ... \n");
				continue;
			}
		}	
}

int main(){
	command_processor();
}

