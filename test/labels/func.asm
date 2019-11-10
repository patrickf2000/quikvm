s_load "Welcome!"
s_print
s_load "Calling a function:"
s_print

call sayHello

s_load "Done"
s_print

exit

lbl sayHello
	s_load "Hello!"
	s_print
	s_pop
	ret
