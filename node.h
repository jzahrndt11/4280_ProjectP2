/*
 *  CS4280 - Project P2
 *      - by. Jeremy Zahrndt
 *      - node.h
 */
#ifndef NODE_H
#define NODE_H

#include "token.h"

typedef struct node_t {
    struct node_t *childOne;
    struct node_t *childTwo;
    struct node_t *childThree;
    char label;
    char* tokenInstanceOne;
    int tokenIdOne;
    char* tokenInstanceTwo;
    int tokenIdTwo;
    char* tokenInstanceThree;
    int tokenIdThree;
} node_t;

#endif
