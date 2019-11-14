#include <stdio.h>
#include <string.h>

#include "program.h"

FILE *fp;

//Write a string to our file
void qkbk_write_str(char *str)
{
	fwrite(str, sizeof(char), strlen(str), fp);
}

//Write an integer
void qkbk_write_int(int i)
{
	char buf[5];
	sprintf(buf, "%d", i);
	fwrite(buf, sizeof(char), 5, fp);
}

//Write a newline
void qkbk_write_nl()
{
	fwrite("\n", sizeof(char), 1, fp);
}

//Open the file for writing
void qkbk_init(char *path)
{
	fp = fopen(path, "w");
}

//Write a comment
void qkbk_write_comment(char *ln)
{
	int len = strlen(ln);
	fwrite(";", sizeof(char), 1, fp);
	fwrite(ln, sizeof(char), len, fp);
	fwrite("\n", sizeof(char), 1, fp);
}

//Close and write the file
void qkbk_close() 
{
	char *exit_ln = "exit\n";
	fwrite(exit_ln, sizeof(char), strlen(exit_ln), fp);
	fclose(fp);
}
