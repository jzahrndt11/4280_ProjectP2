/*
 *  CS4280 - Project P2
 *      - by. Jeremy Zahrndt
 *      - testTree.cpp
 */
#include <stdio.h>
#include <stdlib.h>

#include "testTree.h"

// Test Tree function -----------------------------------------------------------------------------------------------------------------
void testTree(node_t* tree) {
    printf("TestTree.cpp: { Hello }\n");
    traversePreOrder(tree, 0);
}

// Traverse Pre-order function -----------------------------------------------------------------------------------------------------------------
void traversePreOrder(node_t* root, int level) {
    // Base case
    if (root == NULL) {
        return;
    }

    // print current node detail
    printf("%*c%c\n", level*4, ' ', root->label);

    // traverse left-most subtree (if needed)
    if (root->childOne != NULL) {
        traversePreOrder(root->childOne, level + 1);
    }

    // traverse middle subtree (if needed)
    if (root->childTwo != NULL) {
        traversePreOrder(root->childTwo, level + 1);
    }

    // traverse right-most subtree (if needed)
    if (root->childThree != NULL) {
        traversePreOrder(root->childThree, level + 1);
    }
}