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

//Test double
void test3(void *arg)
{
	double d = *(double *)arg;
	puts("Test 3-> Success!");
	printf("Float Arg: %f\n", d);
}

//Test return
int test_ret()
{
	puts("Returning 6:");
	return 6;
}

int test_ret2(void *arg)
{
	int x = *(int *)arg;
	return x*x;
}
