lib "io>open:str;void"
lib "io>getln:void;str"
lib "io>is_eof:void;int"
lib "io>close:void;void"

s_load "file.txt"
excall "open"

lbl read
	excall "getln"
	s_print
	s_pop

	excall "is_eof"
	i_cmp 1
	jne read

lbl done
	s_load "Done!"
	s_print
	
	excall "close"
	exit
