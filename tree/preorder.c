#include <stdlib.h>
#include "tree.h"

/**
 * Return an array of size *returnSize.
 * Note: The returned array must be malloced, assume caller calls free().
 */
void getTreeSize(TREE_NODE_S *node, int *size) {
    if (node != NULL) {
        *size += 1;
        getTreeSize(node->left, size);
        getTreeSize(node->right, size);
        
    }
}

int* preorder(TREE_NODE_S *root, int *returnArray) {
    if (root == NULL)
        return returnArray;
    
    *returnArray++ = root->val;
    returnArray = preorder(root->left, returnArray);
    returnArray = preorder(root->right, returnArray);
    
    return returnArray;
}

int* preorderTraversal(TREE_NODE_S* root, int* returnSize) {
    int i;
    int size = 0;
    int *returnArray;

    if (root != NULL) {
        getTreeSize(root, &size);
        
        *returnSize = size;
        returnArray = (int *)malloc(size * sizeof(int));
        (void) preorder(root, returnArray);
    } else {
        *returnSize = 0;
        returnArray = NULL;
    }
    
    return returnArray;
}

