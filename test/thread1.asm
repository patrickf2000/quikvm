lbl start
	s_load "Starting the threads!"
	s_print
	
	new_thread thread1
	new_thread thread2
	new_thread thread3
	
	s_load "All done!"
	s_print
	exit

lbl thread1
	s_load "Thread 1!"
	s_print
	sleep 3
	jmp done

lbl thread2
	s_load "Thread 2!"
	s_print
	sleep 1
	jmp done

lbl thread3
	s_load "Thread 3!"
	s_print
	sleep 4
	jmp done
	
lbl done
