/*
 *  CS4280 - Project P2
 *      - by. Jeremy Zahrndt
 *      - testTree.cpp
 */
#include <stdio.h>
#include <stdlib.h>

#include "testTree.h"

const char* tokenNames[] = {
        "EOF Token",
        "T1 Token",
        "T2 Token",
        "T3 Token",
        "Unknown"
};

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

    if (root->tokenInstanceOne != NULL) {
        if (root->tokenIdOne != 4) {
            printf("%*c%s%s\n", level+1*4, ' ', tokenNames[root->tokenIdOne], root->tokenInstanceOne);
        }
        else {
            printf("%*c%s\n", level+1*4, ' ', root->tokenInstanceOne);
        }
    }

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