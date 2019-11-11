#include <stdio.h>
#include <string.h>
#include <malloc.h>
#include <stdlib.h>

FILE *f;
int c;

void open(void *arg)
{
	char *path = *(char **)arg;
	f = fopen(path, "r");
	
	if (f == NULL) {
		puts("Unable to open file.");
		exit(1);
	}
}

char *getln()
{
	int len = 100;
	char *ln = malloc(len+1);
	int i = 0;
	c = 0;
	
	while (((c = fgetc(f)) != EOF) && (i < len))
	{
		if (c == '\n')
			break;
			
		ln[i] = c;
		++i;
	}
	
	ln[i] = '\0';
	return ln;
}

int is_eof()
{
	if (c == EOF) return 1;
	return 0;
}

void close()
{
	fclose(f);
}
