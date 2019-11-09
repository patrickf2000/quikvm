#include <stdio.h>

//Test calling a function without args
void test1()
{
	puts("Test 1-> Success!");
}

//Tests calling a function with arguments
void test2(void *arg)
{
	int x = *(int *)arg;
	puts("Test 2-> Success!");
	printf("Arg: %d\n", x);
}
