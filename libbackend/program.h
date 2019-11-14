#pragma once

#include <stdio.h>

extern FILE *fp;

void qkbk_write_str(char *str);
void qkbk_write_int(int i);
void qkbk_write_nl();

void qkbk_init(char *path);
void qkbk_write_comment(char *ln);
void qkbk_close();
