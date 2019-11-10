#include <stdio.h>
#include <string.h>
#include <malloc.h>

//String length
int str_len(void *arg)
{
	char *str = *(char **)arg;
	return strlen(str);
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
