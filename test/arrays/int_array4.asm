i_array nums 3

i_var x
i_load 2
i_store x

i_load 1
i_load 2
i_load 3

i_store nums
i_store nums+1
i_store nums+2

i_load_arr nums+1
i_print

i_load_arr nums+x
i_print

exit
