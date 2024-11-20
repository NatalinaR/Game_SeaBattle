#pragma once
void line(int cols, const char *start, const char *s, void (chars(int i)), const char *end);

char *bprintf(char *fmt, ...);


void row_header(int j);