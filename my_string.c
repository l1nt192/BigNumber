#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include "my_string.h"
void* my_memcpy(void* dest, const void* src, size_t n)
{
    unsigned char* d = (unsigned char*)dest;
    const unsigned char* s = (const unsigned char*)src;
    while (n--) {
        *d++ = *s++;
    }
    return dest;
}

void* my_memmove(void* dest, const void* src, size_t n)
{
    unsigned char* d = (unsigned char*)dest;
    const unsigned char* s = (const unsigned char*)src;
    if (d < s) {
        while (n--) {
            *d++ = *s++;
        }
    }
    else {
        const unsigned char* lasts = s + (n - 1);
        unsigned char* lastd = d + (n - 1);
        while (n--) {
            *lastd-- = *lasts--;
        }
    }
    return dest;
}

bool IsIntString(const char* str)
{
    if (str == NULL || *str == '\0') {
        return false;
    }

    if (*str == '-') {
        str++;
    }

    while (*str) {
        if (!isdigit(*str)) {
            return false;
        }
        str++;
    }
    return true;
}