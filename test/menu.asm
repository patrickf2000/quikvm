; The main menu label
lbl menu
	; Print the options
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

	; Clean out the string stack
	s_pop
	s_pop
	s_pop
	s_pop
	s_pop
	s_pop

	; Get input and do comparison tests
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
	
	; If we have an invalid entry, re-display the menu
	jmp menu

; The addition option (option 1)
lbl add_option
	s_load "Add!"
	s_print
	jmp done

; The subtraction option (option 2)
lbl sub_option
	s_load "Sub!"
	s_print
	jmp done

; The multiplication option (option 3)
lbl mp_option
	s_load "Mul!"
	s_print
	jmp done

; The division option (option 4)
lbl div_option
	s_load "Div!"
	s_print
	jmp done

; Displays a message and exits
lbl done
	s_load "Goodbye!"
	s_print
	exit
