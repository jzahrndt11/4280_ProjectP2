/*
 *  CS4280 - Project P2
 *      - by. Jeremy Zahrndt
 *      - buildTree.cpp
 *
 *  Resources:
 *      - https://www.w3resource.com/c-programming-exercises/tree/c-tree-exercises-1.php
 *      - https://www.geeksforgeeks.org/ftell-c-example/
 *      - https://www.geeksforgeeks.org/fread-function-in-c/
 *      - https://www.geeksforgeeks.org/strtok-strtok_r-functions-c-examples/
 */

#include <stdio.h>
#include <stdlib.h>

#include "buildTree.h"

// Create a New Node of the Binary Tree --------------------------------------------------------------------------------
node_t* create(char label) {
    node_t* newNode = (node_t*)malloc(sizeof(node_t));

    // check if memory allocation was successful
    if (newNode != NULL) {
        // Initialize node data
        newNode->label = label;
        newNode->childOne = NULL;
        newNode->childTwo = NULL;
        newNode->childThree = NULL;
        newNode->tokenInstanceOne = NULL;
        newNode->tokenIdOne = 4; // Unknown
        newNode->tokenInstanceTwo = NULL;
        newNode->tokenIdTwo = 4; // Unknown
        newNode->tokenInstanceThree = NULL;
        newNode->tokenIdThree = 4; // Unknown
    }
    printf("Made it Here\n");
    return newNode;
}
