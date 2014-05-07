%{
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*
 * Abstract syntax tree
 */
typedef struct ast {
	/*
	 * AST type (legal values
	 * are a subset of tokens)
	 */
	int type;

	/* 
	 * leaf values (only one is valid;
	 * which one depends on ast type)
	 */
	int i;
	char c;
	double r;

	/*
	 * Left & right kids (this
	 * particular tree is binary
	 * though ASTs can be of any
	 * kind)
	 */
	struct ast *left;
	struct ast *right;
} ast_t;

static ast_t *makenode(int op, ast_t *left, ast_t *right);
static ast_t *makeleaf(int op, int val, double rval, char id);
static int yyerror(ast_t **ast, const char *s);

extern int yylex();
%}

%union {
    int code;
	char name;
    double real;
    struct ast *ast;
}

%parse-param{struct ast **ast}
%destructor {free($$);} <ast>

%token PROGRAM INT REAL BOOL BGIN END PRINT
%token VAR IF THEN ELSE WHILE DO TRUE FALSE
%token TO FOR SWITCH CASE BREAK RECORD OF

%token DECLST STMLST CASLST PTR ARRAY INDLST RNGLST RANGE LEXERR

%token<code> INTCONST
%token<name> IDENT
%token<real> REALCONST

%type<ast> assign program stmt_seq while_stmt if_stmt if2 range range_lst
%type<ast> expr atom stmt decl_list var_decl switch_stmt print array_index
%type<ast> type for_stmt ident for_range integer decl case cases var simp_type

%nonassoc '<' LEQ EQ NEQ '>' GEQ
%left '+' '-' OR
%left '*' '/' AND '%'
%right NOT NEG DUMMY

%%
program : PROGRAM IDENT ';' decl
          BGIN stmt_seq END                  {*ast = makenode(PROGRAM, $4, $6); $$ = NULL;}
        ;

decl : VAR decl_list                         {$$ = $2;}
     |                                       {$$ = NULL;}
     ;

decl_list : var_decl                         {$$ = makenode(DECLST, NULL, $1);}
          | decl_list var_decl               {$$ = makenode(DECLST, $1, $2);}
          ;

var_decl : ident ':' type ';'                {$$ = makenode(VAR, $1, $3);}
         ;

simp_type : INT                              {$$ = makenode(INT, NULL, NULL);}
          | REAL                             {$$ = makenode(REAL, NULL, NULL);}
          | BOOL                             {$$ = makenode(BOOL, NULL, NULL);}
          | ident                            {$$ = $1;}
          ;

type : simp_type                             {$$ = $1;}
     | '^' simp_type                         {$$ = makenode(PTR, $2, NULL);}
     | RECORD decl_list END                  {$$ = makenode(RECORD, $2, NULL);}
     | ARRAY '[' range_lst ']' OF simp_type  {$$ = makenode(ARRAY, $3, $6);}
     ;

range : integer RANGE integer                {$$ = makenode(RANGE, $1, $3);}
      ;

range_lst : range_lst ',' range              {$$ = makenode(RNGLST, $1, $3);}
          | range                            {$$ = makenode(RNGLST, NULL, $1);}
          ;

stmt_seq : stmt_seq ';' stmt                 {$$ = makenode(STMLST, $1, $3);}
         | stmt                              {$$ = makenode(STMLST, NULL, $1);}
         |                                   {$$ = NULL;}
         ;
         
stmt : assign                                {$$ = $1;}
     | if_stmt                               {$$ = $1;}
     | while_stmt                            {$$ = $1;}
     | for_stmt                              {$$ = $1;}
     | switch_stmt                           {$$ = $1;}
     | print                                 {$$ = $1;}
     ;

assign :  var '=' expr                       {$$ = makenode('=', $1, $3);}
       ;

if_stmt : IF expr if2                        {$$ = makenode(IF, $2, $3);}  
        ;

if2 : '{' stmt_seq '}' ELSE '{' stmt_seq '}' {$$ = makenode(ELSE, $2, $6);}
    | '{' stmt_seq '}'                       {$$ = $2;}
	;

while_stmt : WHILE expr '{' stmt_seq '}'     {$$ = makenode(WHILE, $2, $4);}
           ; 

for_stmt : FOR for_range '{' stmt_seq '}'    {$$ = makenode(FOR, $2, $4);}
         ; 

for_range : assign TO integer                {$$ = makenode(TO, $1, $3);}
      ;

switch_stmt : SWITCH expr '{' cases '}'      {$$ = makenode(SWITCH, $2, $4);}
            ;

cases : case                                 {$$ = makenode(CASLST, NULL, $1);}
      | cases case                           {$$ = makenode(CASLST, $1, $2);}
      ;

case : CASE integer '{' stmt_seq '}'         {$$ = makenode(CASE, $2, $4);}
     ;

print : PRINT expr                           {$$ = makenode(PRINT, $2, NULL);}
      ;

expr : expr '+' expr                         {$$ = makenode('+', $1, $3);}
     | expr '-' expr                         {$$ = makenode('-', $1, $3);}
     | expr '*' expr                         {$$ = makenode('*', $1, $3);}
     | expr '/' expr                         {$$ = makenode('/', $1, $3);}
     | expr '%' expr                         {$$ = makenode('%', $1, $3);}
     | expr '<' expr                         {$$ = makenode('<', $1, $3);}
     | expr '>' expr                         {$$ = makenode('>', $1, $3);}
     | expr LEQ expr                         {$$ = makenode(LEQ, $1, $3);}
     | expr GEQ expr                         {$$ = makenode(GEQ, $1, $3);}
     | expr EQ expr                          {$$ = makenode(EQ, $1, $3);}
     | expr NEQ expr                         {$$ = makenode(NEQ, $1, $3);}
     | expr AND expr                         {$$ = makenode(AND, $1, $3);}
     | expr OR expr                          {$$ = makenode(OR, $1, $3);}
     | '(' expr ')'                          {$$ = $2;}
     | '-' atom %prec DUMMY                  {$$ = makenode(NEG, $2, NULL);}
     | NOT atom                              {$$ = makenode(NOT, $2, NULL);}
     | atom                                  {$$ = $1;}
     ;
 
