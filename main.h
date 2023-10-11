#ifndef _MAIN_H_
#define _MAIN_H_

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

#define OP_ADD 1
#define OP_SUB 2 
#define OP_MUL 3
#define OP_DIV 4

#define TRI_NONE 0 
#define TRI_SIN 1 
#define TRI_COS 2 
#define TRI_TAN 3

#define NODE_OP 1 
#define NODE_DATA 2

typedef uint32_t tri_t;
typedef uint32_t op_t;
typedef double value_t;

struct Node
{
    int type;
    union 
    {
        struct BinValue
        {
            tri_t tri_type; 
            value_t v;
        } bin;

        struct BinOp
        {
            op_t op_type;
            struct Node *left; 
            struct Node *right;
        } op;

    } value;
};

struct ParseState
{
    struct Node *node;
};

typedef struct yy_buffer_state *YY_BUFFER_STATE;

void yy_switch_to_buffer ( YY_BUFFER_STATE new_buffer  );
YY_BUFFER_STATE yy_scan_string ( const char *yy_str  );
int yyparse(struct ParseState*);

struct Node *gen_value_node(tri_t t, value_t v);
struct Node *gen_op_node(op_t op, struct Node *left, struct Node *right);

void dump(struct Node *node);
value_t calculator(struct Node *node);

void delete_node(struct Node *node);

#endif