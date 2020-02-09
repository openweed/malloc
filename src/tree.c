#include "malloc.h"

#include <stddef.h>

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

struct block *delete(struct block *node)
{
    struct block *exist_node;

    if (!node->left || !node->right) // case 1 and 2
    {
        exist_node = node->left ? node->left : node->right;
        if (exist_node)
            exist_node->parent = node->parent;
        if (node->parent && node->parent->left == node)
            node->parent->left = exist_node;
        else if (node->parent)
            node->parent->right = exist_node;
        return node;
    }

    exist_node = node->left;
    while (exist_node->right)
        exist_node = exist_node->right;
    exist_node = delete(exist_node);

    if (node->parent && node->parent->left == node)
        node->parent->left = exist_node;
    else if (node->parent)
        node->parent->right = exist_node;

    exist_node->left = node->left;
    if (node->left)
        node->left->parent = exist_node;
    exist_node->right = node->right;
    if (node->right)
        node->right->parent = exist_node;
    return node;
}
