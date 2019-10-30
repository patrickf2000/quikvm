s_load "Enter a number:"
s_print
s_pop
i_input
i_cmp 10
je eq
jl less
jg greater
lbl eq
s_load "It is equal to 10!"
s_print
s_pop
jmp done
lbl less
s_load "It is less than 10!"
s_print
s_pop
jmp done
lbl greater
s_load "It is greater than 10!"
s_print
s_pop
lbl done
exit
