#include <stdio.h>
#include <string.h>
#include <malloc.h>
#include <stdlib.h>

//String length
int str_len(void *arg)
{
	char *str = *(char **)arg;
	return strlen(str);
}

//Convert a string to an integer
int str2int(void *arg)
{
	char *str = *(char **)arg;
	int no = atoi(str);
	return no;
}

//The test function
char *test_str_ret()
{
	const char *str = "Hello!";
	int len = strlen(str);
	char *ret = malloc(len+1);
	
	for (int i = 0; i<len; i++)
	{
		ret[i] = str[i];
	}
	
	return ret;
}

void test_str_in(void *arg)
{
	char *str = *(char **)arg;
	printf("STR: %s\n", str);
}
