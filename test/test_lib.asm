s_load "Testing an external function:"
s_print

i_load 5

excall "test>test1"
excall "test>test2:int"

exit
