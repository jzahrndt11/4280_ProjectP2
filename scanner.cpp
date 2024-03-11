/*
 *  CS4280 - Project P2
 *      - by. Jeremy Zahrndt
 *      - scanner.cpp
 */
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

#include "scanner.h"
#include "parser.h"

int line = 1;
const int TABLE_SIZE = 12;

int tableArr[TABLE_SIZE][TABLE_SIZE] = {
        { 1, -1, 3, 5, 6, -2, 8, -3, 10, -4, 0, 1001 },
        { -5, 2, -5, -5, -5, -5, -5, -5, -5, -5, -5, -5 },
        { 1002, 2, 1002, 1002, 1002, 1002, 1002, 1002, 1002, 1002, 1002, 1002 },
        { -5, 4, -5, -5, -5, -5, -5, -5, -5, -5, -5, -5 },
        { 1003, 4, 1003, 1003, 1003, 1003, 1003, 1003, 1003, 1003, 1003, 1003 },
        { 1004, 1004, 1004, 1004, 1004, 1004, 1004, 1004, 1004, 1004, 1004, 1004 },
        { 1004, 1004, 1004, 1004, 1004, 7, 1004, 1004, 1004, 1004, 1004, 1004 },
        { 1004, 1004, 1004, 1004, 1004, 1004, 1004, 1004, 1004, 1004, 1004, 1004 },
        { 1004, 1004, 1004, 1004, 1004, 1004, 1004, 9, 1004, 1004, 1004, 1004 },
        { 1004, 1004, 1004, 1004, 1004, 1004, 1004, 1004, 1004, 1004, 1004, 1004 },
        { 1004, 1004, 1004, 1004, 1004, 1004, 1004, 1004, 1004, 11, 1004, 1004 },
        { 1004, 1004, 1004, 1004, 1004, 1004, 1004, 1004, 1004, 1004, 1004, 1004 }
};

// Scanner function return Token struct
Token scanner() {
    Token token;
    int state = 0;
    int nextState;
    int tokenIndex = 0;

    memset(token.tokenInstance, '\0', MAX_TOKEN_SIZE);
    token.tokenId = Unknown;


    while (true) {
        // Increment line if new line is found and skip new line
        if (nextChar == 10) {
            line++;
            nextChar = fgetc(filePointer);
        }

        // set line number
        token.lineNum = line;

        // get colNum for table
        int colNum = getTableColumn();

        // get next state
        if (state < 12 && colNum < 12) {
            nextState = tableArr[state][colNum];
        } else {
            printf("Error (scanner) tableArr index greater can't be greater than 11");
        }

        // Error states
        if (nextState < 0) {
            switch (nextState) {
                case -1:
                    printf("Error (scanner): No Tokens starts with a { digit } - Line { %d }\n", line);
                    exit(EXIT_FAILURE);
                case -2:
                    printf("Error (scanner): No Tokens starts with a { \" } - Line { %d }\n", line);
                    exit(EXIT_FAILURE);
                case -3:
                    printf("Error (scanner): No Tokens starts with a { $ } - Line { %d }\n", line);
                    exit(EXIT_FAILURE);
                case -4:
                    printf("Error (scanner): No Tokens starts with a { ; } - Line { %d }\n", line);
                    exit(EXIT_FAILURE);
                case -5:
                    printf("Error (scanner): Token { %s } must be followed by a { digit } - Line { %d }\n", token.tokenInstance, line);
                    exit(EXIT_FAILURE);
                default:
                    printf("Error (scanner): Unknown Error");
                    exit(EXIT_FAILURE);
            }
        }

        // End of Token states
        if (nextState > 1000) {
            switch (nextState) {
                case 1001:
                    token.tokenId = EOF_Token;
                    return token;
                case 1002:
                    token.tokenId = T1_Token;
                    return token;
                case 1003:
                    token.tokenId = T2_Token;
                    return token;
                case 1004:
                    token.tokenId = T3_Token;
                    return token;
                default:
                    printf("Error! (scanner): Unknown Error");
                    token.tokenId = Unknown;
                    return token;
            }
        } else {
            // If not an error or end of state append char to instance and get next char
            state = nextState;
            token.tokenInstance[tokenIndex++] = nextChar;
            nextChar = fgetc(filePointer);
        }
    }
}

// function to get column number for FSA Table
int getTableColumn() {
    if (isalpha(nextChar)) {
        return 0;
    } else if (isdigit(nextChar)){
        return 1;
    } else {
        switch (nextChar) {
            case '%':
                return 2;
            case '.':
                return 3;
            case '!':
                return 3;
            case '*':
                return 4;
            case '\"':
                return 5;
            case '?':
                return 6;
            case '$':
                return 7;
            case ',':
                return 8;
            case ';':
                return 9;
            case ' ':
                return 10;
            case '\n':
                return 10;
            case '\t':
                return 10;
            case EOF:
                return 11;
            default:
                printf("Error Unknown Character { %c } Line { %d }\n", nextChar, line);
                exit(EXIT_FAILURE);
        }
    }
}