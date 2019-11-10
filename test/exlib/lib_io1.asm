lib "io>open:str;void"
lib "io>getln:void;str"
lib "io>is_eof:void;int"
lib "io>close:void;void"

s_load "file.txt"
excall "open"

excall "getln"
s_print
s_pop

excall "getln"
s_print
s_pop

excall "getln"
s_print
s_pop

excall "is_eof"
i_cmp 1
je y_eof
jmp n_eof

lbl y_eof
	s_load "We are at end."
	s_print
	jmp done

lbl n_eof
	s_load "We aren't done!!"
	s_print

lbl done
	excall "close"
	exit
