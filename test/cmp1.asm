s_load "Enter a number:"
s_print
s_pop
i_input
i_cmp 10
je eq
jne neq
lbl eq
s_load "It is equal to 10!"
s_print
s_pop
jmp done
lbl neq
s_load "It is not equal to 10!"
s_print
s_pop
lbl done
exit
