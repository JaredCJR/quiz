#include "BinaryTree.h"
#include <stddef.h>

void flatten(struct TreeNode* root)
{
    struct TreeNode* leftt;
    while(root!=NULL) {
        if(root->left!=NULL) {
            leftt=root->left;
            while(leftt->right!=NULL) leftt=leftt->right;
            leftt->right=root->right;
            root->right=root->left;
            root->left=NULL;
        }
        root=root->right;
    }
}