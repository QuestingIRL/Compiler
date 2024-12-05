//=======================================================================================
// Definitions and Includes
%{
#include <stdio.h>  // For standard I/O operations
#include <stdlib.h> // For memory management functions like malloc
#include <string.h> // For string manipulation functions

#include "symboltable.h" // Symbol table management
#include "ast.h"         // Abstract Syntax Tree structure and functions
#include "tac.h"         // Three Address Code (TAC) generation
#include "mips.h"        // MIPS assembly generation

// External declarations for lexer and parser
extern int yylex();
extern int yyparse();
extern FILE* yyin; // Input file for parsing

// Semantic and execution state variables
int computeEquation(struct AST* num1, struct AST* num2, char operator); // Function to compute expressions
void yyerror(const char* s); // Error reporting function

// Global state variables
char currentScope[50] = "GLOBAL"; // Current scope of parsing (e.g., global or function name)
char currReturnType[10];          // Current return type in parsing
int semanticCheckPassed = 1;      // Semantic check success flag
int goToElse = 0;                 // Condition flag for if-else blocks
int maxParam = 0;                 // Maximum parameters allowed in a function
int paramCount = 0;               // Current count of parameters in a function
int inFunction = 0;               // Flag indicating if inside a function definition
int hasMath = 0;                  // Flag indicating if a math operation is detected
char mathVal1[10], mathVal2[10];  // Temporary storage for math operands
char conditionString[50];         // String representation of conditions
int stringCount = 0;              // Counter for unique string identifiers

%}

// Lexer and Parser Union
%union {
    int number;                   // Integer values
    float floatValue;             // Float values
    char character;               // Single character
    char* string;                 // Strings
    struct AST* ast;              // Abstract Syntax Tree node
}

// Token Definitions
%token <string> ID            // Identifier
%token <number> INTEGER       // Integer constant
%token <floatValue> DECIMAL   // Decimal constant
%token <string> STRING        // String constant
%token <string> SEMICOLON     // ;
%token <string> EQ            // =
%token <string> WRITE         // write keyword
%token <string> SWRITE        // swrite keyword
%token <string> FUNC          // function keyword
%token <string> PLUS          // +
%token <string> MINUS         // -
%token <string> MULTIPLY      // *
%token <string> DIVIDE        // /
%token <string> LBRACKET      // [
%token <string> RBRACKET      // ]
%token <string> LPAREN        // (
%token <string> RPAREN        // )
%token <string> LBRACE        // {
%token <string> RBRACE        // }
%token <string> INT           // int keyword
%token <string> CHAR          // char keyword
%token <string> FLOAT         // float keyword
%token <string> RETURN        // return keyword
%token <string> WRITELN       // writeln keyword
%token <string> CHARACTER     // Character constant

// Operator Precedence
%left PLUS MINUS
%left MULTIPLY DIVIDE

// Token Printing for Debugging
%printer { fprintf(yyoutput, "%s", $$); } ID;
%printer { fprintf(yyoutput, "%d", $$); } INTEGER;

// Non-terminal Types
%type <ast> Program DeclList Decl VarDeclList FunDeclList VarDecl FunDecl FunCall ParamDecList Block ParamDecListTail ParamDecl Type Stmt StmtList ArrayExpr Expr MathExpr Trm Factor ParamList Primary UnaryOp BinOp 

// Start Symbol
%start Program

%%

// Grammar Rules and Actions

Program: 
    DeclList {
        $$ = $1; 
        // Uncomment below to visualize the AST (adjust function as needed)
        // printAST($$, 3);
    }
;

DeclList:	
    Decl DeclList { 
        $1->right = $2; // Link declarations sequentially in AST
        $$ = $1;        // Return the combined AST
    } 
    | Decl {
        $$ = $1;        // Single declaration
    }
    | FunDeclList {
        $$ = $1;        // Function declaration list
    }
;

Decl: 		
    VarDecl {
        // Variable declaration action can be expanded if needed
    }
    | StmtList {
        // Statements list, placeholder for further actions
    }
;

VarDeclList: 
    { /* Empty variable declaration list */ }
    | VarDecl VarDeclList {
        $1->right = $2; // Link variable declarations
        $$ = $1;
    }
    | VarDecl {
        $$ = $1;        // Single variable declaration
    }
;

