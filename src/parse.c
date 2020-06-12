#include "include/parse.h"
#include "include/mzna.h"
#include <string.h>         // strcmp

int check_type(parse_stream_t* ps, int lookahead, token_type_t type_check) {
    int index = ps->i + lookahead;
    if(index < ps->t->size)
        return (ps->t->stream[index].type == type_check) ? 1 : 0;
    return 0;
}

int has_space(parse_stream_t* ps) {
    if(ps->i < ps->t->size)
        return 1;
    return 0;
}

data_type_t type_from_ident(char* ident) {
    if(strcmp(ident, "string") == 0)
        return DATASTR;
    else if(strcmp(ident, "bool") == 0)
        return DATABOOL;
    else if(strcmp(ident, "num") == 0)
        return DATANUM;
    return DATAVOID;
}

/* if         := "if" expression ifblock
   ifblock    := colon  (statement)*  ("elif" statement*) ("else" statement*) end */
int if_statement(parse_stream_t* ps, ast_node_t* node);

/* while      := "while" expression  block */
int while_statement(parse_stream_t* ps, ast_node_t* node);

/* statement  := assignment | call | if | while */
int statement(parse_stream_t* ps, ast_node_t* node) {}

/*
block      := (singleblock | multiblock)
singleblock := colon statement
multiblock := colon  newline  ( statement  (newline  statement)* )  end
*/
int one_line_block(parse_stream_t* ps, ast_node_t* node) {
    if(check_type(ps, 0, COLON)) {
        ps->i++;
    } else {
        return -1;
    }
    return statement(ps, node);
}

int multi_line_block(parse_stream_t* ps, ast_node_t* node) {
    if(check_type(ps, 0, COLON)) {
        ps->i++;
    } else {
        return -1;
    }
    if(check_type(ps, 0, NEWLINE)) {
        ps->i++;
    } else {
        fprintf(stderr, "[%sSyntax Error%s] Expecting newline, near Line %d Col %d");
        return -1;
    }
}

int block(parse_stream_t* ps, ast_node_t* node, node_relation_t relation, data_type_t nconstraint) {
    if(check_type(ps, 0, COLON) != 1) {
        fprintf(stderr, "[%sSyntax Error%s] Expecting colon at start of block, near Line %d Col %d",
            TRM_RED_BOLD, TRM_RESET, ps->t->stream[ps->i].row, ps->t->stream[ps->i].col);
        return -1;
    }

    ast_node_t* block_node = ast_node_new(BLOCK, relation, nconstraint);
    ast_node_add_child(node, block_node);
    if(check_type(ps, 1, NEWLINE))
        return multi_line_block(ps, block_node);
    return one_line_block(ps, block_node);
}

// params :=  param_op   (value  type  (, value type)+)
int params(parse_stream_t* ps, ast_node_t* node) {
    if(check_type(ps, 0, PARAMOP) != 1)
        return -1;
    ps->i++;
    while(check_type(ps, 0, IDENT) && check_type(ps, 1, TYPE)) {
        ast_node_t* param_node =   ast_node_new(VARIABLE, PARAMETER, type_from_ident(ps->t->stream[ps->i+1].value));
        ast_node_assign_string(param_node, ps->t->stream[ps->i].value);
        ast_node_add_child(node, param_node);
        ps->i += 2;
        if(check_type(ps, 0, COMMA))
            ps->i += 1;
    }
    if(check_type(ps, 0, IDENT) && (check_type(ps, 1, TYPE) != 1)) {
        fprintf(stderr, "[%sSyntax Error%s] Expecting data type after parameter, near Line %d Col %d\n",
            TRM_RED_BOLD, TRM_RESET, ps->t->stream[ps->i].row, ps->t->stream[ps->i].col);
        return -1;
    }
    return 0;
}

// function := ident (type) (params) block
int function(parse_stream_t* ps, ast_node_t* node) {
    data_type_t nconstraint = DATAVOID;
    if(check_type(ps, 0, IDENT) != 1)
        return -1;
    ast_node_t* func_node = ast_node_new(FUNCTION, BODY, nconstraint);
    ast_node_add_child(node, func_node);
    ast_node_assign_string(func_node, ps->t->stream[ps->i].value);
    ps->i++;
    if(check_type(ps, 0, TYPE)) {
        nconstraint = type_from_ident(ps->t->stream[ps->i].value);
        node->type_constraint = nconstraint;
        ps->i++;
    }
    if(check_type(ps, 0, PARAMOP)) {
        params(ps, func_node);
    }

    return block(ps, func_node, BODY, nconstraint);
}

// program := (assignment | function)*
int program(parse_stream_t* ps, ast_node_t* node) {
    while(has_space(ps)) { // * loop
        // If loose newline
        if(check_type(ps, 0, NEWLINE)) {
            ps->i++;
            continue;
        }
        // If function declaration
        if( (check_type(ps, 0, IDENT) && (check_type(ps, 1, PARAMOP) || (check_type(ps, 1, TYPE) && check_type(ps, 2, PARAMOP)))) 
            || (check_type(ps, 0, IDENT) && check_type(ps, 1, COLON)) ) {
            if(function(ps, node) != 0)
                return -1;
        } else {
            fprintf(stderr, "[%sSyntax Error%s] Expecting variable assignment or function declaration, near Line %d Col %d\n",
                TRM_RED_BOLD, TRM_RESET, ps->t->stream[ps->i].row, ps->t->stream[ps->i].col);
            return -1;
        }
    }
    return 0;
}

int parse(token_stream_t* ts, ast_node_t* root_node) {
    parse_stream_t ps = {0, ts};
    int status = program(&ps, root_node);   // 0 = success, anything else is fail
    return status;
}
