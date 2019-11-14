#include <stdio.h>

#include <program.h>
#include <vars.h>
#include <str.h>
#include <math.h>

void main()
{
	qkbk_init("test2.asm");
	qkbk_write_comment("This tests math.");
	
	qkbk_print_str("Arithmetic Tests");
	qkbk_print_nl();
	
	qkbk_new_ivar("result", 0);
	qkbk_iadd("3", "38", "result");
	qkbk_print_ivar("result");
	
	qkbk_new_ivar("x2", 0);
	qkbk_iadd("10", "result", "x2");
	qkbk_print_ivar("x2");
	
	qkbk_new_ivar("x3", 0);
	qkbk_iadd("x2", "result", "x3");
	qkbk_print_ivar("x3");
	
	qkbk_close();
}
