lib "str>test_str_in:str;void"
lib "str>test_str_ret:void;str"

s_load "Testing string library."
s_print

s_load "Input!!"
excall "test_str_in"
s_pop

excall "test_str_ret"
s_print

exit
