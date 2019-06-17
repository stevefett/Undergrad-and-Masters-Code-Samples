/*
	Steven Salmons
	CS136
	Project 1 -- Recursive Descent Parser

	Takes the assigned symbols associated with the grammar and returns
        an error if the grammar rules are violated, or a success message
        if the syntax is correctly parsed. 

*/


#include <ctype.h>
#include <stdlib.h>
#include <stdio.h>

int token; //holds current char to parse
int debug = 0;

/* recursive descent functions */

void command(void);
int program(void);
int isLetter(char c);
int stmtSeq(void);
int stmt(void);
int ifStmt(void);
int repeatStmt(void);
int assignStmt(void);
int readStmt(void);
int writeStmt(void);
int expr(void);
int compareOp(void);
int simpleExp(void);
int addop(void);
int term(void);
int mutop(void);
int factor(void);
int ident(void);
int charac(void);
int number(void);
int letter(void);
int digit(void);

void error(void)
{
	printf("Parsing error\n");
	exit(1);
}

//We get character tokens to parse.
void getToken(void)
{
	token = getchar();
}

//If the token checks out, grab the next token.
void match(char c)
{
	if (token == c)
		getToken();
	else
	{
		if (debug == 1)
			printf("expected %c got %c\n", c, token);
		error();
	}
}

//Checks to see if a token is a letter (x, y, or z)
int isLetter(char c)
{
	if ((c == 'X') || (c == 'Y') || (c == 'Z'))
		return 1;
	return 0;
}


//If the "program" token is a # char, end the parse and print.
void command(void)
{
	int result = program();
	if (token == '#')
		printf("Parsing successful!\n");
	else
		error();
}

//<program> ::= <stmt-seq>
int program(void)
{
	int result = stmtSeq();
	return result;
}

//<stmt-seq> ::= <stmt> { ; <stmt>}
int stmtSeq(void)
{
	int result = stmt();
	while (token == ';')
	{
		match(';');
		result = stmt();
	}
	if (debug == 1)
		printf("stmtSeq\n");
	return result;
}

/* <stmt> ::= <if-stmt> | <repeat-stmt> | <assign-stmt> | <read-stmt> | <write-stmt> */
int stmt(void)
{
	int result;
	if (token == 'I')
	{
		result = ifStmt();
	}
	else if (token == 'A')
	{
		result = repeatStmt();
	}
	else if (isLetter(token) == 1)
	{
		result = assignStmt();
	}
	else if (token == 'R')
	{
		result = readStmt();
	}
	else if (token == 'W')
	{
		result = writeStmt();
	}
	if (debug == 1)
		printf("stmt\n");
	return result;
}

/* <if-stmt> ::= if <exp> then <stmt-seq> [ else <stmt-seq> ] end  */
int ifStmt(void)
{
	int result;
	if (debug == 1)
		printf("if seen\n");
	match('I');
	result = expr();

	match('@');
	result = stmtSeq();
	if (token == '%')
	{
		match('%');
		result = stmtSeq();
	}
	match('$');
	if (debug == 1)
		printf("if-stmt\n");
	return result;
}

/* <repeat-stmt> ::= repeat <stmt-seq> until <exp> */
int repeatStmt(void)
{	
	int result;
	if (token == 'A')
	{
		match('A');
		result = stmtSeq();
	}
	if (token == 'U')
	{
		match('U');
		result = expr();
	}
	if (debug == 1)
		printf("repeatStmt\n");
	return result;
}

/* <assign-stmt> ::= <ident> := <expr> */
int assignStmt(void)
{
	int result;
	result = ident();
	if (token == '&')
	{
		match('&');
		result = expr();
	}
	if (debug == 1)
		printf("assignStmt\n");
	return result;
}

/* <read-stmt> ::= read <ident> */
int readStmt(void)
{
	int result;
	if (token == 'R')
	{
		match('R');
		result = ident();
	}
	if (debug == 1)
		printf("readStmt\n");
	return result;
	
}

/* <write-stmt> ::= write <expr> */
int writeStmt(void)
{
	int result;
	if (token == 'W')
	{
		match('W');
		result = expr();
	}
	if (debug == 1)
		printf("writeStmt\n");
	return result;
}

/* <expr> ::= <simple-exp> [ <compare-op> <simple-exp> ] */
int expr(void)
{
	int result;
	result = simpleExp();
	if ((token == '<') || (token == '='))
	{ 
		result = compareOp();
		result = simpleExp();
	}
	if (debug == 1)
		printf("expr\n");
	return result;
}

int compareOp(void)
{
	if (token == '<')
		match('<');
	else if (token == '=')
		match('=');
	if (debug == 1)
		printf("compareOp\n");
	return 1;
}

int simpleExp(void)
{
	int result = term();
	while ((token == '+') || (token == '-'))
	{
		result = addOp();
		result = term();
	}
	if (debug == 1)
		printf("simpleExp\n");
	return result;
}

int addOp(void)
{
	if (token == '+')
		match('+');
	if (token == '-')
		match('-');
	if (debug == 1)
		printf("addOp\n");
	return 1;
}

int term(void)
{
	int result = factor();
	while ((token == '*') || (token == '/'))
	{
		result = mutOp();
		result = factor();
	}
	if (debug == 1)
		printf("term\n");
	return result;
}

int mutOp(void)
{
	if (token == '*')
		match('*');
	if (token == '/')
		match ('/');
	if (debug == 1)
		printf("mutOp\n");
	return 1;
}

int factor(void)
{
	int result;
	if (token == '(')
	{
		match('(');
		result = expr();
		match(')');
	}
	else
	{
		result = number();
	}
	if (debug == 1)
		printf("factor\n");
	return result;
}

int ident(void)
{
	int result;
	result = letter();
	while ((token == 'X') || (token == 'Y') || (token == 'Z'))
	{
		result = charac();
	}
	if (debug == 1)
		printf("ident\n");
	return result;
}

int charac(void)
{
	int result;
	if ((token == 'X') || (token == 'Y') || (token == 'Z'))
	{
		result = letter();
	}
	else
		result = digit();
	if (debug == 1)
		printf("charac\n");
	return result;
}

int number(void)
{
	int result;
	result = digit();
	while ((token == '0') || (token == '1'))
	{
		result = digit();
	}
	if (debug==1)
		printf("number\n");
	return result;
}

int letter(void)
{
	int result;
	if (token == 'X')
	{
		match('X');
	}
	else if (token == 'Y')
	{
		match('Y');
	}
	else if (token == 'Z')
	{
		match('Z');
	}
	if(debug == 1)
		printf("letter\n");
	return 1;
}

int digit(void)
{
	int result;
	if (token == '1')
	{
		match ('1');
	}
	if (token == '0')
	{
		match('0');
	}
	if(debug==1)
		printf("digit!\n");
	return 1;
}


void parse(void)
{
	getToken();
	command();
}

int main()
{
	parse();
	return 0;
}
