s_load "Enter a number:"
s_print
s_pop
i_input
i_cmp 10
jge ge
jle le
lbl ge
s_load "It is greater than or equal to 10!"
s_print
s_pop
jmp done
lbl le
s_load "It is less than or equal to 10!"
s_print
s_pop
lbl done
exit
