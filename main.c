#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>


#define LENGTHS_MAX 10

static void readargs(int,char **);
static void error(char *fmt,...);
int allcombs(char *,int);
int matchcombs(char *,int);
int uniquecombs(char *,int);
int singlecombs(char *,int);

int all,matching,unique,single,piped,len[LENGTHS_MAX];
char *chars,*prog;


int main(int argc,char *argv[])
{
	all = 1;
	matching = unique = single = piped = 0;
	prog = *argv;

	//if (argc < 3)
	//	error("Usage: %s 6 0123456789\n",prog);

	//readargs(argc,argv);
	chars = "0123456789";

	allcombs(chars,8);
	
	exit(0);

}

static void readargs(int argc,char **argv)
{
	int i,n;

	for ( i = 1; --argc > 0 ;i++){
		if (*argv[i] == '-')
			while(*++argv[i])
				switch (*argv[i]){
					case 'p':
						piped = 1;
						break;
					case 'm':
						matching =  1;
						all = 0;
						break;
					case 'u':
						unique = 1;
						all = 0;						
						break;
					case 's':
						single = 1;
						all = 0;						
						break;
					case 'a':
						all = 1;
						break;
					default:
						error("unknown option %c \n",*argv[i]);
						break;
				}
			else if (atoi(argv[i])){
				printf("%d\n",atoi(argv[i]));
			}
	}

}

static void error(char *fmt,...)
{
	va_list args;

	va_start(args,fmt);
	vfprintf(stderr,fmt,args);
	va_end(args);

	exit(1);
}