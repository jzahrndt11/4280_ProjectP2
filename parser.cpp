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

// Parser Function -------------------------------------------------------------------------------------------------------------------------------
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
}

// function to remove comments -----------------------------------------------------------------------------------------------------------------
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

// S -> CD          ( First set: t2 ) ---------------------------------------------------------------------------------------------------------------------------
void S() {
    printf("S()\n");

    C();    // run non-terminal C
    D();    // run non-terminal D

    printf("End of S()\n");
}

// A -> FX          ( First set: t1 t2 )
void A() {
    printf("A()\n");

    F();    // run non-terminal F
    X();    // run non-terminal X

    printf("End of A()\n");
}

// B -> .t2A!       ( First set: . ) ---------------------------------------------------------------------------------------------------------------------------
void B() {
    printf("B()\n");

    if (tokenInfo.tokenId == T3_Token && tokenInfo.tokenInstance[0] == '.') {
        printf("Process { . } in B()\n");   // process .
        tokenInfo = scanner();  //consume .

        if (tokenInfo.tokenId == T2_Token) {
            printf("Process t2 token { %s } in B()\n", tokenInfo.tokenInstance);  // process t2
            tokenInfo = scanner();  //consume t2

            A();    // run non-terminal A

            if (tokenInfo.tokenId == T3_Token && tokenInfo.tokenInstance[0] == '!') {
                printf("Process { ! } in B()\n");  // process !
                tokenInfo = scanner();  // consume !
                printf("End of B()\n");
                return;
            }
            else {
                printf("ERROR parser.cpp-B(): { ! } required. You gave { %s } - Line %d\n", tokenInfo.tokenInstance, tokenInfo.lineNum);
                exit(EXIT_FAILURE);
            }
        }
        else {
            printf("ERROR parser.cpp-B(): { t2 } required. You gave { %s } - Line %d\n", tokenNames[tokenInfo.tokenId], tokenInfo.lineNum);
            exit(EXIT_FAILURE);
        }
    }
    else {
        printf("ERROR parser.cpp-B(): { . } required. You gave { %s } - Line %d\n", tokenInfo.tokenInstance, tokenInfo.lineNum);
        exit(EXIT_FAILURE);
    }
}

// C -> t2*         ( First set: t2 ) ------------------------------------------------------------------------------------------------------------------
void C() {
    printf("C()\n");

    if (tokenInfo.tokenId == T2_Token) {
        printf("Process t2 token { %s } in C()\n", tokenInfo.tokenInstance);  // process t2
        tokenInfo = scanner();  // consume t2

        if (tokenInfo.tokenId == T3_Token && tokenInfo.tokenInstance[0] == '*') {
            printf("Process { * } in C()\n");  // process *
            tokenInfo = scanner();  // consume *

            printf("End of C()\n");
            return;
        }
        else {
            printf("ERROR parser.cpp-C(): { * } required. You gave { %s } - Line %d\n", tokenInfo.tokenInstance, tokenInfo.lineNum);
            exit(EXIT_FAILURE);
        }
    } else {
        printf("ERROR parser.cpp-C(): { t2 } required. You gave { %s } - Line %d\n", tokenNames[tokenInfo.tokenId], tokenInfo.lineNum);
        exit(EXIT_FAILURE);
    }
}

// D -> Y           ( First set: , ,; . t2 *" ? empty )
void D() {
    printf("D()\n");

    Y();    // run non-terminal Y
    printf("End of D()\n");
}

