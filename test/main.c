#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "malloc.h"
#include "zone.h"

int main(void)
{
    void *p[16] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};

    p[1] = ft_malloc(123);
    for (int i = 0; i < 100000000; ++i)
    {
        *p = ft_malloc(23);
        ft_free(*p);
    }
    ft_free(p[1]);
    printf("End\n");
    return 0;
}

//    void *p[16] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};

//    p[0] = ft_malloc(8);
//    printf("Data: %p\n", p[0]);
//    p[1] = ft_malloc(8);
//    printf("Data: %p\n", p[1]);
//    p[2] = ft_malloc(8);
//    printf("Data: %p\n", p[2]);
//    p[3] = ft_malloc(8);
//    printf("Data: %p\n", p[3]);
//    p[4] = ft_malloc(8);
//    printf("Data: %p\n", p[4]);
//    ft_free(p[2]);
//    ft_free(p[1]);
//    ft_free(p[3]);
//    p[0] = ft_malloc(40);
//    printf("Data: %p\n", p[0]);
