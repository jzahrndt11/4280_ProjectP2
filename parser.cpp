/*
 *  CS4280 - Project P2
 *      - by. Jeremy Zahrndt
 *      - parser.cpp
 */

#include <stdio.h>
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
Token tokenInfo;


// Test Scanner Function
void parser() {
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

// S -> CD          ( First set: t2 )
void S() {
    if (tokenInfo.tokenId == T2_Token) {
        // process t2
        tokenInfo = scanner(tokenInfo.lineNum);
        D();
        return;
    } else {
        printf("parser.cpp: Error in S()\n");
    }
}

// A -> FX          ( First set: t1 t2 )
void A() {
    if (tokenInfo.tokenId == (T1_Token | T2_Token)) {
        // process t1 or t2 token
        tokenInfo = scanner(tokenInfo.lineNum);
        X();
        return;
    }
    else {
        printf("parser.cpp: Error in A()\n");
    }
}

// B -> .t2A!       ( First set: . )
void B() {
    if (tokenInfo.tokenId == T3_Token && tokenInfo.tokenInstance[0] == '.') {
        // process .
        tokenInfo = scanner(tokenInfo.lineNum);
        if (tokenInfo.tokenId == T2_Token) {
            // process t2
            tokenInfo = scanner(tokenInfo.lineNum);
            A();
            if (tokenInfo.tokenId == T3_Token && tokenInfo.tokenInstance[0] == '!') {
                // process !
                tokenInfo = scanner(tokenInfo.lineNum);
                return;
            }

        }
    }
    else {
        printf("parser.cpp: Error in B()\n");
    }
}

// C -> t2*         ( First set: t2 )
void C() {
    if (tokenInfo.tokenId == T2_Token) {
        // process t2
        tokenInfo = scanner(tokenInfo.lineNum);
        if (tokenInfo.tokenId == T3_Token && tokenInfo.tokenInstance[0] == '*') {
            // process *
            tokenInfo = scanner(tokenInfo.lineNum);
            return;
        }
    } else {
        printf("parser.cpp: Error in C()\n");
    }
}

// D -> Y           ( First set: , ,; . t2 *" ? empty )
void D() {

}

// E -> ,AAH | ,;FH             ( First set: , | ,; )
void E() {

}

// F -> t1 | t2         ( First set: t1 | t2 )
void F() {

}

// G -> B | C | J           ( First set: . | t2 | *" )
void G() {

}

// H -> E? | G. | empty         ( First set: , ,; | . t2 *" | empty )
void H(){

}

// J -> *"A.        ( First set: *" )
void J() {

}

// X -> F?$ | .         ( First set: t1 t2 | . )
void X() {

}

// Y -> H?Y | empty         ( First set: , ,; . t2 *" ? empty | empty )
void Y() {

}