VarDecl: 
	Type ID SEMICOLON {

		printf("\nRECOGNIZED RULE: VARIABLE declaration %s\n", $2);


		// ----- SYMBOL TABLE ----- //
		int inSymTab = found($2, currentScope);
		

		// ------ SEMANTIC CHECKS ------ //
		if (inSymTab == 0)  {
			addItem($2, "VAR", $1->nodeType, currentScope);
			//showSymTable();
		}
		else {
			printf("SEMANTIC ERROR: Var %s is already in the symbol table\n", $2);
			semanticCheckPassed = 0;
		}


		// ------  AST  ------ //
		if (semanticCheckPassed) {

			$$ = AST_Type("TYPE", $1->nodeType, $2);

			
		}

		semanticCheckPassed = 1;
	}
	

	// ------ ARRAY DECL ------ //
	| Type ID LBRACKET INTEGER RBRACKET SEMICOLON {
		
		printf("\nRECOGNIZED RULE: ARRAY declaration %s\n\n", $2);

		// ----- SYMBOL TABLE ----- //
		//symTabAccess();

		int inSymTab = found($2, currentScope);

		if (inSymTab == 0) {
			char arrIndex[12];
			for (int i = 0; i < $4; i++) {
				sprintf(arrIndex, "%s[%d]", $2, i);
				addItem(arrIndex, "ARRAY", $1->nodeType, currentScope);				
			}

			//showSymTable();
		} else {
			printf("SEMANTIC ERROR: Var %s is already in the symbol table\n", $2);
		}


		// ----- AST ----- //
		char intVal[50]; 
		sprintf(intVal, "%d", $4);
		$$ = AST_assignment("ARR", intVal, $2);


		// ---- MIPS CODE ---- //
		emitMIPSArrayDecl($2, $4);

		semanticCheckPassed = 1;
	} 
;

FunDeclList: 
	FunDecl 

	| FunDecl FunDeclList {
		

	}
;

FunDecl:
	FUNC Type ID LPAREN {

		inFunction = 1;

		printf("\nRECOGNIZED RULE: Function Declaration \"%s\"\n\n", $3);
		printf("ID = %s\n", $3);
		strcpy(currentScope, $3);
		printf("\n------------------- Scope Change --> ");
		printf("%s", currentScope);
		printf(" -------------------\n");


		// ----- SYMBOL TABLE ----- //
		symTabAccess();
		int inSymTab = found($3, currentScope);

		// ------ SEMANTIC CHECKS ------ //
 		if (inSymTab == 0) {
			
			addItem($3, "FUNC", $2->nodeType, currentScope);

		} 
		else {
			printf("SEMANTIC ERROR: Function %s is already in the symbol table\n", $2->nodeType);
			semanticCheckPassed = 0;
		}

		// ---- MIPS CODE ---- //
		if (semanticCheckPassed) {
			emitMIPSFunc($3);
		}

		semanticCheckPassed = 1;

	} 

	ParamDecList RPAREN Block {

		//showSymTable(); //updates for function and parameters

		// ----- AST ----- //
		if (semanticCheckPassed) {
			$$ = AST_assignment("FUNC", $2->nodeType, $3);		


		}

		// Leave Function in MIPScode.h
		endOfMIPSFunction($3);
	
		semanticCheckPassed = 1;
		inFunction = 0;
		maxParam = 0;
		paramCount = 0;

	}
;


ParamDecList: /* EPSILON */ {printf("No ParamDeclList (EPSILON)\n\n");}

	| ParamDecListTail {
		printf("Parameters Detected--->\n");
		$$ = $1;
	}

;

ParamDecListTail: 
	ParamDecl {	

		if (maxParam < 4) {
			maxParam++;
		} else {
			printf("WARNING!! Too many parameters in FunDecl");
		}
	}

	| ParamDecl ParamDecListTail {
		$1->right = $2; 
		$$ = $1;
	}

;

ParamDecl: 
	Type ID {

		printf("\nRECOGNIZED RULE: Parameter VARIABLE declaration %s\n\n" , $2);

		int inSymTab = found($2, currentScope);

		if (inSymTab == 0) {
			addItem($2, "PARAM", $1->nodeType, currentScope);
			//showSymTable();
		} 
		else {
			printf("\nSEMANTIC ERROR: Var %s is already in the symbol table\n", $2);
		} 

		emitMIPSParameters($2, paramCount);
		paramCount++;

	}

