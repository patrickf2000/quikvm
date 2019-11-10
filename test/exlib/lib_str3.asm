s_load "Converting 10 to int"
s_print

s_load "Int stack top:"
s_print

i_load 5
i_print

s_load "10"
excall "str>str2int:str;int"

s_pop
s_print

i_print

exit
