#include <string.h>
#include <stdio.h>
#include <stdlib.h>

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
void qkbk_imath(char *n1, char *n2, char *rval, char op)
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
	
	//do work
	switch (op)
	{
		case '+': qkbk_write_str("\ni_add\n"); break;
		case '-': qkbk_write_str("\ni_sub\n"); break;
		case '*': qkbk_write_str("\ni_mul\n"); break;
		case '/': qkbk_write_str("\ni_div\n"); break;
		case '%': qkbk_write_str("\ni_mod\n"); break;
		default: {
			puts("Error: Unknown mathematical operation.");
			exit(1);
		}
	}
	
	qkbk_write_str("i_store ");
	qkbk_write_str(rval);
	qkbk_write_nl();
}

//The next five are wrapper functions to make people's life easier
// and to make code more readable
void qkbk_iadd(char *n1, char *n2, char *rval)
{
	qkbk_imath(n1, n2, rval, '+');
}

void qkbk_isub(char *n1, char *n2, char *rval)
{
	qkbk_imath(n1, n2, rval, '-');
}

void qkbk_imul(char *n1, char *n2, char *rval)
{
	qkbk_imath(n1, n2, rval, '*');
}

void qkbk_idiv(char *n1, char *n2, char *rval)
{
	qkbk_imath(n1, n2, rval, '/');
}

void qkbk_imod(char *n1, char *n2, char *rval)
{
	qkbk_imath(n1, n2, rval, '%');
}
