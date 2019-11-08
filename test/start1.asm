lbl first
	s_load "Hello!"
	s_print
	s_load "You should not see this!"
	s_print
	
lbl _start
	s_load "Welcome!"
	s_print
	s_load "This is the not-first main function!"
	s_print
	
	exit
