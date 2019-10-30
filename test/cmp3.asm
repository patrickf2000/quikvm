; This file tests the greater/less than or equal conditions
; Note that by default, if the number is equal to 10, we
; default to the greater than or equal to label.
; If you do not like this, just switch swap the orders of
; the labels.

; Get input
s_load "Enter a number:"
s_print
s_pop
i_input

; Compare with 10
i_cmp 10
jge ge
jle le

; Jump here if greater than or equal to 10
lbl ge
	s_load "It is greater than or equal to 10!"
	s_print
	s_pop
	jmp done

; Jump here if less than or equal to 10
lbl le
	s_load "It is less than or equal to 10!"
	s_print
	s_pop

lbl done
	exit
