#include <stdio.h>
#include <stdlib.h>
#include "tree.h"

int main(int argc, char **argv)
{
    TREE_NODE_S *root;
    int i;
    int returnSize; 
    int *returnArray;

    root = calloc(1, sizeof(TREE_NODE_S));
    root->val = 4;
    root->left = calloc(1, sizeof(TREE_NODE_S));
    root->left->val = 5;

    root->right = calloc(1, sizeof(TREE_NODE_S));
    root->right->val = 6;

    returnArray = preorderTraversal(root, &returnSize);
    for (i = 0; i < returnSize; i++)
    {
        printf("Val: %d\r\n", returnArray[i]);
    }

    return 0;
}
