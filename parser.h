/*
 *  CS4280 - Project P2
 *      - by. Jeremy Zahrndt
 *      - parser.h
 */
#ifndef PARSER_H
#define PARSER_H

#include "token.h"

extern char nextChar;
extern FILE* filePointer;
extern FILE* filteredFilePointer;
extern int line;

void parser();
void filter();
void S();
void A();
void B();
void C();
void D();
void E();
void F();
void G();
void H();
void J();
void X();
void Y();

#endif
