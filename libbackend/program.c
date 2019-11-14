#include <stdio.h>
#include <string.h>

#include "program.h"

FILE *fp;

void qkbk_init(char *path)
{
	fp = fopen(path, "w");
}

void qkbk_write_comment(char *ln)
{
	int len = strlen(ln);
	fwrite(";", sizeof(char), 1, fp);
	fwrite(ln, sizeof(char), len, fp);
	fwrite("\n", sizeof(char), 1, fp);
}

void qkbk_close() 
{
	fclose(fp);
}
