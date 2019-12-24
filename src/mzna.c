#include "include/mzna.h"
#include "include/lex.h"
#include "include/parse.h"
#include <stdio.h>          // fprintf, fopen, fclose
#include <stdlib.h>         // malloc

int begin_compile(FILE* infile) {
    // Initialise
    token_stream_t ts;
    token_stream_init(&ts);
    int status = -1;        // assume failure until successful compile gives status of 0

    ast_node_t* root_node = ast_node_new(ROOT, NOREL, DATAVOID);

    // Run compilation
    printf("[Log] === Lexer ===\n");
    if(lex(infile, &ts) == 0) {
        printf("[Log] Tokenisation complete. Found %d tokens.\n", ts.size);
        for(int i = 0; i < ts.size; i++) {
            printf("[[[TOKEN]]] %d: %s\n", ts.stream[i].type, ts.stream[i].value);
        }
        printf("[Log] === Parser ===\n");
        if(parse(&ts, root_node) == 0) {
            
            status = 0; // assume success

        }
    }

    ast_node_print_tree(root_node, 0);  // DEBUG

    // Clean up
    printf("[Log] === Cleaning up ===\n");
    fclose(infile);
    token_stream_destroy(&ts);
    ast_node_destroy(root_node);

    return status;
}

FILE* try_file(char* filename) {
    FILE *fptr;
    fptr = fopen(filename, "r");
    if(fptr == NULL) {
        fprintf(stderr, "%sYikes!%s Could not open the file %s for reading.\n", TRM_RED_BOLD, TRM_RESET, filename);
        return NULL;
    }
    return fptr;
}

int main(int argc, char * argv[]) {
    if(argc > 1) {
        int src_i = -1;
        FILE* fptr;
        for(int i = 1; i < argc; i++) {
            if(argv[i][0] != '-') {
                src_i = i;
            }
        }
        if(src_i != -1) {
            fptr = try_file(argv[src_i]);
            if(fptr == NULL) return 1;
            return begin_compile(fptr);
        } else {
            fprintf(stderr, "%sUh-oh!%s Please supply a source file.\n", TRM_RED_BOLD, TRM_RESET);
        }
        return 0;
    }
    fprintf(stderr, "%sUh-oh!%s Please supply a source file.\n", TRM_RED_BOLD, TRM_RESET);
    return 1;
}