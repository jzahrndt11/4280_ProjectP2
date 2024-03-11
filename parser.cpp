/*
 *  CS4280 - Project P1
 *      - by. Jeremy Zahrndt
 *      - testScanner.cpp
 */

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include "string.h"

#include "parser.h"
#include "scanner.h"

const char* tokenNames[] = {
        "EOF Token",
        "T1 Token",
        "T2 Token",
        "T3 Token",
        "Unknown"
};

// Initialization of Global Variables
char nextChar = 0;

// Test Scanner Function
void parser() {
    Token tokenInfo;
    int line = 1;
    bool comment = false;
    memset(tokenInfo.tokenInstance, '\0', MAX_TOKEN_SIZE);

    // get first char
    nextChar = fgetc(filePointer);

    do {
        // Skip Comments
        while (comment) {
            nextChar = fgetc(filePointer);

            // Increment line if new line is found
            if (nextChar == 10) {
                line++;
            }

            // end of comment
            if (nextChar == 35) {
                comment = false;
                nextChar = fgetc(filePointer);
            }
        }

        // Check for start of comment
        if (nextChar == 35) {
            comment = true;
            continue;
        }

        // Skip Spaces
        while (isspace(nextChar)) {
            // Increment line if new line is found
            if (nextChar == 10) {
                line++;
            }

            nextChar = fgetc(filePointer);
        }

        // start scanner function
        tokenInfo = scanner(line);

        // Print token info
        printf("%s\t%s\t%d\n", tokenNames[tokenInfo.tokenId], tokenInfo.tokenInstance, tokenInfo.lineNum);

    } while (tokenInfo.tokenId != EOF_Token);
}