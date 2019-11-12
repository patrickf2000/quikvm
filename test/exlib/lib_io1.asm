lib "qkio>open:str;void"
lib "qkio>getln:void;str"
lib "qkio>is_eof:void;int"
lib "qkio>close:void;void"

s_load "file.txt"
excall "open"

lbl read
	excall "getln"
	s_print
	s_pop

	excall "is_eof"
	i_cmp 0
	jne read

lbl done
	s_load "Done!"
	s_print
	
	excall "close"
	exit
