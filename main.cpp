/*
 *  CS4280 - Project P2
 *      - by. Jeremy Zahrndt
 *      - main.cpp
 */
#include <stdio.h>
#include <stdlib.h>

#include "parser.h"
#include "testTree.h"

FILE* filePointer = nullptr;

// main function -------------------------------------------------------------------------------------------------------------------
int main(int argc, char* argv[]) {
    node_t* tree = NULL;
    char* file;
    int character;
    bool outputFileCreated = false;

    // check the number of commands
    if (argc > 2) {
        printf("Fatal: Improper Usage!\nUsage: P0 [fileName]\n");
        return EXIT_FAILURE;
    }

    // process command line arguments
    if (argv[1] != nullptr) {
        file = argv[1];
    } else {
        // set up keyboard processing so that hereafter the input method is not relevant
        file = "out";
        FILE* outputFilePointer = fopen(file, "w");
        outputFileCreated = true;
        character = getchar();
        while (character != EOF) {
            fputc(character, outputFilePointer);
            character = getchar();
        }
        fclose(outputFilePointer);
    }

    // make sure file is readable, error otherwise
    filePointer = fopen(file, "r");
    if (filePointer == nullptr) {
        perror("Fatal: Error Opening File!\n");
        fclose(filePointer);
        return EXIT_FAILURE;
    }

    // Test Scanner function call
    tree = parser();
    testTree(tree);

    if (outputFileCreated) {
        system("rm out");
    }
    system("rm filter.txt");
    return 0;
}