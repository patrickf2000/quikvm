lbl menu
s_load "Welcome!"
s_print
s_load "Press 1 to add."
s_print
s_load "Press 2 to subtract."
s_print
s_load "Press 3 to multiply."
s_print
s_load "Press 4 to divide."
s_print
s_load "Press 5 to exit."
s_print
s_pop
s_pop
s_pop
s_pop
s_pop
s_pop
i_input
i_cmp 1
je add_option
i_cmp 2
je sub_option
i_cmp 3
je mp_option
i_cmp 4
je div_option
i_cmp 5
je done
jmp menu
lbl add_option
s_load "Add!"
s_print
jmp done
lbl sub_option
s_load "Sub!"
s_print
jmp done
lbl mp_option
s_load "Mul!"
s_print
jmp done
lbl div_option
s_load "Div!"
s_print
jmp done
lbl done
s_load "Goodbye!"
s_print
exit
