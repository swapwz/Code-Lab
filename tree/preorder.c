#include <stdio.h>
#include <stdlib.h>

/* Definition for a binary tree node. */
struct TreeNode {
    int val;
    struct TreeNode *left;
    struct TreeNode *right;
};

/**
 * Return an array of size *returnSize.
 * Note: The returned array must be malloced, assume caller calls free().
 */
void getTreeSize(struct TreeNode *node, int *size) {
    if (node != NULL) {
        *size += 1;
        getTreeSize(node->left, size);
        getTreeSize(node->right, size);
        
    }
}

int* preorder(struct TreeNode *root, int *returnArray) {
    if (root == NULL)
        return returnArray;
    
    *returnArray++ = root->val;
    returnArray = preorder(root->left, returnArray);
    returnArray = preorder(root->right, returnArray);
    
    return returnArray;
}

int* preorderTraversal(struct TreeNode* root, int* returnSize) {
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

int main(int argc, char **argv)
{
    struct TreeNode *root;
    int i;
    int returnSize; 
    int *returnArray;

    root = calloc(1, sizeof(struct TreeNode));
    root->val = 4;
    root->left = calloc(1, sizeof(struct TreeNode));
    root->left->val = 5;

    root->right = calloc(1, sizeof(struct TreeNode));
    root->right->val = 6;

    returnArray = preorderTraversal(root, &returnSize);
    for (i = 0; i < returnSize; i++)
    {
        printf("Val: %d\r\n", returnArray[i]);
    }

    return 0;
}
