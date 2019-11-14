#include <string.h>

#include "vars.h"
#include "program.h"

//Creates a new integer variable
void qkbk_new_ivar(char *name, int val)
{
	char *ln1 = "i_var ";
	char *ln2 = "i_load ";
	char *ln3 = "i_store ";
	
	//i_var <name>
	fwrite(ln1, sizeof(char), strlen(ln1), fp);
	fwrite(name, sizeof(char), strlen(name), fp);
	fwrite("\n", sizeof(char), 1, fp);
	
	//i_load <val>
	char buf[5];
	sprintf(buf, "%d", val);
	
	fwrite(ln2, sizeof(char), strlen(ln2), fp);
	fwrite(buf, sizeof(char), 5, fp);
	fwrite("\n", sizeof(char), 1, fp);
	
	//i_store <name>
	fwrite(ln3, sizeof(char), strlen(ln3), fp);
	fwrite(name, sizeof(char), strlen(name), fp);
	fwrite("\n", sizeof(char), 1, fp);
}

//Prints a constant value
void qkbk_print_const(int val)
{

}

//Prints a variable value
void qkbk_print_ivar(char *name)
{
	char *ln1 = "i_load_var ";
	fwrite(ln1, sizeof(char), strlen(ln1), fp);
	fwrite(name, sizeof(char), strlen(name), fp);
	fwrite("\n", sizeof(char), 1, fp);

	char *p_ln = "i_print\n";
	fwrite(p_ln, sizeof(char), strlen(p_ln), fp);
}
