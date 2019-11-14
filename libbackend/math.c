#include <string.h>

#include "math.h"
#include "program.h"

//Check to see if a digit is a number
int is_num(char *no)
{
	for (int i = 0; i<strlen(no); i++)
	{
		if (!isdigit(no[i]))
			return 0;
	}
	
	return 1;
}

//Integer math
void qkbk_iadd(char *n1, char *n2, char *rval)
{
	//number 1
	if (is_num(n1))
	{
		qkbk_write_str("i_load ");
		qkbk_write_str(n1);
	}
	else
	{
		qkbk_write_str("i_load_var ");
		qkbk_write_str(n1);
	}
	
	//number 2
	if (is_num(n2))
	{
		qkbk_write_str("\ni_load ");
		qkbk_write_str(n2);
	}
	else
	{
		qkbk_write_str("\ni_load_var ");
		qkbk_write_str(n2);
	}
	
	//add
	qkbk_write_str("\ni_add\n");
	qkbk_write_str("i_store ");
	qkbk_write_str(rval);
	qkbk_write_nl();
}
