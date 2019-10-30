; Start here and get input
lbl _start
	s_load "Enter a number:"
	s_print
	s_pop
	i_input
	
	; Compare with 10
	i_cmp 10
	je eq
	jl less
	jg greater

; If equal, jump here
lbl eq
	s_load "It is equal to 10!"
	s_print
	s_pop
	jmp done

; If less than 10, jump here
lbl less
	s_load "It is less than 10!"
	s_print
	s_pop
	jmp done

; If greater than 10, jump here
lbl greater
	s_load "It is greater than 10!"
	s_print
	s_pop

; Exit
lbl done
	exit