;

Block: 
	LBRACE DeclList RBRACE {
		$$ = $2;
		
	}
;


Type: INT {}
	| FLOAT {}
	| CHAR {}



StmtList: 
	Stmt 

	| Stmt StmtList {
		$1->right = $2;
		$$ = $1;
	}
;


Stmt: 
	SEMICOLON {
		printf("\nRECOGNIZED RULE: SEMICOLON %s\n", $1);	
	} 


	| Expr SEMICOLON {
		hasMath = 0;
		$$ = $1;
	}

	| RETURN Expr SEMICOLON {		

		printf("RETURN Statement Recognized!\n");


		// ----- AST ----- //
		$$ = AST_assignment("RETURN", "", $2->RHS);

		char *returnType = $2->nodeType;
	
		char val[25];
		if (!strcmp(returnType, "id")) {
			strcpy(val, getValue($2->RHS, currentScope));
		} else {
			strcpy(val, $2->RHS);
		}
		setItemValue(currentScope, val, currentScope);

		if (strcmp(currentScope, "main")) {
			emitMIPSReturn($2->RHS, returnType);
		}

		hasMath = 0;

	}


	| WRITE Expr SEMICOLON {
		printf("\nRECOGNIZED RULE: Write Statement\n");

		$$ = AST_Write("WRITE", "", $2->RHS);

		emitIRWriteId($2->RHS, getVariableType($2->RHS, currentScope));
		
		if (!strcmp($2->nodeType,"id")) {

			emitMIPSWriteId($2->RHS, getVariableType($2->RHS, currentScope));

		}

		else if (!strcmp($2->nodeType, "int")) {

			emitMIPSWriteInt(atoi($2->RHS));

		}

		else if (!strcmp($2->nodeType, "char")) {

			emitMIPSWriteId($2->RHS, getVariableType($2->RHS, currentScope));

		}
		
	}

	| WRITELN SEMICOLON {

		printf("\nRECOGNIZED RULE: Write Line %s\n", $1);

	 	$$ = AST_assignment("WRITELN", "", "");

		emitMIPSNewLine();
	}

	| SWRITE STRING SEMICOLON {

		printf("\nRECOGNIZED RULE: Write String %s\n", $2);

		emitMIPSString($2, stringCount);

		stringCount++;

	}

;

ArrayExpr:

	ID LBRACKET INTEGER RBRACKET EQ Primary {

		printf("\nRECOGNIZED RULE: ARRAY assignment %s\n", $1);

		//symTabAccess();
		int inSymTab = found($1, currentScope);

		if (inSymTab != 0) {
			printf("\nSEMANTIC ERROR: ARR %s is NOT in the symbol table\n", $2);
			semanticCheckPassed = 0;
		} else {
			printf("\nSEMANTIC CHECK PASSED\n");
			
		}
		
		char arrayStmt[10]; char newVal[10];
		sprintf(arrayStmt, "%s%s%d%s", $1, $2, $3, $4);

		setItemValue(arrayStmt, $6->RHS, currentScope);

		$$ = AST_assignment("=", arrayStmt, newVal);		


		emitMIPSIntArrayAssign($1, $3, atoi($6->RHS));

	}


	| ID EQ ID LBRACKET INTEGER RBRACKET {

		//symTabAccess();
		int inSymTab = found($1, currentScope);

		// Getting array value in the symbol table
		if (inSymTab) {

			char arrayStmt[10]; char newVal[10];
			sprintf(arrayStmt, "%s%s%d%s", $3, $4, $5, $6);

			int arrayVal = atoi(getValue(arrayStmt, currentScope));
			sprintf(newVal, "%d", arrayVal);


			// ---- SYMBOL TABLE ---- //
			setItemValue($1, newVal, currentScope);


			// ------ AST ------ //
			$$ = AST_assignment("=", $1, newVal);

		}

	}

;

