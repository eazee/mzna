#ifndef _parse_h
#define _parse_h

typedef enum { ROOT, ASSIGN, LITERAL, VARIABLe, BINOP, COMPOP, FUNCTION, CALL, BLOCK } node_type_t;
typedef enum { CONDITION, BODY, IFBODY, ELSEBODY, PARAMETER, SOURCE, DESTINATION } node_relation_t;
typedef union {
    char* string;
    int   integer;
} ast_value_t;
typedef struct {
    node_type_t     type;
    node_relation_t relation;
    ast_value_t     value;
    int             n_children;
    int             buffer_size;
    ast_node_t**    children;
} ast_node_t;

/* ast.c */
ast_node_t* ast_node_new(node_type_t type_c, int n_children_c);
void ast_node_init(ast_node_t* node);
void ast_node_add_child(ast_node_t* parent_node, ast_node_t* child_node);
void ast_node_destroy(ast_node_t* node);

/* parse.c */
int parse(token_stream_t* ts);

#endif /* _parse_h */