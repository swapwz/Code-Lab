#ifndef __TREE_H__
#define __TREE_H__

typedef struct TreeNode {
    int val;
    struct TreeNode *left;
    struct TreeNode *right;
} TREE_NODE_S; 

extern int* preorderTraversal(TREE_NODE_S *root, int *returnSize);

#endif
