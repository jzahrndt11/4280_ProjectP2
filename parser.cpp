/*
 *  CS4280 - Project P2
 *      - by. Jeremy Zahrndt
 *      - parser.cpp
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
Token tokenInfo;
const char* filteredFile = "filter.txt";

// Test Scanner Function
void parser() {
    memset(tokenInfo.tokenInstance, '\0', MAX_TOKEN_SIZE);

    // filter out comments
    filter();

    // open filter.txt after comments have been removed
    filePointer = fopen(filteredFile, "r");
    if (filePointer == nullptr) {
        perror("Fatal: Error Opening File!\n");
        exit(EXIT_FAILURE);
    }

    // get first char
    nextChar = fgetc(filePointer);

    // run scanner
    tokenInfo = scanner();

    // start production S
    S();

    // Check for EOFtk
    if (tokenInfo.tokenId == EOF_Token) {
        printf("Parsing Passed\n");
    }
    else {
        printf("parser.cpp: Error in parser()\n");
        exit(EXIT_FAILURE);
    }

    // Print token info
    printf("%s\t%s\t%d\n", tokenNames[tokenInfo.tokenId], tokenInfo.tokenInstance, tokenInfo.lineNum);

}

// function to remove comments
void filter() {
    bool comment = false;
    FILE* filteredFilePointer;

    filteredFilePointer = fopen(filteredFile, "w");

    if (filteredFilePointer == nullptr) {
        perror("Error opening file { filteredFile }");
        exit(EXIT_FAILURE);
    }

    int c;
    while ((c = fgetc(filePointer)) != EOF) {
        // Skip Comments
        while (comment) {
            c = fgetc(filePointer);

            // keep new line
            if (c == 10) {
                fputc(c, filteredFilePointer);
            }

            // end of comment
            if (c == 35) {
                comment = false;
                c = fgetc(filePointer);
            }
        }

        // Check for start of comment
        if (c == 35) {
            comment = true;
            continue;
        }

        while (isspace(c)) {
            // keep new line
            if (c == 10) {
                fputc(c,filteredFilePointer);
                c = fgetc(filePointer);
            } else {
                c = fgetc(filePointer);
            }
        }

        // if not a comment or a whitespace add to new file
        fputc(c, filteredFilePointer);
    }
    fclose(filePointer);
    fclose(filteredFilePointer);
}

// S -> CD          ( First set: t2 )
void S() {
    if (tokenInfo.tokenId == T2_Token) {
        C();
        D();
        return;
    }
    else {
        printf("ERROR{parser.cpp-S()} Language must start with T2 Token { You gave %s } - Line %d\n", tokenNames[tokenInfo.tokenId], tokenInfo.lineNum);
        exit(EXIT_FAILURE);
    }

}

// A -> FX          ( First set: t1 t2 )
void A() {
    if (tokenInfo.tokenId == (T1_Token | T2_Token)) {
        F();
        X();
        return;
    }
    else {
        printf("ERROR{parser.cpp-A()} T1 or T2 required { You gave %s } - Line %d\n", tokenNames[tokenInfo.tokenId], tokenInfo.lineNum);
        exit(EXIT_FAILURE);
    }
}

// B -> .t2A!       ( First set: . )
void B() {
    if (tokenInfo.tokenId == T3_Token && tokenInfo.tokenInstance[0] == '.') {
        // process .
        tokenInfo = scanner();
        if (tokenInfo.tokenId == T2_Token) {
            // process t2
            tokenInfo = scanner();
            A();
            if (tokenInfo.tokenId == T3_Token && tokenInfo.tokenInstance[0] == '!') {
                // process !
                tokenInfo = scanner();
                return;
            }

        }
    }
    else {
        printf("ERROR:{parser.cpp-B()}  . required { You gave %s } - Line %d\n", tokenInfo.tokenInstance, tokenInfo.lineNum);
        exit(EXIT_FAILURE);
    }
}

// C -> t2*         ( First set: t2 )
void C() {
    if (tokenInfo.tokenId == T2_Token) {
        // process t2
        tokenInfo = scanner();
        if (tokenInfo.tokenId == T3_Token && tokenInfo.tokenInstance[0] == '*') {
            // process *
            tokenInfo = scanner();
            return;
        }
        else {
            printf("ERROR:{parser.cpp-C()}  . required { You gave %s } - Line %d\n", tokenInfo.tokenInstance, tokenInfo.lineNum);
            exit(EXIT_FAILURE);
        }
    } else {
        printf("parser.cpp: Error in C()\n");
        exit(EXIT_FAILURE);
    }
}

// D -> Y           ( First set: , ,; . t2 *" ? empty )
void D() {
    Y();
}

// E -> ,AAH | ,;FH             ( First set: , | ,; )
void E() {
    if (tokenInfo.tokenId == T3_Token && tokenInfo.tokenInstance[0] == ','){
        A();
        A();
        H();
    }
    else if (tokenInfo.tokenId == T3_Token && tokenInfo.tokenInstance[0] == ',' && tokenInfo.tokenInstance[1] == ';') {
        F();
        H();
    }
    else {
        printf("parser.cpp: Error in E()\n");
        exit(EXIT_FAILURE);
    }
}

// F -> t1 | t2         ( First set: t1 | t2 )
void F() {
    if (tokenInfo.tokenId == T1_Token) {
        // process t1
        tokenInfo = scanner();
        return;
    }
    else if (tokenInfo.tokenId == T2_Token) {
        //process t2
        tokenInfo = scanner();
        return;
    }
    else {
        printf("parser.cpp: Error in F()\n");
        exit(EXIT_FAILURE);
    }
}

// G -> B | C | J           ( First set: . | t2 | *" )
void G() {
    if (tokenInfo.tokenId == T2_Token) {
        B();
    }
    else if (tokenInfo.tokenId == T3_Token && tokenInfo.tokenInstance[0] == '.') {
        C();
    }
    else if (tokenInfo.tokenId == T3_Token && tokenInfo.tokenInstance[0] == '*' && tokenInfo.tokenInstance[1] == '"') {
        J();
    }
    else {
        printf("parser.cpp: Error in G()\n");
        exit(EXIT_FAILURE);
    }
}

// H -> E? | G. | empty         ( First set: , ,; | . t2 *" | empty )
void H(){
    if (tokenInfo.tokenId == T3_Token && (tokenInfo.tokenInstance[0] == ',' || (tokenInfo.tokenInstance[0] == ',' && tokenInfo.tokenInstance[1] == ';'))) {
        E();
        if (tokenInfo.tokenId == T3_Token && tokenInfo.tokenInstance[0] == '?') {
            // process ?
            tokenInfo = scanner();
            return;
        }
        else {
            printf("parser.cpp: Error in H()\n");
            exit(EXIT_FAILURE);
        }
    }
    else if (tokenInfo.tokenId == T2_Token || (tokenInfo.tokenId == T3_Token && (tokenInfo.tokenInstance[0] == '.' || (tokenInfo.tokenInstance[0] == '*' && tokenInfo.tokenInstance[1] == '"')))) {
        G();
        if (tokenInfo.tokenId == T3_Token && tokenInfo.tokenInstance[0] == '.') {
            // process .
            tokenInfo = scanner();
            return;
        } else {
            printf("parser.cpp: Error in H()\n");
            exit(EXIT_FAILURE);
        }
    }
    else {
        return;
    }
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