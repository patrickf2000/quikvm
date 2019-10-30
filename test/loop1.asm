; loop1
; This gives an example of what a simple loop may look like

s_load "Counting to 10:"
s_print

i_load 0
i_var x
i_store x

lbl loop
	i_load_var x
	i_print
	
	i_load 1
	i_add
	
	i_cmp 11
	je done
	
	i_store x
	jmp loop
	
lbl done
	s_load "Done!"
	s_print
	exit
	