// E -> ,AAH | ,;FH             ( First set: , | ,; ) -----------------------------------------------------------------------------------------------
void E() {
    printf("E()\n");

    if (tokenInfo.tokenId == T3_Token && tokenInfo.tokenInstance[0] == ',' && tokenInfo.tokenInstance[1] != ';'){
        printf("Process { , } in E()\n");  // process ,
        tokenInfo = scanner();  // consume ,

        A();    // run non-terminal A
        A();    // run non-terminal A
        H();    // run non-terminal H

        printf("End of E()\n");
        return;
    }
    else if (tokenInfo.tokenId == T3_Token && tokenInfo.tokenInstance[0] == ',' && tokenInfo.tokenInstance[1] == ';') {
        printf("Process { ,; } in E()\n");  // process ,;
        tokenInfo = scanner();  // consume ,;

        F();    // run non-terminal F
        H();    // run non-terminal H

        printf("End of E()\n");
        return;
    }
    else {
        printf("ERROR parser.cpp-E(): { , | ,; } required. You gave { %s } - Line %d\n", tokenInfo.tokenInstance, tokenInfo.lineNum);
        exit(EXIT_FAILURE);
    }
}

// F -> t1 | t2         ( First set: t1 | t2 ) --------------------------------------------------------------------------------------------------------
void F() {
    printf("F()\n");

    if (tokenInfo.tokenId == T1_Token) {
        printf("Process t1 token { %s } in F()\n", tokenInfo.tokenInstance);  // process t1
        tokenInfo = scanner();  // consume t1

        printf("End of F()\n");
        return;
    }
    else if (tokenInfo.tokenId == T2_Token) {
        printf("Process t2 token { %s } in F()\n", tokenInfo.tokenInstance);  // process t2
        tokenInfo = scanner();  // consume t2

        printf("End of F()\n");
        return;
    }
    else {
        printf("ERROR parser.cpp-F(): { t1 | t2 } required. You gave { %s } - Line %d\n", tokenNames[tokenInfo.tokenId], tokenInfo.lineNum);
        exit(EXIT_FAILURE);
    }
}

// G -> B | C | J           ( First set: . | t2 | *" ) --------------------------------------------------------------------------------------------
void G() {
    printf("G()\n");

    if (tokenInfo.tokenId == T2_Token) {
        C();    // run non-terminal C

        printf("End of G()\n");
        return;
    }
    else if (tokenInfo.tokenId == T3_Token && tokenInfo.tokenInstance[0] == '.') {
        B();    // run non-terminal B

        printf("End of G()\n");
        return;
    }
    else if (tokenInfo.tokenId == T3_Token && tokenInfo.tokenInstance[0] == '*' && tokenInfo.tokenInstance[1] == '"') {
        J();    // run non-terminal J

        printf("End of G()\n");
        return;
    }
    else {
        printf("ERROR parser.cpp-F(): { t2 | . | *\" } required. You gave { %s } - Line %d\n", tokenInfo.tokenInstance, tokenInfo.lineNum);
        exit(EXIT_FAILURE);
    }
}

// H -> E? | G. | empty         ( First set: , ,; | . t2 *" | empty ) -------------------------------------------------------------------------------
void H(){
    printf("H()\n");

    if (tokenInfo.tokenId == T3_Token && tokenInfo.tokenInstance[0] == ',' ) {
        E();    // run non-terminal E

        if (tokenInfo.tokenId == T3_Token && tokenInfo.tokenInstance[0] == '?') {
            printf("Process { ? } in H()\n");   // process ?
            tokenInfo = scanner();  //consume ?

            printf("End of H()\n");
            return;
        }
        else {
            printf("ERROR parser.cpp-H(): { ? } required. You gave { %s } - Line %d\n", tokenInfo.tokenInstance, tokenInfo.lineNum);
            exit(EXIT_FAILURE);
        }
    }
    else if (tokenInfo.tokenId == T2_Token || (tokenInfo.tokenId == T3_Token && (tokenInfo.tokenInstance[0] == '.'
        || (tokenInfo.tokenInstance[0] == '*' && tokenInfo.tokenInstance[1] == '"')))) {

        G();    // run non-terminal G

            if (tokenInfo.tokenId == T3_Token && tokenInfo.tokenInstance[0] == '.') {
                printf("Process { . } in H()\n");   // process .
                tokenInfo = scanner();  //consume .

                printf("End of H()\n");
                return;
            } else {
                printf("ERROR parser.cpp-H(): { . } required. You gave { %s } - Line %d\n", tokenInfo.tokenInstance, tokenInfo.lineNum);
                exit(EXIT_FAILURE);
            }
    }
    else {
        printf("{empty} End of H()\n");
        return;
    }
}

