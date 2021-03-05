#include <stdio.h> 
#include <stdlib.h> // For exit() 
#include<string.h>
int main() 
{
	char buff[80] = "";
	strcat(buff,"LSTU");
	strcat(buff," ");
	strcat(buff,"LSTM");
	strcat(buff,"\n");
	strcat(buff,"LSTM");
	printf("%s",buff);
	// puts(buff);
}
