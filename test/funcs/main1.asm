lbl _start
	s_load "Calling function:"
	s_print
	s_pop

	call sayHello

	s_load "Done!"
	s_print
	s_pop

	exit