Expr: 
	Primary 

	| MathExpr

	| ArrayExpr

	| FunCall {paramCount = 0; $$ = $1;}

	| UnaryOp Expr { 

		//symTabAccess();
		int inSymTab = found($2->RHS, currentScope);
		//printf("looking for %s in symtab - found: %d \n", $2, inSymTab);
		if (inSymTab == 0) {
			printf("\nSEMANTIC ERROR: Expr %s is NOT in the symbol table\n", $2->nodeType);
		}
		//showSymTable();

	}

	| ID EQ Expr {
		
		printf("\nRECOGNIZED RULE: Assignment Statement ----> %s\n", $1);
		int inSymTab = found($1, currentScope);

		
		// Variable to tell if value has been assigned yet; 1 is true
		int isNullValue = !strcmp(getValue($1, currentScope), "NULL");
		int isFuncCall = !strcmp($3->LHS, "RETURN");


		// ------ SEMANTIC CHECKS ------ //
		if (!inSymTab) {

			printf("\nSEMANTIC ERROR: Var %s is NOT in the symbol table\n", $1);
			semanticCheckPassed = 0;

		} 		

		char *type1 = getVariableType($1, currentScope);


		// Check if types are equal
		if (strcmp(getVariableType($1, currentScope), $3->nodeType)) {

			printf("ERROR: TYPE MISMATCH ---> Attempting to assign %s to %s\n", $3->nodeType, type1);
			semanticCheckPassed = 0;

		} 

		// ------- SYMBOL TABLE ------- //
		if (semanticCheckPassed) {
			setItemValue($1, $3->RHS, currentScope);
		}
		

		// ------ AST ------ //
		$$ = AST_assignment("=", $1, $3->RHS);


		// ------ CODE GENERATION ------ //

		if (semanticCheckPassed) {

			char *test = getVariableType($1, currentScope);


				// ---- CHAR CODE ---- // 
			if (!strcmp(test, "char")) {

				// ---- IR CODE ---- // 
				emitIRCharDecl($1, $3->RHS);

				if(isNullValue) { //if val isn't null
					setCharVar($1, $3->RHS);
				} else {
					emitMIPSCharDecl($1, $3->RHS);
				}

			}

				// ---- INT CODE ---- // 
			else if (!strcmp(test, "int")) {

				// ---- IR CODE ---- //

				emitIntVarIR($1, atoi($3->RHS));


				// ---- MIPS CODE ---- //
				if(!isNullValue) { //if val isn't null

					if (inFunction && hasMath) {
						// printf("Setting new var for int\n");
						setIntVar($1, "$s1");
					} 					

					else if (isFuncCall) {
						setIntVar($1, "$v1");
					}

					else {
						setIntVar($1, $3->RHS);
					}
					
				} else if (inFunction && hasMath) {

					// printf("Setting new var for int\n");
					emitIntVar($1, $3->RHS);
					setIntVar($1, "$s1");

				} else if (isFuncCall) {

					emitIntVar($1, $3->RHS);
					setIntVar($1, "$v1");
				
				} else {

					printf("generating mips var\n");
					emitIntVar($1, $3->RHS);

				}
			}

		}

		semanticCheckPassed = 1;
	}
	
	| ID LBRACKET INTEGER RBRACKET

;

FunCall:
	ID LPAREN ParamList RPAREN {

		printf("\nRECOGNIZED RULE: Function Call ----> %s\n", $1);

		char returnVal[25];
		sprintf(returnVal, "%s", getValue($1, $1));
		$$ = AST_assignment("int", "RETURN", returnVal);
		emitMIPSFuncCall($1);
		emitMIPSGetReturn();
		// ---- SEMANTIC CHECKS ---- //
		
	}

;

Primary: 
	ID {
		$$ = AST_assignment("id", "" , $1);
	}

	| DECIMAL {
		// printf("float detected: %f\n", $1);
		char numVal[10];
		sprintf(numVal, "%f", $1);
		$$ = AST_assignment("float", "", numVal);
	}
	
	| INTEGER {
		// printf("int detected\n");
		char numVal[10];
		sprintf(numVal, "%d", $1);
		$$ = AST_assignment("int", "", numVal);
	}

	|  CHARACTER  {

		$$ = AST_assignment("char", "", $1);

	}


;

MathExpr: 
	Trm	
	
	| MathExpr MINUS Trm {
		
		char newVal[5];

		// Evaluate expression
		char opArray[3];
		sprintf(opArray, "%s", $2);

		sprintf(newVal, "%d", computeEquation($1, $3, opArray[0]));

		$$ = AST_assignment("int", "", newVal);
		hasMath = 1;

	}

	| MathExpr PLUS Trm {
			
		char newVal[5];

		// Evaluate expression
		char opArray[3];
		sprintf(opArray, "%s", $2);

		
		sprintf(newVal, "%d", computeEquation($1, $3, opArray[0]));
	
		$$ = AST_assignment("int", "", newVal);
		hasMath = 1;

	}

