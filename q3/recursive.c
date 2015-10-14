#include "BinaryTree.h"
#include <stddef.h>

struct TreeNode *_flatten(struct TreeNode * node)
{
    if (node == NULL) {
        return NULL;
    }
    if (node->right) {
        node->right = _flatten(node->right);
    }
    if (node->left) {
        struct TreeNode *tmp = node->right;
        node->right = _flatten(node->left);
        struct TreeNode *t = node->right;
        while (t->right) {
            t = t->right;
        }
        t->right = tmp;
        node->left = NULL;
    }
    return node;
}
void flatten(struct TreeNode* node)
{
    _flatten(node);
}