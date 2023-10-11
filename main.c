#include "main.h"

const double PI = 3.141592;

int node_parse(const char *str, struct ParseState *p)
{
    yy_switch_to_buffer(yy_scan_string(str));
    return yyparse(p);
}


int main(int argc, char **argv)
{
    const char *str = "sin{30} * ( cos{30} + 6 )";
    struct ParseState p;

    int n = node_parse(str, &p);
    if(n != 0)
    {
        return 1;
    }

    value_t result;
    printf("Calculating node...: %s\n", str);
    result = calculator(p.node);
    printf("Result: %lf", result);

    delete_node(p.node);
    return 0;
}

value_t calculator(struct Node *node)
{
    if(node->type == NODE_DATA)
    {
        switch (node->value.bin.tri_type)
        {
        case TRI_COS:
            return cos(node->value.bin.v * PI / 180);
        
        case TRI_SIN:
            return sin(node->value.bin.v * PI / 180);

        case TRI_TAN:
            return tan(node->value.bin.v * PI / 180);

        case TRI_NONE: 
            return node->value.bin.v;
        }
    }
    
    else if(node->type == NODE_OP)
    {
        value_t left = calculator(node->value.op.left);
        value_t right = calculator(node->value.op.right);

        switch (node->value.op.op_type)
        {
        case OP_ADD:
            return left + right;
        
        case OP_SUB:
            return left - right;

        case OP_MUL:
            return left * right;

        case OP_DIV:
            return left / right;
        }
    }

    return 0.0;
}

void delete_node(struct Node *node)
{
    if(node == NULL)
    {
        return;
    }

    if(node->type == NODE_DATA)
    {
        free(node);
    }
    else if(node->type == NODE_OP)
    {
        delete_node(node->value.op.left);
        delete_node(node->value.op.right);
    }

    return;
}

void dump(struct Node *node)
{
    if(node == NULL)
    {
        return;
    }

    if(node->type == NODE_DATA)
    {
        switch (node->value.bin.tri_type)
        {
        case TRI_COS:
            printf("cos(%lf)\n", node->value.bin.v);
            break;
        
        case TRI_SIN:
            printf("sin(%lf)\n", node->value.bin.v);
            break;

        case TRI_TAN:
            printf("tan(%lf)\n", node->value.bin.v);
            break;

        case TRI_NONE: 
            printf("%lf\n", node->value.bin.v);
        }
    }
    
    else if(node->type == NODE_OP)
    {
        dump(node->value.op.left);
        dump(node->value.op.right);
        printf("op: %d\n", node->value.op.op_type);
    }
}