;

Trm: 
	Factor {
	}	

	| Trm MULTIPLY Factor {
		
		char newVal[5];

		// Evaluate expression
		char opArray[3];
		sprintf(opArray, "%s", $2);


		$$ = AST_assignment("int", "", newVal);
		hasMath = 1;


	}

	| Trm DIVIDE Factor {
		
		char newVal[5];

		// Evaluate expression
		char opArray[3];
		sprintf(opArray, "%s", $2);

		$$ = AST_assignment("int", "", newVal);
		hasMath = 1;


	}
;

Factor:
	ID {

		char val[25];
		strcpy(val, getValue($1, currentScope));
		if (!strcmp(val, "NULL")) {
			printf("ERROR: ID %s is null\n", $1);
			// exit;
		}
		$$ = AST_assignment("id", $1 , val);
	}

	| INTEGER {
		char numVal[10];
		sprintf(numVal, "%d", $1);
		$$ = AST_assignment("int", "", numVal);
	}

	| LPAREN MathExpr RPAREN {
		printf("MathExpr = %s\n", $2->RHS);
		$$ = AST_assignment("int", "", $2->RHS);
	}
;

ParamList:	{}
	| Primary {

		printf("\nRECOGNIZED RULE: Parameter\n");

		char *paramValue;
		if (!strcmp($1->nodeType, "id")) {
			char *idVal = getValue($1->RHS, currentScope);
			paramValue = malloc((int)strlen(idVal)+1);
			strcpy(paramValue, idVal);
			setMIPSParameters($1->RHS, paramCount);
		} 
		else {
			int size = sizeof($1->RHS) / sizeof($1->RHS)[0]; 
			paramValue = (char*)malloc(size*sizeof(char));
			strcpy(paramValue, $1->RHS);
			setMIPSParameters(paramValue, paramCount);
		}
		 
		printf("ParamValue = %s\n", paramValue);

		paramCount++;

	} ParamList {}
;


UnaryOp: MINUS {printf("\nRECOGNIZED RULE: Unary Operation, NEGATIVE VALUE %s\n", $1);}


BinOp: PLUS {}
    | MINUS {}
	| MULTIPLY {}
	| DIVIDE {}

%%

int computeEquation(struct AST* num1, struct AST* num2, char operator) {
	char mipsVal1[10];
	char mipsVal2[10];
	int val1; int val2;	
	val1 = atoi(num1->RHS);
	val2 = atoi(num2->RHS);
	
	if (!strcmp(num1->nodeType, "id")) {
		strcpy(mipsVal1, num1->LHS);
	} else {
		strcpy(mipsVal1, num1->RHS);
	}

	if (!strcmp(num2->nodeType, "id")) {
		strcpy(mipsVal2, num2->LHS);
	} else {
		strcpy(mipsVal2, num2->RHS);
	}
	if (inFunction) {
		emitMIPSEquation(mipsVal1, mipsVal2, operator);
	}

	int newVal;

	switch (operator) {
		case '+':
			newVal = val1 + val2;

			break;
		case '-':
			newVal = val1 - val2;
			break;
		case '*':
			newVal = val1 * val2;
			break;
		case '/':
			newVal = val1 / val2;
			break;
	}


}

void yyerror(const char* s) {
	fprintf(stderr, "Parse error: %s\n", s);
	exit(1);
}

int main(int argc, char**argv)
{


	printf("\n\n##### COMPILER STARTED #####\n\n");

	// Initialize IR File
	initIRcodeFile();
	// Initialize MIPS.h
	initAssemblyFile();
	
	if (argc > 1){
	  if(!(yyin = fopen(argv[1], "r")))
          {
		perror(argv[1]);
		return(1);
	  }
	}
	yyparse();

	emitEndOfAssemblyCode();

    printf("\nDisplay Symbol Table\n");
    showSymTable();

    // printf("\nDisplay AST Tree\n\n");
    //printAST(node, 0);

	printf("\nTAC Made\n");

	emitEndOfAssemblyCodeIR();
	printf("\nMIPS Made\n");

	// Merge data and main sections in MIPS
	appendFiles();

	printf("\n--END==\n");


}