#include <stdio.h>
#include <stdlib.h>

unsigned long binsearch(unsigned long nel, int (*compare)(unsigned long i)) {
    unsigned long head = nel - 1;
    unsigned long index;
    unsigned long tail = 0;

    if (nel == 1){
        if (compare(0) == 0)
            return 0;
        else
            return nel;
    }


    do {
        index = (tail + head) / 2;
        switch (compare(index)) {
            case 1:
                head = index - 1;
                break;
            case -1:
                tail = index + 1;
                break;
            case 0:
                return index;


        }
    } while (tail <= head);
    return nel;
}


static long threshold;
static unsigned long coef;
static unsigned long nel;


#define CHECK_OVERFLOW(x) \
    if ((x) >= nel) { \
        printf("\n%s:%d: %s(%lu): argument must be in range 0..%lu\n", \
                __FILE__, __LINE__, __func__, (x), nel - 1); \
        exit(EXIT_FAILURE); \
    }


static int linear(unsigned long x) {
    CHECK_OVERFLOW(x);
    if (coef * x < threshold) return -1;
    if (coef * x > threshold) return +1;
    return 0;
}


static int parabola_up(unsigned long x) {
    CHECK_OVERFLOW(x);
    unsigned long y = x * x;
    if (y < threshold) return -1;
    if (y > threshold) return +1;
    return 0;
}


static int parabola_down(unsigned long x) {
    CHECK_OVERFLOW(x);
    x = nel - x;
    unsigned long y = -x * x;
    if (y < threshold) return -1;
    if (y > threshold) return +1;
    return 0;
}


#define NELEM(arr) (sizeof(arr) / sizeof(arr[0]))


struct Test {
    unsigned long nelem;
    long threshold;
    unsigned long expected;
};

static struct Test linear_tests1[] = {
        {1,       0,       0},
        {1,       1,       1},
        {1,       7,       1},
        {2,       0,       0},
        {2,       1,       1},
        {2,       7,       2},
        {1000000, 100500,  100500},
        {1000000, 0,       0},
        {1000000, 999999,  999999},
        {1000000, 1000000, 1000000},
        {1000000, 2000000, 1000000},
        {1000000, -1,      1000000},
        {1000000, -999999, 1000000},
};


static struct Test linear_tests2[] = {
        {1,       0,        0},
        {1,       1,        1},
        {1,       7,        1},
        {2,       0,        0},
        {2,       1,        2},
        {2,       2,        1},
        {2,       5,        2},
        {1000000, 100500,   50250},
        {1000000, 100501,   1000000},
        {1000000, 0,        0},
        {1000000, 1000000,  500000},
        {1000000, 1999998,  999999},
        {1000000, 20000000, 1000000},
        {1000000, 30000000, 1000000},
        {1000000, -1,       1000000},
        {1000000, -999999,  1000000},
};


static struct Test parabola_up_tests[] = {
        {1000000, 0L,             0},
        {1000000, 1L,             1},
        {1000000, 4L,             2},
        {1000000, 9L,             3},
        {1000000, 16L,            4},
        {1000000, 100L,           10},
        {1000000, 99L,            1000000},
        {1000000, 101L,           1000000},
        {1000000, 10100250000L,   100500},
        {1000001, 1000000000000L, 1000000},
        {1000000, 5000000000000L, 1000000},
        {1000000, -1L,            1000000},
};


static struct Test parabola_down_tests[] = {
        {1000000, -1L,             999999},
        {1000000, -4L,             999998},
        {1000000, -9L,             999997},
        {1000000, -16L,            999996},
        {1000000, -10100250000L,   899500},
        {1000000, -809098451001L,  100501},
        {1000000, -1000000000000L, 0},
        {1000000, -77777L,         1000000},
};


int main() {
    int failed = 0;
    unsigned long expected;

#define READ(array) \
    nel = (array)[i].nelem; \
    threshold = (array)[i].threshold; \
    expected = (array)[i].expected;

#define CHECK(func) \
    unsigned long res = binsearch(nel, func); \
    if (res == expected) printf("ok / %s\n", res == nel ? "none" : "found"); \
    else { \
        printf("fail\n\t\texpected result is %lu, your result is %lu\n", \
                expected, res); \
        ++failed; \
    }

    printf("Test a[i] = i:\n");
    coef = 1;
    for (size_t i = 0; i < NELEM(linear_tests1); ++i) {
        READ(linear_tests1);

        printf("\tN = %lu, k = %lu, finding %ld... ", nel, coef, threshold);
        CHECK(linear);
    }

    printf("\nTest a[i] = 2×i:\n");
    coef = 2;
    for (size_t i = 0; i < NELEM(linear_tests2); ++i) {
        READ(linear_tests2);

        printf("\tN = %lu, k = %lu, finding %ld... ", nel, coef, threshold);
        CHECK(linear);
    }

    printf("\nTest a[i] = i²:\n");
    for (size_t i = 0; i < NELEM(parabola_up_tests); ++i) {
        READ(parabola_up_tests);

        printf("\tN = %lu, finding %ld... ", nel, threshold);
        CHECK(parabola_up);
    }

    printf("\nTest a[i] = -(N - i)²\n");
    for (size_t i = 0; i < NELEM(parabola_down_tests); ++i) {
        READ(parabola_down_tests);

        printf("\tN = %lu, finding %ld... ", nel, threshold);
        CHECK(parabola_down);
    }

    return failed == 0 ? EXIT_SUCCESS : EXIT_FAILURE;
}

/* vim: set sw=0 ts=4 noet: */