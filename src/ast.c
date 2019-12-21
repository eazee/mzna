#include "include/parse.h"
#include <string.h>
#include <stdlib.h>

void ast_node_init(ast_node_t* node, node_type_t ntype, node_relation_t nrelation) {
    node->type = ntype;
    node->relation = nrelation;
    node->n_children = 0;
    node->value_type = NOVAL;
    node->buffer_size = INIT_NODE_BUFFER;
    node->children = (ast_node_t**) malloc(node->buffer_size * sizeof(ast_node_t*));
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
    free(node);
}