#include "hdr.h"
#include <stdarg.h>

#define MAX_CHARS	1000

static void readargs(int,char **);
static void expand(char *);
static void error(char *fmt,...);

int main(int argc,char *argv[])
{
	char expchars[MAX_CHARS];

	all = matching = unique = single = piped = bknown = 0;
	prog = *argv;
	chars = NULL;
	fp = NULL;

	if (argc < 3)
		error("Usage: %s 6 0123456789\n",prog);

	readargs(argc,argv);
	expand(expchars);

	if (!piped){
		if ((fp = fopen(fname,"w")) == NULL)
			error("%s: couldn't open %s\n",prog,fname);
		sizecalc(strlen(expchars),len);
	}
	for (int i = 0; len[i] ; i++)
		if (single)
			singlecombs(expchars,len[i]);
		else if (matching)
			matchcombs(expchars,len[i]);
		else if (unique)
			uniquecombs(expchars,len[i]);
		else
			allcombs(expchars,len[i]);
	
	if (fp)
		fclose(fp);
	
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
						break;
					case 'u':
						unique = 1;
						break;
					case 's':
						single = 1;
						break;
					case 'a':
						all = 1;
						break;
					case 'b':
						bknown = 1;
						bpattern = strdup(argv[++i]);
						--argc;
						argv[i] += strlen(argv[i])-1;
						break;
					case '-':
						argv[i] += 1;
						if (strcmp("save",argv[i]) == 0){
							save = atoi(argv[i+1]);
						}else
							error("%s: unknown option %s\n",prog,argv[i]);
						argv[i] += strlen(argv[i])-1;
						break;
					default:
						error("unknown option %c \n",*argv[i]);
						break;
				}
			else if ( (n = strlen(argv[i])) <= 2 && n >= 1 && (l = atoi(argv[i]))){
				if (j < MAX_LENGTHS)
					len[j++] = l;
				else
					error("%s: too many lengths max allowed %d",prog,MAX_LENGTHS);
			}else if (chars == NULL)
				chars = argv[i];
			else if (!piped && chars)
				fname = argv[i];
	}
	len[j] = 0;
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