#ifndef _parse_h
#define _parse_h

#define INIT_NODE_BUFFER 3;
#define INCR_NODE_BUFFER 2;

#include "lex.h"
#include <stddef.h>     // size_t

typedef enum { ROOT, ASSIGN, LITERAL, VARIABLE, BINOP, COMP, FUNCTION, CALL, BLOCK, DATATYPE } node_type_t;
typedef enum { NOREL, CONDITION, BODY, IFBODY, ELSEBODY, PARAMETER, SOURCE, DESTINATION, RETTYPE } node_relation_t;
typedef enum { NOVAL, STRINGVAL, INTVAL, TYPEVAL } node_value_type_t;
typedef enum { DATASTR, DATANUM, DATABOOL, DATAVOID } data_type_t;

typedef union {
    char*       string;
    int         integer;
} node_value_t;
typedef struct ast_node {
    node_type_t       type;
    node_relation_t   relation;
    node_value_t      value;
    node_value_type_t value_type;
    data_type_t       type_constraint;
    size_t            n_children;
    size_t            buffer_size;
    struct ast_node** children;
} ast_node_t;

typedef struct {
    size_t          i;
    token_stream_t* t;
} parse_stream_t;

/* ast.c */
ast_node_t* ast_node_new(node_type_t ntype, node_relation_t nrelation, data_type_t nconstraint);
void ast_node_assign_integer(ast_node_t* node, int nvalue);
void ast_node_assign_string(ast_node_t* node, char* nvalue);
void ast_node_add_child(ast_node_t* parent_node, ast_node_t* child_node);
void ast_node_destroy(ast_node_t* node);
void ast_node_print_tree(ast_node_t* node, int level);

/* parse.c */
int parse(token_stream_t* ts, ast_node_t* root_node);

#endif /* _parse_h */