#include "hdr.h"
#include <stdarg.h>

#define MAX_CHARS	1000
#define MAX_LENGTH 	3

static void readargs(int,char **);
static void expand(char *);
static void simplesort(int *);

int main(int argc,char *argv[])
{
	char expchars[MAX_CHARS];

	matching = unique = single = piped = bknown = save = restore = 0;
	prog = *argv++;
	chars = NULL;
	fp = NULL;

	if (argc < 2)
		error("Usage: %s  -l 6 0123456789 filename\n",prog);

	readargs(argc,argv);
	if (chars == NULL)
		error("No characters entered !!\n");
	else if (fp == NULL && piped == 0)
		error("No file name provided !!\n");
	
	expand(expchars);
	simplesort(len);


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

static void help_message(void);

static void readargs(int argc,char **argv)
{
	int i,j,n;
	char l[3];

	j = 0;
	for (; --argc > 0 ;argv++){
		if (**argv == '-') {
			while(*++*argv) {
				switch (**argv) {
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
					case 'l':
						--argc;
						for (++argv; **argv ;++*argv)
							if ( **argv == ',' )
								continue;
							else if (j < MAX_LENGTHS){
								for (i=0; **argv && i < 2 && **argv != ',';i++,++*argv)
									l[i] = **argv;
								l[i] = '\0';
								len[j++] = atoi(l);
								*argv -= 1;
							}else
								error("%s: too many lengths max allowed %d\n",prog,MAX_LENGTHS);
							*argv -= 1;
						break;
					case 'b':
						bknown = 1;
						bpattern = strdup(*++argv);
						(*argv) += strlen(bpattern) - 1;
						--argc;
						break;
					case 'r':
						restore = 1;
						break;
					case '-':
						--argc;
						*++*argv;
						if (strcmp("save",*argv) == 0){
							save = atoi(*++argv);
							*argv += strlen(*argv) -1;
						}else if (strcmp("help",*argv) == 0)
							help_message();
						else
							error("%s: unknown option %s\n",prog,*argv);
						break;
					default:
						error("unknown option %c \n",**argv);
						break;
				}
			  }	
			}else if (chars == NULL)
				chars = strdup(*argv);
			else if (!piped && chars)
				fname = strdup(*argv);
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

static void help_message(void)
{
	char *message;
	message = "Available options:\n"\
	"-a\tall possible combinations, if no option is given -a is implied.\n"\
	"-m\tmatching character combinations will be generated, i.e 0112\n"\
	"-u\tnon matching character combinations will be generated, i.e 131\n"\
	"-s\tcombinations of unique characters will be generated,  i.e 0123\n"\
	"-p\tcombinations are printed to the stdout stream, used for piping\n"\
	"-b\tpattern to be added before generated combinations, i.e 12***\n"\
	"-l\tspecifies the length of the combinations to be generated, i.e 6 or 6,7,8\n"\
	"-r\trestore last session,i.e prog_name -rl 6 0-9 filename\n"\
	"--save\tsaves progress to the specified percentage e.g 30.\n"\
	"\tif restoring from 30%% and --save 60 what is generated is 30%%-60%%\n"\
	"--help\tprints this message.\n";
	error(message);
}

static void simplesort(int *l)
{
	int i,j,temp;
	for (j = 1; l[j] ; j++)
		for (i = j-1; i >= 0 && l[i] > l[i+1] ; --i)
			temp = l[i],l[i] = l[i+1],l[i+1] = temp;
}

void error(char *fmt,...)
{
	va_list args;

	va_start(args,fmt);
	vfprintf(stderr,fmt,args);
	va_end(args);

	exit(1);
}