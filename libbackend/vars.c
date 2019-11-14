#include <string.h>

#include "vars.h"
#include "program.h"

//Creates a new integer variable
void qkbk_new_ivar(char *name, int val)
{
	//i_var <name>
	qkbk_write_str("i_var ");
	qkbk_write_str(name);
	qkbk_write_nl();
	
	//i_load <val>
	qkbk_write_str("i_load ");
	qkbk_write_int(val);
	qkbk_write_nl();
	
	//i_store <name>
	qkbk_write_str("i_store ");
	qkbk_write_str(name);
	qkbk_write_nl();
}

//Prints a constant value
void qkbk_print_iconst(int val)
{
	qkbk_write_str("i_load ");
	qkbk_write_int(val);
	qkbk_write_str("\ni_print\ni_pop\n");
}

//Prints a variable value
void qkbk_print_ivar(char *name)
{
	qkbk_write_str("i_load_var ");
	qkbk_write_str(name);
	qkbk_write_nl();

	qkbk_write_str("i_print\n");
}

//Prints a floating-point constant
void qkbk_print_dconst(double val)
{
	qkbk_write_str("d_load ");
	qkbk_write_dec(val);
	qkbk_write_str("\nd_print\nd_pop\n");
}
