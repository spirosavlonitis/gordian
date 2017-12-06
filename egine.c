#include <stdio.h>
#include <string.h>

static unsigned long power(int,int);

int allcombs(char *chars,int len)
{
	unsigned long poss;
	register int i,j,b,x,total,n;
	char *units[len],comb[len+2];

	total = 0;
	b = len-1;
	x = b-1;
	n = strlen(chars);
	poss = power(n,len)/n +1;
	comb[len] = '\n';
	comb[len+1] = '\0';

	for (i = 0; i < len ; ++i)
		units[i] = chars;

	while (*units[0]){
		/*iterate n times so that each units[b]++
		can be printed */
		for (i = 0; i < n ; ++i){
			/* iterate though the unit pointers */
			for (j = 0; j < len ; j++)
				/* load the comb array*/
				comb[j] =*units[j];
			printf("%s",comb);
			/* increment the rightmost char */
			units[b]++;
			/* if '\0' reset*/
			if (!*units[b])
			  units[b] -= n;
		}
		/* if x is a valid index starting one index less
		than the right most index */
		/* increment the char that units[x] points to */
		/* if *units[x] is '\0' reset untis[x] and decrement x */
		/* repeat the process until all the first non '\0' has been found */
		/* or all indexes have been exausted */
		for (; x >= 0 && *++units[x] == '\0' ;--x)
			units[x] -= x ? n : 0;
		/* reset x to one inxed less than the righmost index */
		x = b-1;
		total += 10;
	}

	printf("%d\n",total);

	return 0;
}

#define ismatch(A,B)		((A) == (B))

int matchcombs(char *chars,int len)
{
	unsigned long poss,total;
	register int i,j,b,x,n,match;
	char *units[len],comb[len+2];

	total = 0;
	match = 0;
	comb[len] = '\n';
	comb[len+1] = '\0';
	b = len-1;
	x = b-1;
	n = strlen(chars);
	poss = power(n,len)/n + 1;

	for (i = 0; i < len; ++i)
		units[i] = chars;

	while (*units[0]){
		for (i = 0; i < n ; ++i,match = 0){	
			for (j = 0; j < len ; ++j){
				comb[j] = *units[j];
				if (!match && j <= (len-2) && ismatch((*units[j]),*units[j+1]))
					match = 1;				
			}
			if (match)
				printf("%s",comb);
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
	unsigned long poss,total;
	register int i,j,b,x,n;
	int match;
	char *units[len],comb[len+2];

	total = 0;
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
			if (j == len ){
				printf("%s",comb);
				total += 1;
			}
			if (!*++units[b])
				units[b] -= n;
		}
		for (;x >= 0 && *++units[x] == '\0';--x)
			units[x] -= x ? n : 0;
		x = b-1;
	}
	printf("%ld\n",total);
	return 0;
}

int singlecombs(char *chars,int len)
{
	register int i,j,k,b,x,s,total,match;
	int n;
	char *units[len],comb[len],scomb[len+2];

	total = 0;
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
			if (j == len){
				for (j = 0; s && j < len-1 ;j++){
					for (k = j+1; k < len ;k++)
						if (comb[j] == comb[k])
							s = 0;
				}
				if (s){
					printf("%s",comb);
					total++;
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
	printf("%d\n",total);
	return 0;
}

static unsigned long power(int b,int p)
{	
	int n;

	n = b;
	while (--p)
		n *= b;
	
	return n;
}