atom : var                                   {$$ = $1;}
	 | integer                               {$$ = $1;}
     | REALCONST                             {$$ = makeleaf(REALCONST, 0, $1, '\0');}
     | TRUE                                  {$$ = makeleaf(TRUE, 0, 0, '\0');}
     | FALSE                                 {$$ = makeleaf(FALSE, 0, 0, '\0');}
     ;

integer : INTCONST                           {$$ = makeleaf(INTCONST, $1, 0, '\0');}
		;

ident : IDENT                                {$$ = makeleaf(IDENT, 0, 0, $1);}
      ;

var : ident                                  {$$ = $1;}
    | var '[' array_index ']'                {$$ = makenode(ARRAY, $1, $3);}
    | var '.' ident                          {$$ = makenode(RECORD, $1, $3);}
    | var '^'                                {$$ = makenode(PTR, $1, NULL);}
    ;

array_index : expr                           {$$ = makenode(INDLST, $1, NULL);}
            ;

%%

int yyerror(ast_t **ast, const char *s)
{
	extern int yylineno;

	fprintf(stderr, "Line %d: %s\n", yylineno, s ? s : "Parsing error");
	return 0;
}

static ast_t *makenode(int op, ast_t *left, ast_t *right)
{
    ast_t *ast;

    ast = (ast_t *)malloc(sizeof(ast_t));
	if (!ast) {
		fprintf(stderr, "Out of memory\n");
		exit(-1);
	}

	memset(ast, 0, sizeof(ast_t));
    
	ast->type = op;
	ast->left = left;
	ast->right = right;

	return ast;
}

static ast_t *makeleaf(int op, int i, double r, char c)
{
    ast_t *ast;
 
    ast = (ast_t *)malloc(sizeof(ast_t));
	if (!ast) {
		fprintf(stderr, "Out of memory\n");
		exit(-1);
	}
   
	memset(ast, 0, sizeof(ast_t));

	ast->type = op;
	ast->i = i;
	ast->r = r;
	ast->c = c;

    return ast;
}

static ast_t *create()
{
	ast_t *ast = NULL;

	yyparse(&ast);

	return ast;
}

static void destroy(ast_t *ast)
{
	if (ast == NULL)
		return;

	destroy(ast->left);
	destroy(ast->right);
	free(ast);
}

static const char *token2str(int token)
{
	switch (token) {
		case PROGRAM:
			return "PROGRAM";
		case REAL:
			return "REAL";
		case BOOL:
			return "BOOL";
        case INT:
            return "INT";
		case VAR:
			return "VAR";
		case IF:
			return "IF";
		case THEN:
			return "THEN";
		case ELSE:
			return "ELSE";
		case WHILE:
			return "WHILE";
		case TRUE:
			return "TRUE";
		case FALSE:
			return "FALSE";
		case LEQ:
			return "LEQ";
		case EQ:
			return "EQ";
		case NEQ:
			return "NEQ";
		case GEQ:
			return "GEQ";
		case NOT:
			return "NOT";
		case FOR:
			return "FOR";
		case AND:
			return "AND";
		case OR:
			return "OR";
        case DECLST:
            return "DECLST";
        case STMLST:
            return "STMLST";
        case SWITCH:
            return "SWITCH";
        case CASLST:
            return "CASLST";
		case INTCONST:
			return "INTCONST";
		case IDENT:
			return "IDENT";
		case REALCONST:
			return "REALCONST";
		case DUMMY:
			return "DUMMY";
        case RECORD:
            return "RECORD";
        case PTR:
            return "PTR";
        case PRINT:
            return "PRINT";
        case ARRAY:
            return "ARRAY";
        case INDLST:
            return "INDLST";
        case RNGLST:
            return "RNGLST";
        case RANGE:
            return "RANGE";
        case NEG:
            return "NEG";
        case CASE:
            return "CASE";
        case TO:
            return "TO";
        case '-':
            return "-";
        case '+':
            return "+";
        case '<':
            return "<";
        case '>':
            return ">";
        case '*':
            return "*";
        case '/':
            return "/";
        case '%':
            return "%";
        case '=':
            return "=";
		default:
			return "UNKOWN";
	}
}

static void print_node(ast_t *ast)
{
	if (ast->type == REALCONST)
		printf("REALCONST: %f\n", ast->r);
	else if (ast->type == INTCONST)
		printf("INTCONST: %d\n", ast->i);
	else if (ast->type == IDENT)
		printf("IDENT: %c\n", ast->c);
	else
		printf("%s\n", token2str(ast->type));
}

static void print_preorder(ast_t *ast)
{
    if (!ast) {
        printf("~\n"); /* Print ~ for empty tree */
        return;
    }

    print_node(ast);
    print_preorder(ast->left);
    print_preorder(ast->right);    
}

int main(int argc, char *argv[])
{
	ast_t *ast = create();

    print_preorder(ast);

	destroy(ast);

	return 0;
}

