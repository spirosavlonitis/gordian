#include <stdio.h>
#include <stdlib.h>
#include <string.h>


int combgen(char *,int);
int power(int,int);

int main(void)
{

	int len;
	char *chars;
	
	len = 7;
	chars = "0123456789";

	combgen(chars,len);


	exit(0);

}

int combgen(char *chars,int len)
{
	int i,b,j,x,poss,total;
	char *units[len],comb[len+2];

	total = 0;
	b = len-1;
	x = b-1;
	poss = power(strlen(chars),len)/strlen(chars) +1;
	comb[len] = '\n';
	comb[len+1] = '\0';

	for (i = 0; i < len ; ++i)
		units[i] = strdup(chars);

	while (--poss){
		for (i = 0; i < strlen(chars) ; ++i){
			for (j = 0; j < len ; j++)
				comb[j] =*units[j];
			printf("%s",comb);
			units[b]++;
			if (!*units[b])
			  units[b] -= strlen(chars);
		}
		while (x >= 0 && *++units[x] == '\0'){
			units[x] -= strlen(chars);
			--x;
		}
		x = b-1;
		total += 10;
	}

	printf("%d\n",total);

	return 0;
}


int power(int b,int p)
{	
	int n;

	n = b;
	while (--p)
		n *= b;
	
	return n;
}