#include <stdio.h> 
#include <stdlib.h> // For exit() 

int main() 
{ 
	FILE *fptr; 

	char filename[100];
	int c; 

	printf("Enter the filename to open \n"); 
	scanf("%s", filename); 
	fflush(stdin);
	// Open file 
	fptr = fopen(filename, "w"); 
	if (fptr == NULL) 
	{ 
		printf("Cannot open file \n"); 
		exit(0); 
	} 
	char buff[100];
	fgets(buff,99,stdin);
	fputs(buff,fptr);
	fclose(fptr); 
	return 0; 
}
