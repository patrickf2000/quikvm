; loop2
; This gives an example of what a simple loop may look like
; The difference is that it tests function calls

s_load "Saying hello a few times..."
s_print

i_load 0
i_var x
i_store x

lbl loop
	call sayHello

	i_load_var x
	i_load 1
	i_add
	
	i_cmp 10
	je done
	
	i_store x
	jmp loop
	
lbl done
	s_load "Done!"
	s_print
	exit
	
lbl sayHello
	s_load "Hello!"
	s_print
	s_pop
	ret
