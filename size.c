#include "hdr.h"

static long power(long,long);
static long matchcalc(int,int);
static long singlecal(int,int);

static char stype[] = {
	'B','K','M','G','T','P','E','Z','Y'
};

void sizecalc(int b,int *l)
{
	long n;
	double s;
	int i,c;

	for (n = 0,s = 0; *l ; s += (double) n * (*l+1 + (bknown ? strlen(bpattern): 0)),l++)
		if (all)
			n += power(b,*l);
		else if (matching)
			n += matchcalc(b,*l);
		else if (unique)
			n += power(b,*l) - matchcalc(b,*l);
		else
			n += singlecal(b,*l);

	printf("Combinations: %ld\n",n);
	for (i = 0; s >= 1024 ; ++i,s /= 1024)
		;
		printf("File size: %.1f%c\n",s,stype[i]);

	printf("Continue (y|Y n|N): ");
	c = getchar();

	if (c != 'y' && c != 'Y') {
		fclose(fp);
		printf("Goodbye\n");
		exit(0);
	}

}

static long matchcalc(int b,int l)
{	
	long n,i;

	n = b;
	l -= 2;
	for ( i = 1 ; i <= l ;i++)
		n = (n+(power((b-1),i))) * b;

	return n;
}

static long singlecal(int b,int l)
{
	long n;

	for (n = 1; l ; l--,b--)
		n *= b;

	return n;
}

static long power(long b,long p)
{
	long n;

	n = b;
	while (--p)
		n *= b;

	return n;
}