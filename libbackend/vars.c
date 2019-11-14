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
void qkbk_print_const(int val)
{

}

//Prints a variable value
void qkbk_print_ivar(char *name)
{
	qkbk_write_str("i_load_var ");
	qkbk_write_str(name);
	qkbk_write_nl();

	qkbk_write_str("i_print\n");
}
