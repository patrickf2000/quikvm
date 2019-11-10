lib "test>test1:void;void"
lib "test>test2:int;void"
lib "test>test3:dec;void"
lib "test>test_ret:void;int"
lib "test>test_ret2:int;int"

s_load "Testing an external function:"
s_print

i_load 5

excall "test1"
excall "test2"

i_pop
i_load 8

excall "test2"

s_load ""
s_print

d_load 3.14
excall "test3"

s_print

excall "test_ret"

s_load "Returned"
s_print

i_print

s_pop
s_print

i_load 4
i_print

excall "test_ret2"

s_load "Doubled"
s_print

i_print

exit
