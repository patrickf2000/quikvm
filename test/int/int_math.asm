s_load "Enter two numbers:"
s_print
i_var no1
i_var no2
i_input
i_input
i_var no1
i_var no2
i_store no1
i_store no2
i_load_var no1
i_load_var no2
s_load "The sum is:"
s_print
i_add
i_print
i_pop
s_load "The product is:"
s_print
i_load_var no1
i_load_var no2
i_mul
i_print
i_pop
s_load "The difference is:"
s_print
i_load_var no1
i_load_var no2
i_sub
i_print
i_pop
s_load "The quotient is:"
s_print
i_load_var no1
i_load_var no2
i_div
i_print
i_pop
s_load "The remainder is:"
s_print
i_load_var no1
i_load_var no2
i_mod
i_print
i_pop
exit
