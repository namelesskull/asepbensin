#include "file_utils.h"
#include <stdio.h>
#include <stdlib.h>

char *read_file(const char *path, size_t *out_len) {
    FILE *f = fopen(path, "rb");
    if (!f)
        return NULL;

    if (fseek(f, 0, SEEK_END) != 0) {
        fclose(f);
        return NULL;
    }

    long size = ftell(f);
    if (size < 0) {
        fclose(f);
        return NULL;
    }
    rewind(f);

    char *buf = malloc((size_t)size + 1);
    if (!buf) {
        fclose(f);
        return NULL;
    }

    size_t nread = fread(buf, 1, (size_t)size, f);
    fclose(f);

    if (nread != (size_t)size) {
        free(buf);
        return NULL;
    }

    buf[nread] = '\0';

    if (out_len)
        *out_len = nread;

    return buf;
}

char *read_file_str(const char *path) {
    return read_file(path, NULL);
}
