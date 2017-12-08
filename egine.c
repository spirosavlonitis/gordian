#include "hdr.h"
#include <stdio.h>
#include <string.h>

int allcombs(char *chars,int len)
{
	register int i,j,b,x,n;
	char *units[len],comb[len+2];
	
	comb[len] = '\n';
	comb[len+1] = '\0';
	b = len-1;
	n = strlen(chars);

	/* set the pointers */
	for (i = 0; i < len ; ++i)
		units[i] = chars;

	while (*units[0]){
		/*iterate n times for each character*/
		for (i = 0; i < n ; ++i){ 
			/* load the comb array except from the rightmost character*/
			for (j = 0; j < len-1 ; j++)
				comb[j] = *units[j];
			/* set the rightmost character */
			comb[b] = units[b][i];
			if (piped)
				printf("%s",comb);
			else
				fputs(comb,fp);
		}
		/* increment the second from the right most pointer */
		/* if it points to '\0' reset and increment it's left handside pointer */
		/* repeat until the first non '\0' has been reached or leftmost pointer has been incremented */
		for (x = b-1; x >= 0 && !*++units[x] ;--x)
			units[x] -= x ? n : 0;
	}
	return 0;
}

#define ismatch(A,B)		((A) == (B))

int matchcombs(char *chars,int len)
{
	register int i,j,b,x,n,match;
	char *units[len],comb[len+2];

	match = 0;
	comb[len] = '\n';
	comb[len+1] = '\0';
	b = len-1;
	n = strlen(chars);

	for (i = 0; i < len; ++i)
		units[i] = chars;

	for (; *units[0] ;units[b] -= n){
		for (i = 0; i < n ; ++i,++units[b],match = 0){
			for (j = 0; j < len ; ++j){
				comb[j] = *units[j];
				if (!match && j <= (len-2) && ismatch((*units[j]),*units[j+1]))
					match = 1;				
			}
			if (match)
				if (piped)
					printf("%s",comb);
				else
					fputs(comb,fp);
		}
		for (x = b-1;x >= 0 && *++units[x] == '\0';--x)
			units[x] -= x ? n : 0;
	}
	return 0;
}

int uniquecombs(char *chars,int len)
{
	register int i,j,b,x,n;
	char *units[len],comb[len+2];

	comb[len] = '\n';
	comb[len+1] = '\0';
	b = len-1;
	n = strlen(chars);

	for (i = 0; i < len; ++i)
		units[i] = chars;

	for (;*units[0];units[b] -= n){
		for (i = 0; i < n ; ++i,++units[b]){			
			for (j = 0; j < len ; ++j){
				if (j <= (len-2) && ismatch((*units[j]),(*units[j+1])))
					break;
				comb[j] = *units[j];
			}
			if (j == len )
			  if(piped)
				printf("%s",comb);
			  else
			  	fputs(comb,fp);
		}
		for (x = b - 1 ;x >= 0 && *++units[x] == '\0';--x)
			units[x] -= x ? n : 0;
	}
	return 0;
}

int singlecombs(char *chars,int len)
{
	register int i,j,k,b,x,s;
	int n;
	char *units[len],comb[len],scomb[len+2];

	comb[len] = '\n';
	comb[len+1] = '\0';
	b = len -1;
	n = strlen(chars);
	s = 1;

	for (i = 0; i < len ; ++i)
		units[i] = chars;

	for (; *units[0] ; units[b] -= n){
		for (i = 0; i < n ; ++i,s = 1,units[b]++){
			for (j = 0; j < len ; ++j){
				if ( j < len-2 && ismatch((*units[j]),(*units[j+1])))
					break;
				comb[j] = *units[j];
			}
			if (j == len){
				for (j = 0; s && j < len-1 ;j++){
					for (k = j+1; k < len ;k++)
						if (comb[j] == comb[k])
							s = 0;
				}
				if (s)
				  if (piped)
					printf("%s",comb);
				  else
				  	fputs(comb,fp);
			}
		}
		for (x = b - 1; x >= 0 && !*++units[x] ;--x)
			units[x] -= x ? n : 0;
	}
	return 0;
}