#include <stdio.h>

#include <program.h>
#include <vars.h>
#include <str.h>

void main()
{
	qkbk_init("test2.asm");
	qkbk_write_comment("This tests math.");
	
	qkbk_print_str("Arithmetic Tests");
	qkbk_print_nl();
	
	qkbk_close();
}
