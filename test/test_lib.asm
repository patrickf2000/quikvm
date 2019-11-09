s_load "Testing an external function:"
s_print

i_load 5

excall "test>test1"
excall "test>test2:int"

i_pop
i_load 8

excall "test>test2:int"

exit
