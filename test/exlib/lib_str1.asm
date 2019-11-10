s_load "Testing string library."
s_print

s_load "Input!!"
excall "str>test_str_in:str;void"
s_pop

excall "str>test_str_ret:void;str"
s_print

exit
