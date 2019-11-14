#include <stdio.h>
#include <string.h>

#include "str.h"
#include "program.h"

void qkbk_print_str(char *str) 
{
	qkbk_write_str("s_load \"");
	qkbk_write_str(str);
	qkbk_write_str("\"\ns_print\ns_pop\n");
}

void qkbk_print_nl() 
{
	qkbk_print_str(" ");
}
