#include "malloc.h"

#include <stddef.h>

static struct block *_delete1(struct block **root, struct block *node);
static struct block *_delete2(struct block **root, struct block *node);

struct block *insert(struct block **root, struct block *node)
{
    struct block *parent;

    parent = NULL;
    while (*root)
    {
        parent = *root;
        if (node->max_block < (*root)->max_block)
            root = &(*root)->left;
        else
            root = &(*root)->right;
    }
    *root = node;
    node->parent = parent;
    node->left = NULL;
    node->right = NULL;
    return node;
}


struct block *search(struct block *root, uint16_t key)
{
    struct block *ret;

    if (root->max_block == key)
        return root;
    if (root->max_block > key)
    {
        if (!root->left)
            return root;
        ret = search(root->left, key);
        if (ret)
            return ret;
        else
            return root;
    }
    if (root->right)
        return search(root->right, key);
    else
        return NULL;
}

struct block *delete(struct block **root, struct block *node)
{
    if (!node->left || !node->right)
        return _delete1(root, node); // case 1 and 2
    else
        return _delete2(root, node);
}

static struct block *_delete1(struct block **root, struct block *node)
{
    struct block *exist_node;

    exist_node = node->left ? node->left : node->right;
    if (exist_node)
        exist_node->parent = node->parent;
    if (node->parent && node->parent->left == node)
        node->parent->left = exist_node;
    else if (node->parent)
        node->parent->right = exist_node;
    if (*root == node)
        *root = exist_node;
    return node;
}

static struct block *_delete2(struct block **root, struct block *node)
{
    struct block *replace_node;

    replace_node = node->left;
    while (replace_node->right)
        replace_node = replace_node->right;
    replace_node = _delete1(root, replace_node);

    if (node->parent && node->parent->left == node)
        node->parent->left = replace_node;
    else if (node->parent)
        node->parent->right = replace_node;

    replace_node->left = node->left;
    if (node->left)
        node->left->parent = replace_node;
    replace_node->right = node->right;
    if (node->right)
        node->right->parent = replace_node;
    replace_node->parent = node->parent;
    if (*root == node)
        *root = replace_node;
    return node;
}

void print_tree(struct block *root)
{
    if (root->left)
        print_tree(root->left);
    printf("addr: %p\n", root);
    printf("    key: %u\n", root->max_block);
    printf("    left  : %p\n", root->left);
    printf("    right : %p\n", root->right);
    printf("    parent: %p\n", root->parent);
    if (root->right)
        print_tree(root->right);
}
