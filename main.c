#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdarg.h>


#define MAX_LENGTHS 10
#define MAX_CHARS	1000


static void readargs(int,char **);
static void expand(char *);
static void error(char *fmt,...);
int allcombs(char *,int);
int matchcombs(char *,int);
int uniquecombs(char *,int);
int singlecombs(char *,int);

int all,matching,unique,single,piped,len[MAX_LENGTHS];
char *chars,*prog;


int main(int argc,char *argv[])
{
	char expchars[MAX_CHARS];

	all = 1;
	matching = unique = single = piped = 0;
	prog = *argv;

	if (argc < 3)
		error("Usage: %s 6 0123456789\n",prog);

	readargs(argc,argv);
	expand(expchars);
	printf("%s\n",expchars);
	
	exit(0);
}

static void readargs(int argc,char **argv)
{
	int i,j,n,l;

	j = 0;
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
			else if ((n = strlen(argv[i]) <= 2 && n >= 1 && ( l = atoi(argv[i]))))
				if (j < MAX_LENGTHS)
					len[j++] = l;
				else
					error("%s: too many lengths max allowed %d",prog,MAX_LENGTHS);
			else
				chars = argv[i];
	}

}

#define isrange(A,B)	(A >= 'A' && B <= 'Z' || A >= 'a' && B <= 'z' || A >= '0' && B <= '9' )

static void expand(char *expchars)
{
	int i,j,c,lim;

	for (i = 0,j = 0; chars[i] ; ++i)
		if (chars[i] == '-'){
			if (i == 0)
				error("%s: invalid range dash\n",prog);
			else{
				lim = chars[++i];
				if (lim == '\0')
					error("%s: invalid end of range\n",prog);
				c = expchars[j-1];
				if (isrange(c,lim))
				while (++c <= lim)
					expchars[j++] = c;
				else
					expchars[j++] = lim;

			}

		}else
			expchars[j++] = chars[i];

	expchars[j]	= '\0';
}

static void error(char *fmt,...)
{
	va_list args;

	va_start(args,fmt);
	vfprintf(stderr,fmt,args);
	va_end(args);

	exit(1);
}