/*
 *  CS4280 - Project P2
 *      - by. Jeremy Zahrndt
 *      - parser.h
 */
#ifndef PARSER_H
#define PARSER_H

#include "token.h"
#include "node.h"

extern char nextChar;
extern FILE* filePointer;

node_t* parser();
void filter();
node_t* S();
node_t* A();
node_t* B();
node_t* C();
node_t* D();
node_t* E();
node_t* F();
node_t* G();
node_t* H();
node_t* J();
node_t* X();
node_t* Y();

#endif
