#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LENGTHS 10
#define MAX_CHARS	1000

int allcombs(char *,int);
int matchcombs(char *,int);
int uniquecombs(char *,int);
int singlecombs(char *,int);

void sizecalc(int,int *);

double total_cmbs;
int all,matching,unique,single,piped,bknown,len[MAX_LENGTHS];
char *chars,*prog,*fname,*bpattern;
FILE *fp;