#include <stdio.h>
#include <stdlib.h>

int allcombs(char *,int);
int matchcombs(char *,int);

int main(void)
{

	int len;
	char *chars;
	
	len = 7;
	chars = "0123456789";

	//allcombs(chars,len);
	matchcombs(chars,len);

	exit(0);

}