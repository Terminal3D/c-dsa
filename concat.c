#include <stdio.h>
#include <stdlib.h>
#include <string.h>
char *concat(char **s, int n) {
    unsigned long total_size = 0;
    int i = 0;
    while (i < n){
        total_size += strlen(s[i]);
        i++;
    }
    total_size++;
    char* c_cat = (char*)malloc(total_size);
    i = 0;
    unsigned long index = 0;
    while (i < n){
        for(unsigned int j = 0; j < strlen(s[i]); j++){
            c_cat[index] = s[i][j];
            index++;
        }
        i++;
    }
    c_cat[index] = '\0';
    return c_cat;
}








#define MEM(p) must_be_not_null((p), #p, __FILE__, __LINE__)

static void *must_be_not_null(void *p, const char *expr,
                              const char *file, int line)
{
    if (p) return p;

    fprintf(stderr, "%s:%d: '%s' returns NULL\n", file, line, expr);
    abort();
}


static void *memdup(const void *mem, size_t size) {
    void *result = malloc(size);
    if (result) memcpy(result, mem, size);
    return result;
}


static char *mystrdup(const char *str) {
    return memdup(str, strlen(str) + 1);
}


static const char sample[] = "The quick brown fox jumps over the lazy dog";

static void triangle_test(void)
{
    char *sample_copy = MEM(mystrdup(sample));
    char **substrs = MEM(malloc(sizeof(sample) * sizeof(substrs[0])));
    size_t i = 0;
    do {
        substrs[i] = &sample_copy[i];
        ++i;
    } while (sample_copy[i] != 0);

    char *result = concat(substrs, (int) i);
    size_t expected_len = i * (i + 1) / 2;
    size_t real_len = strlen(result);

    if (expected_len != real_len) {
        printf("%s(): expected_len (%zu) != real_len (%zu)\n",
               __func__, expected_len, real_len);
        exit(EXIT_FAILURE);
    }

    char *base = sample_copy;
    char *p = base;
    for (size_t i = 0; i < expected_len; ++i) {
        char expected = *p;
        if (result[i] != expected) {
            printf("%s(): result[%zu] ('%c') != expected char '%c'\n",
                   __func__, i, result[i], expected);
            exit(EXIT_FAILURE);
        }

        ++p;
        if (*p == '\0') {
            p = ++base;
        }
    }

    free(result);
    free(substrs);
    free(sample_copy);
}


static void clone_test(const char *sample, size_t n)
{
    size_t sample_len = strlen(sample);
    char *sample_copy = MEM(mystrdup(sample));
    char **items = MEM(malloc(n * sizeof(items[0])));

    for (size_t i = 0; i < n; ++i) items[i] = sample_copy;

    char *result = concat(items, (int) n);
    size_t expected_len = strlen(sample) * n;
    size_t real_len = strlen(result);

    if (expected_len != real_len) {
        printf("%s(): expected_len (%zu) != real_len (%zu)\n",
               __func__, expected_len, real_len);
        exit(EXIT_FAILURE);
    }

    for (size_t i = 0; i < expected_len; ++i) {
        char expected = sample[i % sample_len];
        if (result[i] != expected) {
            printf("%s(\"%s\", %zu): result[%zu] ('%c') != expected char '%c'\n",
                   __func__, sample, n, i, result[i], expected);
            exit(EXIT_FAILURE);
        }
    }

    free(result);
    free(items);
    free(sample_copy);
}


int main()
{
    triangle_test();
    clone_test("hello", 0);
    clone_test("hello", 1);
    clone_test("hello", 100);
    clone_test("", 10);
    clone_test("", 0);
    clone_test("hello", 100500);
    clone_test(sample, 100500);

    return 0;
}