// J -> *"A.        ( First set: *" ) ----------------------------------------------------------------------------------------------------------
void J() {
    printf("J()\n");

    if (tokenInfo.tokenId == T3_Token && tokenInfo.tokenInstance[0] == '*' && tokenInfo.tokenInstance[1] == '"') {
        printf("Process { *\" } in J()\n");   // process *"
        tokenInfo = scanner();  //consume *"

        A();    // run non-terminal A

        if (tokenInfo.tokenId == T3_Token && tokenInfo.tokenInstance[0] == '.') {
            printf("Process { . } in J()\n");   // process .
            tokenInfo = scanner();  //consume .

            printf("End of J()\n");
            return;
        }
        else {
            printf("ERROR parser.cpp-J(): { . } required. You gave { %s } - Line %d\n", tokenInfo.tokenInstance, tokenInfo.lineNum);
            exit(EXIT_FAILURE);
        }
    }
    else {
        printf("ERROR parser.cpp-J(): { *\" } required. You gave { %s } - Line %d\n", tokenInfo.tokenInstance, tokenInfo.lineNum);
        exit(EXIT_FAILURE);
    }
}

// X -> F?$ | .         ( First set: t1 t2 | . ) ----------------------------------------------------------------------------------------------
void X() {
    printf("X()\n");

    if (tokenInfo.tokenId == T1_Token || tokenInfo.tokenId == T2_Token) {
        F();    // run non-terminal F

        if (tokenInfo.tokenId == T3_Token && tokenInfo.tokenInstance[0] == '?' && tokenInfo.tokenInstance[1] == '$') {
            printf("Process { ?$ } in X()\n");   // process ?$
            tokenInfo = scanner();  //consume ?$

            printf("End of X()\n");
            return;
        }
        else {
            printf("ERROR parser.cpp-X(): { ?$ } required. You gave { %s } - Line %d\n", tokenInfo.tokenInstance, tokenInfo.lineNum);
            exit(EXIT_FAILURE);
        }
    }
    else if (tokenInfo.tokenId == T3_Token && tokenInfo.tokenInstance[0] == '.') {
        printf("Process { . } in X()\n");   // process .
        tokenInfo = scanner();  //consume .

        printf("End of X()\n");
        return;
    }
    else {
        printf("ERROR parser.cpp-X(): { t1 | t2 | . } required. You gave { %s } - Line %d\n", tokenInfo.tokenInstance, tokenInfo.lineNum);
        exit(EXIT_FAILURE);
    }
}

// Y -> H?Y | empty         ( First set: , ,; . t2 *" ? empty | empty ) ------------------------------------------------------------------------
void Y() {
    printf("Y()\n");

    if (tokenInfo.tokenId == T2_Token || (tokenInfo.tokenId == T3_Token && (tokenInfo.tokenInstance[0] == ',' || tokenInfo.tokenInstance[0] == '.'
        || tokenInfo.tokenInstance[0] == '?' || (tokenInfo.tokenInstance[0] == '*' && tokenInfo.tokenInstance[1] == '"')))){

            H();    // run non-terminal H

            if (tokenInfo.tokenId == T3_Token && tokenInfo.tokenInstance[0] == '?') {
                printf("Process { ? } in H()\n");   // process ?
                tokenInfo = scanner();  //consume ?

                Y();    // run non-terminal Y (right recursion)

                printf("End of Y()\n");
                return;
            }
            else {
                printf("ERROR parser.cpp-Y(): { ? } required. You gave { %s } - Line %d\n", tokenInfo.tokenInstance, tokenInfo.lineNum);
                exit(EXIT_FAILURE);
            }
    }
    else {
        printf("{empty} End of Y()\n");
        return;
    }
}