s_load "Testing an external function:"
s_print

i_load 5

excall "test>test1"
excall "test>test2:int"

i_pop
i_load 8

excall "test>test2:int"

s_load ""
s_print

d_load 3.14

excall "test>test3:dec"

exit
