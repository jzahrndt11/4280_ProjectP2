/*
 *  CS4280 - Project P1
 *      - by. Jeremy Zahrndt
 *      - testScanner.h
 */
#ifndef PARSER_H
#define PARSER_H

#include "token.h"

extern char nextChar;
extern FILE* filePointer;

void parser();
int getTableColumn(int);

#endif
