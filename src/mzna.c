#include "include/mzna.h"

int begin_compile(FILE* infile) {
    parse(infile);
    // Clean up
    fclose(infile);
    return 0;
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