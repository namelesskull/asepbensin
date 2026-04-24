#ifndef FILE_UTILS_H
#define FILE_UTILS_H

#include <stddef.h>

char *read_file(const char *path, size_t *out_len);
char *read_file_str(const char *path);

#endif
