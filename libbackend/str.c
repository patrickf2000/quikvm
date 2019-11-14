#include <stdio.h>
#include <string.h>

#include "str.h"
#include "program.h"

void qkbk_print_str(char *str) 
{
	char *ln1 = "s_load \"";
	char *ln2 = "\"\n";
	char *ln3 = "s_print\n";
	char *ln4 = "s_pop\n";
	
	fwrite(ln1, sizeof(char), strlen(ln1), fp);
	fwrite(str, sizeof(char), strlen(str), fp);
	fwrite(ln2, sizeof(char), strlen(ln2), fp);
	fwrite(ln3, sizeof(char), strlen(ln3), fp);
	fwrite(ln4, sizeof(char), strlen(ln4), fp);
}

void qkbk_print_nl() 
{
	qkbk_print_str(" ");
}
