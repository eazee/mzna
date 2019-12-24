#include "include/parse.h"
#include "include/mzna.h"
#include <string.h>
#include <stdlib.h>

const char* enum_node_type[] = {"root","assign","literal","variable","binop","comp","function","call","block","datatype"};
const char* enum_node_relation[] = {"norel","condition","body","ifbody","elsebody","parameter","source","destination","rettype"};
const char* enum_data_type[] = {"string","number","bool","void"};

ast_node_t* ast_node_new(node_type_t ntype, node_relation_t nrelation, data_type_t nconstraint) {
    ast_node_t* node = (ast_node_t*) malloc(sizeof(ast_node_t));
    node->type = ntype;
    node->relation = nrelation;
    node->n_children = 0;
    node->value_type = NOVAL;
    node->buffer_size = INIT_NODE_BUFFER;
    node->type_constraint = nconstraint;
    node->children = (ast_node_t**) malloc(node->buffer_size * sizeof(ast_node_t*));
    return node;
}
void ast_node_assign_integer(ast_node_t* node, int nvalue) {
    node->value.integer = nvalue;
    node->value_type = INTVAL;
}
void ast_node_assign_string(ast_node_t* node, char* nvalue) {
    node->value.string = (char*) malloc(strlen(nvalue)+1);
    strcpy(node->value.string, nvalue);
    node->value_type = STRINGVAL;
}
void ast_node_add_child(ast_node_t* parent_node, ast_node_t* child_node) {
    if(parent_node->n_children >= parent_node->buffer_size) {
        parent_node->buffer_size += INCR_NODE_BUFFER;
        parent_node->children = (ast_node_t**) realloc(parent_node->children, parent_node->buffer_size * sizeof(ast_node_t*));
    }
    parent_node->children[parent_node->n_children] = child_node;
    parent_node->n_children++;
}
void ast_node_destroy(ast_node_t* node) {
    if(node->n_children > 0) {
        for(int i = 0; i < node->n_children; i++) {
            ast_node_destroy(node->children[i]);
        }
    }
    if(node->value_type == STRING)
        free(node->value.string);
    free(node);
    printf("[Log] Destroying a node!\n");
}

// last_or_root   -1 = root, 0 = neutral, 1 = last
void ast_node_print_tree(ast_node_t* node, int level) {
    for(int s = 0; s < level; s++) {
        printf("╠════");
    }
    printf("╬═> %s", TRM_BLUE_BOLD);
    if(level == 0) {
        printf("Root%s: ", TRM_RESET);
    } else {
        printf("Node%s: ", TRM_RESET);
    }
    printf("[Type %s%s%s - Relation %s%s%s", TRM_GREEN, enum_node_type[node->type], TRM_RESET, TRM_GREEN, enum_node_relation[node->relation], TRM_RESET);
    if(node->type_constraint != DATAVOID) {
        printf(" - Constraint %s%s%s]", TRM_GREEN, enum_data_type[node->type_constraint], TRM_RESET);
    } else {
        printf("]");
    }
    if(node->value_type == STRINGVAL) {
        printf(" ('%s')\n", node->value.string);
    } else if(node->value_type == INTVAL) {
        printf(" (%d)\n", node->value.integer);
    } else {
        printf("\n");
    }
    for(int i = 0; i < node->n_children; i++) {
        ast_node_print_tree(node->children[i], level+1);
    }
}