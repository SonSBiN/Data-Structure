#include <stdio.h>
#include <stdlib.h>
#include "BSTree.h"

static Element BSTreFindMinValue(PTreeNode root);

PTreeNode BSTreInsert(PTreeNode root, Element e, CompareElement compare)
{
    // 规过 1
    //if (root == NULL) {
    //    return TreCreateNode(e);
    //}
    //else if (compare(&e, &(root->data)) < 0) {
    //    root->left = BSTreInsert(root->left, e, compare);
    //}
    //else if (compare(&e, &(root->data)) > 0) {
    //    root->right = BSTreInsert(root->right, e, compare);
    //}
    //return root;

    // 规过 2
    if (root) {
        int n = compare(&e, &(root->data));
        if (n < 0) {
            root->left = BSTreInsert(root->left, e, compare);
        }
        else if (n > 0) {
            root->right = BSTreInsert(root->right, e, compare);
        }
        return root;
    }
    return TreCreateNode(e);
}

PTreeNode BSTreDelete(PTreeNode root, Element e, CompareElement compare)
{
    if (root == NULL) {
        return root;
    }
    // 版快 1
    int n = compare(&e, &(root->data));
    if (n < 0) {
        root->left = BSTreDelete(root->left, e, compare);
    }
    else if (n > 0) {
        root->right = BSTreDelete(root->right, e, compare);
    }
    else {
        // 版快 1
        if (root->left == NULL && root->right == NULL) {
            free(root);
            return NULL;
        }
        else if (root->left == NULL) { // 版快 2
            PTreeNode temp = root;
            root = root->right;
            free(temp);
        }
        else if (root->right == NULL) { // 版快 2
            PTreeNode temp = root;
            root = root->left;
            free(temp);
        }
        else { // 版快 3
            int data = BSTreFindMinValue(root->right);
            root->data = data;
            root->right = BSTreDelete(root->right, data, compare);
        }
    }
    return root;
}

PTreeNode BSTreSearch(PTreeNode root, Element e, CompareElement compare)
{
    if (root) {
        int n = compare(&e, &(root->data));
        if (n == 0) {
            return root;
        }
        else if (n < 0) {
            return BSTreSearch(root->left, e, compare);
        }
        else if (n > 0) {
            return BSTreSearch(root->right, e, compare);
        }
    }
    return NULL;
}

static Element BSTreFindMinValue(PTreeNode root)
{
    if (root->left == NULL) {
        return root->data;
    }
    return BSTreFindMinValue(root->left);
}


