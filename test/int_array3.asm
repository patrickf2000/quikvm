i_array num 5

i_var x
i_load 0
i_store x

i_var n
i_load 7
i_store n

lbl lp
	i_load_var n
	i_store num+x
	
	i_load 1
	i_load_var n
	i_sub
	i_store n
	
	i_load_var x
	i_cmp 4
	je done
	
	i_load_var x
	i_load 1
	i_add
	i_store x
	jmp lp
	
lbl done
	s_load "Done!"
	s_print
	exit
