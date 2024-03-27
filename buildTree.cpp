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
#include "string.h"

#include "buildTree.h"

// Create a New Node of the Binary Tree --------------------------------------------------------------------------------
node_t* create(char label) {
    printf("Made it Here\n");
    node_t* newNode = (node_t*)malloc(sizeof(node_t));
    printf("Made it Here\n");
    // check if memory allocation was successful
    if (newNode != NULL) {
        // Initialize node data
        newNode->label = label;
        newNode->childOne = NULL;
        newNode->childTwo = NULL;
        newNode->childThree = NULL;
        memset(newNode->tokenInstanceOne, '\0', MAX_TOKEN_SIZE);
        newNode->tokenIdOne = 4; // Unknown
        memset(newNode->tokenInstanceTwo, '\0', MAX_TOKEN_SIZE);
        newNode->tokenIdTwo = 4; // Unknown
        memset(newNode->tokenInstanceThree, '\0', MAX_TOKEN_SIZE);
        newNode->tokenIdOne = 4; // Unknown
        memset(newNode->tokenInstanceThree, '\0', MAX_TOKEN_SIZE);
        newNode->tokenIdTwo = 4; // Unknown
    }
    return newNode;
}
