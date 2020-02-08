#ifndef _SRC_MALLOC_H_
#define _SRC_MALLOC_H_

enum colors {
    RED,
    BLACK
};

struct node {
    struct node *left;
    struct node *right;
    struct node *parent;
    enum colors color;
    void *block;
};

#endif
