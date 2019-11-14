#pragma once

#include <stdio.h>

extern FILE *fp;

void qkbk_init(char *path);
void qkbk_write_comment(char *ln);
void qkbk_close();
