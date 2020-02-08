#include "malloc.h"

#include <stddef.h>

void insert_case1(struct node *n);
void insert_case2(struct node *n);
void insert_case3(struct node *n);
void insert_case4(struct node *n);
void insert_case5(struct node *n);

struct node *insert(struct node **root, struct node *n)
{

    return n;
}

struct node *grandparent(struct node *n)
{
    if ((n != NULL) && (n->parent != NULL))
        return n->parent->parent;
    else
        return NULL;
}

struct node *uncle(struct node *n)
{
    struct node *g = grandparent(n);
    if (g == NULL)
        return NULL; // No grandparent means no uncle
    if (n->parent == g->left)
        return g->right;
    else
        return g->left;
}

void rotate_left(struct node *n)
{
    struct node *pivot = n->right;

    pivot->parent = n->parent; /* при этом, возможно, pivot становится корнем дерева */
    if (n->parent != NULL) {
        if (n->parent->left==n)
            n->parent->left = pivot;
        else
            n->parent->right = pivot;
    }

    n->right = pivot->left;
    if (pivot->left != NULL)
        pivot->left->parent = n;

    n->parent = pivot;
    pivot->left = n;
}

void rotate_right(struct node *n)
{
    struct node *pivot = n->left;

    pivot->parent = n->parent; /* при этом, возможно, pivot становится корнем дерева */
    if (n->parent != NULL) {
        if (n->parent->left==n)
            n->parent->left = pivot;
        else
            n->parent->right = pivot;
    }

    n->left = pivot->right;
    if (pivot->right != NULL)
        pivot->right->parent = n;

    n->parent = pivot;
    pivot->right = n;
}

void insert_case1(struct node *n)
{
    if (n->parent == NULL)
        n->color = BLACK;
    else
        insert_case2(n);
}

void insert_case2(struct node *n)
{
    if (n->parent->color == BLACK)
        return; // Tree is still valid
    else
        insert_case3(n);
}

void insert_case3(struct node *n)
{
    struct node *u = uncle(n), *g;

    if ((u != NULL) && (u->color == RED)) {
    // && (n->parent->color == RED) Второе условие проверяется в insert_case2, то есть родитель уже является красным.
        n->parent->color = BLACK;
        u->color = BLACK;
        g = grandparent(n);
        g->color = RED;
        insert_case1(g);
    } else {
        insert_case4(n);
    }
}

void insert_case4(struct node *n)
{
    struct node *g = grandparent(n);

    if ((n == n->parent->right) && (n->parent == g->left)) {
        rotate_left(n->parent);
        n = n->left;
    } else if ((n == n->parent->left) && (n->parent == g->right)) {
        rotate_right(n->parent);
        n = n->right;
    }
    insert_case5(n);
}

void insert_case5(struct node *n)
{
    struct node *g = grandparent(n);

    n->parent->color = BLACK;
    g->color = RED;
    if ((n == n->parent->left) && (n->parent == g->left)) {
        rotate_right(g);
    } else { /* (n == n->parent->right) && (n->parent == g->right) */
        rotate_left(g);
    }
}