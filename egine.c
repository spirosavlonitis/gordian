#include "hdr.h"
#include <stdio.h>
#include <string.h>
#include <sys/syscall.h>

#define MAX_WORD	1000
#define PER_BASE 	20

static double current_cmbs = 0.0;
static int percent,p = PER_BASE;
char new_comb[MAX_WORD];

int allcombs(char *chars,int len)
{
	register int i,j,b,x,n;
	char *units[len],comb[len+2];
	
	b = len-1;
	x = b-1;
	n = strlen(chars);
	comb[len] = '\n';
	comb[len+1] = '\0';

	for (i = 0; i < len ; ++i)
		units[i] = chars;

	while (*units[0]){
		/*iterate n times so that each units[b]++ can be printed */
		for (i = 0; i < n ; ++i){
			/* iterate though the unit pointers */
			for (j = 0; j < len ; j++)
				comb[j] =*units[j];	/* load the comb array*/
			if (piped)
				printf("%s%s", bknown ? bpattern : "" ,comb);
			else {
				if (bknown){
					sprintf(new_comb,"%s%s",bpattern,comb);
					fputs(new_comb,fp);
				}else
					fputs(comb,fp);

				current_cmbs++;	/* Increace combination count*/
				if (((percent = (int) current_cmbs / total_cmbs * 100.0)) == p){	/* If percentage base or multiple has been reached*/
					fprintf(stderr, "%d%c complete\n",percent,'%');
					p += PER_BASE; 
				}
			}
			/* increment the rightmost char */
			units[b]++;
			/* if '\0' reset*/
			if (*units[b] == '\0')
			  units[b] -= n;
		}

		/* if x is a valid index starting one index less
		than the right most index */
		/* increment the the *(units+x)  pointer */
		/* if *units[x] is '\0' reset untis[x] and decrement x */
		/* so the units point to its left can be accessed */
		/* repeat the process until the first non '\0' has been found */
		/* or all indexes have been exausted */
		for (; x >= 0 && *++units[x] == '\0' ;--x)
			units[x] -= x ? n : 0; /* reset all but the very left index */
		/* reset x to one inxed less than the righmost index */
		x = b-1;
	}
	return 0;
}

#define ismatch(A,B)		((A) == (B))

int matchcombs(char *chars,int len)
{
	unsigned long total;
	register int i,j,b,x,n,match;
	char *units[len],comb[len+2];

	total = 0;
	match = 0;
	comb[len] = '\n';
	comb[len+1] = '\0';
	b = len-1;
	x = b-1;
	n = strlen(chars);

	for (i = 0; i < len; ++i)
		units[i] = chars;

	while (*units[0]){
		for (i = 0; i < n ; ++i,match = 0){	
			for (j = 0; j < len ; ++j){
				comb[j] = *units[j];
				if (!match && j <= (len-2) && ismatch((*units[j]),*units[j+1]))
					match = 1;
			}
			current_cmbs++;
			if (match)
				if (piped)
					printf("%s%s", bknown ? bpattern : "" ,comb);
				else{
					if (bknown){
						sprintf(new_comb,"%s%s",bpattern,comb);
						fputs(new_comb,fp);
					}else
						fputs(comb,fp);
					if (((percent = (int) current_cmbs / total_cmbs * 100.0)) == p){	/* If percentage base or multiple has been reached*/
						fprintf(stderr, "%d%c complete\n",percent,'%');
						p += PER_BASE; 
					}
				}
			if (!*++units[b])
				units[b] -= n;
		}
		for (;x >= 0 && *++units[x] == '\0';--x)
			units[x] -= x ? n : 0;
		x = b-1;
	}
	return 0;
}

int uniquecombs(char *chars,int len)
{
	unsigned long poss;
	register int i,j,b,x,n;
	int match;
	char *units[len],comb[len+2];

	comb[len] = '\n';
	comb[len+1] = '\0';
	b = len-1;
	x = b-1;
	n = strlen(chars);

	for (i = 0; i < len; ++i)
		units[i] = chars;

	while (*units[0]){
		for (i = 0; i < n ; ++i){			
			for (j = 0; j < len ; ++j){
				if (j <= (len-2) && ismatch((*units[j]),(*units[j+1])))
					break;
				comb[j] = *units[j];
			}
			current_cmbs++;
			if (j == len ){
				if (piped)
					printf("%s%s", bknown ? bpattern : "" ,comb);
				else {
					if (bknown){
						sprintf(new_comb,"%s%s",bpattern,comb);
						fputs(new_comb,fp);
					}else
						fputs(comb,fp);
					if (((percent = (int) current_cmbs / total_cmbs * 100.0)) == p){	/* If percentage base or multiple has been reached*/
						fprintf(stderr, "%d%c complete\n",percent,'%');
						p += PER_BASE; 
					}
				}
			}
			if (!*++units[b])
				units[b] -= n;
		}
		for (;x >= 0 && *++units[x] == '\0';--x)
			units[x] -= x ? n : 0;
		x = b-1;
	}
	if (piped != 1)
		fprintf(stderr, "100%c complete\n",'%');
	return 0;
}

int singlecombs(char *chars,int len)
{
	register int i,j,k,b,x,s,match;
	int n;
	char *units[len],comb[len],scomb[len+2];

	comb[len] = '\n';
	comb[len+1] = '\0';
	b = len -1;
	x = b - 1;
	n = strlen(chars);
	s = 1;

	for (i = 0; i < len ; ++i)
		units[i] = chars;

	while (*units[0]){
		for (i = 0; i < n ; ++i){
			for (j = 0; j < len ; ++j){
				if ( j < len-2 && ismatch((*units[j]),(*units[j+1])))
					break;
				comb[j] = *units[j];
			}
			current_cmbs++;
			if (j == len){
				for (j = 0; s && j < len-1 ;j++){
					for (k = j+1; k < len ;k++)
						if (comb[j] == comb[k])
							s = 0;
				}
				if (s){
					if (piped)
						printf("%s%s", bknown ? bpattern : "" ,comb);
					else {
						if (bknown){
							sprintf(new_comb,"%s%s",bpattern,comb);
							fputs(new_comb,fp);
						}else
							fputs(comb,fp);
						if (((percent = (int) current_cmbs / total_cmbs * 100.0)) == p){	/* If percentage base or multiple has been reached*/
							fprintf(stderr, "%d%c complete\n",percent,'%');
							p += PER_BASE; 
						}
					}							
				}
			}
			if (!*++units[b])
				units[b] -= n;
			s = 1;
		}
		for (; x >= 0 && !*++units[x] ;--x)
			units[x] -= x ? n : 0;
		x = b -1;
	}
	if (piped != 1)
		fprintf(stderr, "100%c complete\n",'%');
	return 0;
}