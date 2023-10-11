# 삼각함수 계산기 
main함수에 정의된 삼각함수가 포함된 수학식을 문법에 맞게 파싱하고 계산해주는 프로젝트

# Usage
```Shell
sh build.sh
```

# Example 
```
➜  night ./program
Calculating node...: sin{30} * ( cos{30} + 6 )
Result: 3.433012%
➜  night
```
터미널창에서 '*'와 '(' 문자에 대해 와일드카드 및 쉘 함수로 인식하여 파일로의 파싱 또는 "" 문자열로 묶어서 파싱하거나 해야하기에 추후 개선사항으로 남겨두었습니다.

# Main Logic 
```C
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
```
계산을 하기 위해서는 트리구조를 이루어야 합니다. 그렇기에 트리의 원소 단위를 `struct Node`로 정의합니다. 이때 Node값이 연산자일 수 있고 값일 수 있습니다. 그렇기에 type을 두고 union으로 처리합니다.

```C
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
```
하나의 추상 구문트리로 만들어지는 Node를 후위연산하여 처리합니다. 각 노드의 타입에 맞게 삼각함수를 계산하고 OP코드에 맞게 연산을 처리합니다. 

```C
expr : expr T_ADD expr 
    {
        $$ = gen_op_node(OP_ADD, $1, $3); 
    }
    | expr T_SUB expr 
    {
        $$ = gen_op_node(OP_SUB, $1, $3);
    }
    | expr T_MUL expr 
    {
        $$ = gen_op_node(OP_MUL, $1, $3);
    }
    | expr T_DIV expr 
    {
        $$ = gen_op_node(OP_DIV, $1, $3);
    }
    | '(' expr ')' 
    {
        $$ = $2;
    }
    | term
    {
        $$ = $1;
    }
    ;
```
정의한 문법입니다. Context Free Grammar형태로 작성되어 있으며 규칙에 맞게 `gen_op_node` 함수를 호출하거나 `gen_value_node`를 호출하여 노드를 추상구문트리로 만들기 위한 과정을 거칩니다. 

```C
[ \t]+	; // ignore all whitespace
\n		{return T_NEWLINE;}
[0-9]+		{yylval.value = atoi(yytext); return T_VALUE;}
"sin" { return T_SIN;}
"cos" { return T_COS;}
"tan" { return T_TAN;}
"{" {return '{';}
"}" {return '}';}
"(" {return '(';}
")" {return ')';}
"+" {return T_ADD;}
"-" {return T_SUB;}
"*" {return T_MUL;}
"/" {return T_DIV;}
```
렉서부분입니다. 입력값 문자열에 대해 토큰처리를 진행합니다. 그 외의 문자가 들어올 시 에러를 출력하고 프로그램을 끝냅니다.# circular_function_calculator
