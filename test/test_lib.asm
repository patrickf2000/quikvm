s_load "Testing an external function:"
s_print

i_load 5

excall "test>test1:void;void"
excall "test>test2:int;void"

i_pop
i_load 8

excall "test>test2:int;void"

s_load ""
s_print

d_load 3.14
excall "test>test3:dec;void"

s_print

excall "test>test_ret:void;int"

s_load "Returned"
s_print

i_print

s_pop
s_print

i_load 4
i_print

excall "test>test_ret2:int;int"

s_load "Doubled"
s_print

i_print

exit
