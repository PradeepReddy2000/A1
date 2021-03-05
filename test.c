#include <stdio.h> 
#include <stdlib.h> // For exit() 

int main() 
{
	FILE *fptr2;
	fptr2 = fopen("temp","w");
	char c;
	c = fgetc(fptr);
	int cnt =0,n=0;
	char messagebuffer[200];
	while(cnt < 3){
		if(c == '#'){
			cnt++;
		}
		messagebuffer[n]=c;
		n++;
		if(cnt != 3){
			c = fgetc(fptr);
		}
	}
	mesasgebuffer[n] = '\0';
	fputs(messagebuffer,fptr2);
	fclose(fptr);
	fclose(fptr2);
	return 0; 
}
