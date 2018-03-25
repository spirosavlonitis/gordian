#include "hdr.h"
#include <stdio.h>
#include <string.h>
#include <sys/syscall.h>

#define MAX_WORD	1000
#define PER_BASE 	20.0

static void set_save(char *,char *,long,double,int);
static void set_restore(char **,char *,double *);

static double current_cmbs = 0.0;
char new_comb[MAX_WORD];
FILE *s_file,*r_file;

int allcombs(char *chars,int len)
{
	register int i,j,b,x,n;
	char *units[len],comb[len+2],c;
	float percent,p;

	b = len-1;
	x = b-1;
	n = strlen(chars);
	comb[len] = '\n';
	comb[len+1] = '\0';
	p = PER_BASE;

	/* Load charactets */
	for (i = 0; i < len ; ++i)
		units[i] = chars;
	
	/* restore section */
	if (restore && (r_file = fopen("save.txt","r"))){
		set_restore(units,chars,&current_cmbs);
		fclose(r_file);
	}

	while (*units[0]){
		/*iterate n times so that each units[b]++ can be printed */
		for (i = 0; i < n ; ++i){
			/* iterate though the unit pointers */
			for (j = 0; j < len ; j++)
				comb[j] =* units[j];	/* load the comb array*/
			if (piped)
				printf("%s%s", bknown ? bpattern : "" ,comb);
			else {
				if (bknown){
					sprintf(new_comb,"%s%s",bpattern,comb);
					fputs(new_comb,fp);
				}else
					fputs(comb,fp);

				current_cmbs++;	/* Increace combination count*/
				if (((percent = (current_cmbs / total_cmbs) * 100.0)) >= p){	/* If percentage base or multiple has been reached */
					fprintf(stderr, "%.0f%% complete\n",percent);
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

		/* Save section */
		if (save && percent >= save) { 
			for (j = 0; j < len ; j++)
				comb[j] =* units[j];
			set_save(comb,chars,(long) current_cmbs,percent,len);
		}
	}
	return 0;
}

#define ismatch(A,B)		((A) == (B))

int matchcombs(char *chars,int len)
{
	unsigned long total;
	register int i,j,b,x,n,match;
	char *units[len],comb[len+2];
	float percent,p;

	total = 0;
	match = 0;
	comb[len] = '\n';
	comb[len+1] = '\0';
	b = len-1;
	x = b-1;
	n = strlen(chars);
	p = PER_BASE;

	for (i = 0; i < len; ++i)
		units[i] = chars;

	if (restore && (r_file = fopen("save.txt","r"))){
		set_restore(units,chars,&current_cmbs);
		fclose(r_file);
	}

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
					if (((percent = current_cmbs / total_cmbs * 100.0)) == p){	/* If percentage base or multiple has been reached*/
						fprintf(stderr, "%.0f%% complete\n",percent);
						p += PER_BASE; 
					}
				}
			if (!*++units[b])
				units[b] -= n;
		}
		for (;x >= 0 && *++units[x] == '\0';--x)
			units[x] -= x ? n : 0;
		x = b-1;

		if (save && percent >= save) { 
			for (j = 0; j < len ; j++)
				comb[j] =* units[j];
			set_save(comb,chars,(long) current_cmbs,percent,len);
		}
	}
	return 0;
}

int uniquecombs(char *chars,int len)
{
	unsigned long poss;
	register int i,j,b,x,n;
	int match;
	char *units[len],comb[len+2];
	float percent,p;

	comb[len] = '\n';
	comb[len+1] = '\0';
	b = len-1;
	x = b-1;
	n = strlen(chars);
	p = PER_BASE;

	for (i = 0; i < len; ++i)
		units[i] = chars;

	if (restore && (r_file = fopen("save.txt","r"))){
		set_restore(units,chars,&current_cmbs);
		fclose(r_file);
	}

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
					if (((percent = current_cmbs / total_cmbs * 100.0)) == p){	/* If percentage base or multiple has been reached*/
						fprintf(stderr, "%.0f%% complete\n",percent);
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
		
		if (save && percent >= save) { 
			for (j = 0; j < len ; j++)
				comb[j] =* units[j];
			set_save(comb,chars,(long) current_cmbs,percent,len);
		}

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
	float percent,p;

	comb[len] = '\n';
	comb[len+1] = '\0';
	b = len -1;
	x = b - 1;
	n = strlen(chars);
	s = 1;
	p = PER_BASE;

	for (i = 0; i < len ; ++i)
		units[i] = chars;

	if (restore && (r_file = fopen("save.txt","r"))){
		set_restore(units,chars,&current_cmbs);
		fclose(r_file);
	}

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
						if (((percent =  current_cmbs / total_cmbs * 100.0)) >= p){	/* If percentage base or multiple has been reached*/
							fprintf(stderr, "%.0f%% complete\n",percent);
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

		if (save && percent >= save) { 
			for (j = 0; j < len ; j++)
				comb[j] =* units[j];
			set_save(comb,chars,(long) current_cmbs,percent,len);
		}
	}
	if (piped != 1)
		fprintf(stderr, "100%% complete\n");
	return 0;
}

/* Set save point */
static void set_save(char *comb,char *chars,long current_cmbs,double percent,int len)
{
	s_file = fopen("save.txt","w");
	fprintf(s_file,"%s%ld\nchars:%s\nlength:%d",comb,current_cmbs,chars,len);
	fprintf(stderr, "%.0f%% complete\n",percent);
	fclose(s_file);
	error("Restore point set\n");
}

/* Set restore point */
static void set_restore(char **units,char *chars,double *current_cmbs)
{
	char c;
	int i;

	/* Set units saved combination */
	for (i = 0; (c = getc(r_file)) != '\n' ; ++i)
		while(*units[i] != c)
			++units[i];

	/* Set current_cmbs to saved combs */
	for (i = 0; (c = getc(r_file)) != '\n' ; ++i)
		*current_cmbs = 10 * *current_cmbs + (c - '0');
}