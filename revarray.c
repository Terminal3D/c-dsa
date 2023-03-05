#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <wchar.h>
void revarray(void *base, size_t nel, size_t width)
{
    char *temp = malloc(width);
    for (size_t i = 0; i < nel / 2; i++)
    {

        memcpy(temp, (char*)base + (nel - (i + 1))* width, width);
        memcpy((char*)base + (nel - (i + 1)) * width, (char*)base + i * width, width);
        memcpy((char*)base + i * width, temp, width);

    }
    free(temp);
}