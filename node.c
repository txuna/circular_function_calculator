#include "main.h"

struct Node *gen_value_node(tri_t t, value_t v)
{
    struct Node *node = (struct Node*)malloc(sizeof(struct Node));
    if(node == NULL)
    {
        return NULL;
    }

    node->type = NODE_DATA;
    node->value.bin.tri_type = t; 
    node->value.bin.v = v;

    return node;
}


struct Node *gen_op_node(op_t op, struct Node *left, struct Node *right)
{
    struct Node *node = (struct Node*)malloc(sizeof(struct Node));
    if(node == NULL)
    {
        return NULL;
    }

    node->type = NODE_OP;
    node->value.op.op_type = op; 
    node->value.op.left = left; 
    node->value.op.right = right;

    return node;
}