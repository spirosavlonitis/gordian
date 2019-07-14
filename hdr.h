#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX_LENGTHS 10

int allcombs(char *,int);
int matchcombs(char *,int);
int uniquecombs(char *,int);
int singlecombs(char *,int);

void sizecalc(int,int *);
void error(char *fmt,...);

double total_cmbs;
int matching,unique,single,piped,bknown,save,restore,len[MAX_LENGTHS];
char *chars,*prog,*fname,*bpattern;
FILE *fp;