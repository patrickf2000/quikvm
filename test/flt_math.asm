s_load "Enter two decimal numbers:"
s_print
d_var no1
d_var no2
d_input
d_input
d_var no1
d_var no2
d_store no1
d_store no2
d_load_var no1
d_load_var no2
s_load "The sum is:"
s_print
d_add
d_print
d_pop
s_load "The product is:"
s_print
d_load_var no1
d_load_var no2
d_mul
d_print
d_pop
s_load "The difference is:"
s_print
d_load_var no1
d_load_var no2
d_sub
d_print
d_pop
s_load "The quotient is:"
s_print
d_load_var no1
d_load_var no2
d_div
d_print
d_pop
exit
