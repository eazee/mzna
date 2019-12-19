#ifndef _parse_h
#define _parse_h

typedef enum {} node_type_t;
typedef struct {} ast_node_t;

/* parse.c */
int parse(TokenStream* ts);

#endif /* _parse_h */