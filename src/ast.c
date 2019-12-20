#include "include/mzna.h"

ast_node_t* ast_node_new(node_type_t type_c, int n_children_c);
void ast_node_init(ast_node_t* node);
void ast_node_add_child(ast_node_t* parent_node, ast_node_t* child_node);
void ast_node_destroy(ast_node_t* node);