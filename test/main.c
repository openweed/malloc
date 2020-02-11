#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "malloc.h"

int main(void)
{
    printf("Node size: %zu\n", sizeof(struct block));
    struct block arr[10];
    struct block *root = NULL;

    memset(arr, 0, sizeof (arr));
    for (int i = 0; i < 10; ++i)
        arr[i].max_block = i * 2;

    for (int i = 0; i < 10; ++i)
        insert(&root, &arr[i]);

    for (int i = 0; i < 10; i += 2) {
        delete(&root, &arr[i]);
    }

    for (int i = 0; i < 10; i += 2) {
        insert(&root, &arr[i]);
    }

    for (int i = 1; i < 10; i += 2) {
        delete(&root, &arr[i]);
    }
    for (int i = 1; i < 10; i += 2) {
        insert(&root, &arr[i]);
    }
    for (int i = 0; i < 10; ++i) {
        delete(&root, &arr[i]);
    }
    for (int i = 0; i < 10; i += 2) {
        insert(&root, &arr[i]);
    }
    printf("root: %p\n", root);
    print_tree(root);
    printf("blocks inserted\n");
    return 0;
}
