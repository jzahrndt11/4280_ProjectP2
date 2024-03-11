/*
 *  CS4280 - Project P1
 *          - by. Jeremy Zahrndt
 *          - token.h
 *      Resources:
 *          - https://www.geeksforgeeks.org/enumeration-enum-c/
 */
#ifndef TOKEN_H
#define TOKEN_H

const int MAX_TOKEN_SIZE = 100;

// Enumeration - mainly used to assign names to integral constants
typedef enum {
    EOF_Token,
    T1_Token,
    T2_Token,
    T3_Token,
    Unknown
} TokenId;

typedef struct {
    TokenId tokenId;
    char tokenInstance[MAX_TOKEN_SIZE];
    int lineNum;
} Token;

#endif
