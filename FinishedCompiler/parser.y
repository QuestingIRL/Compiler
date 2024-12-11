
%{
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "symboltable.h"
#include "ast.h"
#include "tac.h"
#include "mips.h"

// Forward declarations
extern int yylex();
extern int yyparse();
extern FILE* yyin;

// Function prototypes for additional functionality
int computeEquation(struct AST* num1, struct AST* num2, char operator);
int evalCondition(struct AST* x, struct AST* y, char logOp[5]);
void yyerror(const char* s);

// Global variables for semantic and runtime state
char currentScope[50] = "GLOBAL"; // Tracks current scope ("GLOBAL" or function name)
char currReturnType[10];          // Tracks the expected return type
int semanticCheckPassed = 1;      // Semantic check success flag
int goToElse = 0;                 // Tracks if the if() condition is true
int maxParam = 0;                 // Maximum of 3 parameters
int paramCount = 0;               // Current parameter count
int ifCount = 0;                  // Counter for unique if blocks
int whileCount = 0;               // Counter for unique while loops
int onWhile = 0;                  // Tracks if currently in a while loop
int inFunction = 0;               // Tracks if currently inside a function
int hasMath = 0;                  // Tracks if an expression contains math
char mathVal1[10];                // First operand in math expression
char mathVal2[10];                // Second operand in math expression
char conditionString[50];         // String representation of conditions
int stringCount = 0;              // Counter for unique string literals
%}

/* Union type for tokens and AST nodes */
%union {
    int number;                   // Integer value
    float floatValue;             // Float value
    char character;               // Character value
    char* string;                 // String value
    struct AST* ast;              // AST node
}

/* Token declarations with their associated types */
%token <string> ID
%token <number> INTEGER
%token <floatValue> DECIMAL
%token <string> STRING

%token <string> SEMICOLON
%token <string> EQ
%token <string> WRITE
%token <string> SWRITE
%token <string> FUNC
%token <string> IF
%token <string> ELSE
%token <string> WHILE
%token <string> PLUS
%token <string> MINUS
%token <string> TIMES
%token <string> DIVIDE
%token <string> LOGIC
%token <string> LBRACKET
%token <string> RBRACKET
%token <string> LPAREN
%token <string> RPAREN
%token <string> LBRACE
%token <string> RBRACE
%token <string> INT
%token <string> CHAR
%token <string> FLOAT
%token <string> RETURN
%token <string> WRITELN
%token <string> CHARACTER

/* Operator precedence and associativity */
%left PLUS 
%left MINUS
%left MULTIPLY
%left DIVIDE

/* Custom printing rules for specific types */
%printer { fprintf(yyoutput, "%s", $$); } ID
%printer { fprintf(yyoutput, "%d", $$); } INTEGER

/* Non-terminal type declarations */
%type <ast> Program DeclList Decl VarDeclList FunDeclList VarDecl FunDecl FunCall ParamDecList Block ParamDecListTail ParamDecl Type Stmt StmtList IfStmt WhileLoop Condition Else ArrayExpr Expr MathExpr Trm Factor ParamList Primary UnaryOp BinOp 

/* Entry point of the parser */
%start Program

%%
Program: 
    DeclList {
        $$ = $1;
    }
;

/* A list of declarations: can be a variable, statement, or a function declaration */
DeclList: 
    Decl DeclList { 
        $1->right = $2; // Link the current declaration to the list
        $$ = $1;        // Return the updated list
    } 
    | Decl {
        $$ = $1;        // A single declaration
    }
    | FunDeclList {      // Function declarations are also part of declarations
        $$ = $1;
    }
;

/* Declaration can be a variable declaration or a list of statements */
Decl: 
    VarDecl {}
    | StmtList {}
;

/* A list of variable declarations */
VarDeclList: 
    {}
    | VarDecl VarDeclList {
        $1->right = $2; // Link the current variable declaration to the list
        $$ = $1;        // Return the updated list
    }
    | VarDecl {
        $$ = $1;        // A single variable declaration
    }
;

/* Variable declaration: Handles both simple and array declarations */
VarDecl: 
    Type ID SEMICOLON {
        printf("\nRECOGNIZED RULE: VARIABLE declaration %s\n", $2);

        // Check for duplicate variable declaration
        int inSymTab = found($2, currentScope);
        if (inSymTab == 0) {
            addItem($2, "VAR", $1->nodeType, currentScope);
        } else {
            printf("SEMANTIC ERROR: Var %s is already in the symbol table\n", $2);
            semanticCheckPassed = 0;
        }

        // Generate AST node if semantic checks pass
        if (semanticCheckPassed) {
            $$ = AST_Type("TYPE", $1->nodeType, $2);
        }
        semanticCheckPassed = 1; // Reset the flag
    }
    | Type ID LBRACKET INTEGER RBRACKET SEMICOLON {
        printf("\nRECOGNIZED RULE: ARRAY declaration %s\n\n", $2);

        // Check for duplicate array declaration
        int inSymTab = found($2, currentScope);
        if (inSymTab == 0) {
            char arrIndex[12];
            for (int i = 0; i < $4; i++) {
                sprintf(arrIndex, "%s[%d]", $2, i);
                addItem(arrIndex, "ARRAY", $1->nodeType, currentScope);
            }
        } else {
            printf("SEMANTIC ERROR: Var %s is already in the symbol table\n", $2);
        }

        // Create AST node and emit MIPS code for the array
        char intVal[50]; 
        sprintf(intVal, "%d", $4);
        $$ = AST_assignment("ARR", intVal, $2);
        emitMIPSArrayDecl($2, $4);

        semanticCheckPassed = 1; // Reset the flag
    }
;

/* List of function declarations */
FunDeclList: 
    FunDecl {
        $$ = $1;
    }
    | FunDecl FunDeclList {
        $1->right = $2; // Link the current function to the list
        $$ = $1;
    }
;

/* Function declaration with parameters and a body */
FunDecl:
    FUNC Type ID LPAREN {
        inFunction = 1; // Enter function scope

        printf("\nRECOGNIZED RULE: Function Declaration \"%s\"\n\n", $3);
        printf("ID = %s\n", $3);
        strcpy(currentScope, $3); // Change scope to function name
        printf("\n------------------- Scope Change --> %s -------------------\n", currentScope);

        // Check for duplicate function declaration
        int inSymTab = found($3, currentScope);
        if (inSymTab == 0) {
            addItem($3, "FUNC", $2->nodeType, currentScope);
        } else {
            printf("SEMANTIC ERROR: Function %s is already in the symbol table\n", $2->nodeType);
            semanticCheckPassed = 0;
        }

        // Emit MIPS code for the function start
        if (semanticCheckPassed) {
            emitMIPSFunc($3);
        }
        semanticCheckPassed = 1; // Reset the flag
    } 
    ParamDecList RPAREN Block {
        // Generate AST for the function and handle its body
        if (semanticCheckPassed) {
            $$ = AST_assignment("FUNC", $2->nodeType, $3);
        }

        // Emit MIPS code to end the function
        endOfMIPSFunction($3);

        // Reset function-specific flags and counters
        semanticCheckPassed = 1;
        inFunction = 0;
        maxParam = 0;
        paramCount = 0;
    }
;

/* Parameter declaration list: can be empty or contain a list of parameters */
ParamDecList: 
    {
        printf("No ParamDeclList (EPSILON)\n\n");
    }
    | ParamDecListTail {
        printf("Parameters Detected--->\n");
        $$ = $1; // Pass the parameter list
    }
;

/* Tail of the parameter declaration list */
ParamDecListTail: 
    ParamDecl {
        if (maxParam < 4) { // Check parameter limit
            maxParam++;
        } else {
            printf("Too many parameters in FunDecl\n");
        }
    }
    | ParamDecl ParamDecListTail {
        $1->right = $2; // Link the current parameter to the list
        $$ = $1;
    }
;

/* Parameter declaration: type and identifier */
ParamDecl: 
    Type ID {
        printf("\nRECOGNIZED RULE: Parameter VARIABLE declaration %s\n\n", $2);

        // Check for duplicate parameter
        int inSymTab = found($2, currentScope);
        if (inSymTab == 0) {
            addItem($2, "PARAM", $1->nodeType, currentScope);
        } else {
            printf("\nSEMANTIC ERROR: Var %s is already in the symbol table\n", $2);
        }

        emitMIPSParameters($2, paramCount); // Emit MIPS code for the parameter
        paramCount++;
    }
;

/* Block: enclosed by curly braces */
Block: 
    LBRACE DeclList RBRACE {
        $$ = $2; // Pass the declarations inside the block
    }
;

/* Type specifiers */
Type: 
    INT {}
    | FLOAT {}
    | CHAR {}
;

/* Statement list: a sequence of statements */
StmtList: 
    Stmt {
        $$ = $1; // Single statement
    }
    | Stmt StmtList {
        $1->right = $2; // Link the current statement to the list
        $$ = $1;
    }
;

/* Statement definitions */
Stmt: 
    SEMICOLON {
        printf("\nRECOGNIZED RULE: SEMICOLON %s\n", $1);
    }
    | WhileLoop {}
    | IfStmt {}
    | Expr SEMICOLON {
        hasMath = 0; // Reset math flag after expression
        $$ = $1;
    }
    | RETURN Expr SEMICOLON {
        printf("RETURN Statement Recognized!\n");

        $$ = AST_assignment("RETURN", "", $2->RHS);

        char* returnType = $2->nodeType;
        char val[25];

        if (!strcmp(returnType, "id")) {
            strcpy(val, getValue($2->RHS, currentScope));
        } else {
            strcpy(val, $2->RHS);
        }

        setItemValue(currentScope, val, currentScope);

        if (strcmp(currentScope, "main")) {
            emitMIPSReturn($2->RHS, returnType); // Emit MIPS return statement
        }

        hasMath = 0; // Reset math flag
    }
    | WRITE Expr SEMICOLON {
        printf("\nRECOGNIZED RULE: Write Statement\n");

        $$ = AST_Write("WRITE", "", $2->RHS);

        emitIRWriteId($2->RHS, getVariableType($2->RHS, currentScope));

        if (!strcmp($2->nodeType, "id")) {
            emitMIPSWriteId($2->RHS, getVariableType($2->RHS, currentScope));
        } else if (!strcmp($2->nodeType, "int")) {
            emitMIPSWriteInt(atoi($2->RHS));
        } else if (!strcmp($2->nodeType, "char")) {
            emitMIPSWriteId($2->RHS, getVariableType($2->RHS, currentScope));
        }
    }
    | WRITELN SEMICOLON {
        printf("\nRECOGNIZED RULE: Write Line %s\n", $1);

        $$ = AST_assignment("WRITELN", "", "");
        emitMIPSNewLine(); // Emit newline in MIPS
    }
    | SWRITE STRING SEMICOLON {
        printf("\nRECOGNIZED RULE: Write String %s\n", $2);

        emitMIPSString($2, stringCount); // Emit string in MIPS
        stringCount++; // Increment string count
    }
;

IfStmt:	
	IF LPAREN Condition RPAREN Block {

		emitMIPSEndOfIfBlock(ifCount);

		emitMIPSElseStmt(ifCount);
		

	} Else {

		printf("IF STATEMENT RECOGNIZED ---->\n");
		$$ = AST_assignment("IF", "COND", "BLOCK");
		$$->left = $3;
		$$->right = $5;

		emitMIPSPassElse(ifCount);

		ifCount++;

		semanticCheckPassed = 1;

	}

;

Else: 
	{printf("NO ELSE STATEMENT\n\n");}
	
	| ELSE  Block {
		
	}

;

WhileLoop: 
	WHILE LPAREN {

		printf("WHILE LOOP FOUND\n");

		onWhile = 1;

		emitMIPSWhile(whileCount); 

	} Condition RPAREN Block {

		char type1[8]; char type2[8];
		char val1[10]; char val2[10];
		strcpy(type1, $4->left->nodeType); 
		strcpy(type2, $4->right->nodeType); 
		strcpy(val1, $4->LHS);
		strcpy(val2, $4->RHS);
		
		emitMIPSEndWhile(val1, val2, type1, type2, whileCount);

		printf("Emmiting end of while loop!\n");
		
	}

;

Condition:
	Primary LOGIC Primary {

		int inSymTab = found($1, currentScope);
		int inSymTab2 = found($3, currentScope);

		if (inSymTab != 0 && inSymTab2 != 0) {
			printf("\nSEMANTIC ERROR: ARR %s is NOT in the symbol table\n", $2);
			semanticCheckPassed = 0;
		} else {
			printf("\nSEMANTIC CHECK PASSED\n");
			
		}

		char type1[8]; char type2[8];
		char val1[10]; char val2[10];
		if (!strcmp($1->nodeType, "id") && !strcmp($3->nodeType, "id")) {
			strcpy(type1, getVariableType($1->RHS, currentScope));
			strcpy(type2, getVariableType($3->RHS, currentScope));
			strcpy(val1, getValue($1->RHS, currentScope));
			strcpy(val2, getValue($3->RHS, currentScope));
		} 
		else if (!strcmp($1->nodeType, "id")) {
			strcpy(type1, getVariableType($1->RHS, currentScope));
			strcpy(type2, $3->nodeType);
			strcpy(val1, getValue($1->RHS, currentScope));
		}
		else if (!strcmp($3->nodeType, "id")) {
			strcpy(type1, $1->nodeType);
			strcpy(type2, getVariableType($3->RHS, currentScope));
			strcpy(val2, getValue($3->RHS, currentScope));
		} 

		if (!strcmp(type1, type2)) {

			printf("TYPES ARE COMPATIBLE\n");

		} else {

			printf("ERROR TYPE MISMATCH: Attempting to compare %s to %s", type2, type1);
			printf("\n");
			semanticCheckPassed = 0;
		}

		$$ = AST_assignment($2, $1->RHS, $3->RHS);
		$$->left = $1->nodeType;
		$$->right = $3->nodeType;

		int cond = evalCondition($1, $3, $2);

		printf("%s %s %s is ", $1->RHS, $2, $3->RHS);

		if (cond) {
			printf("TRUE\n");
			goToElse = 0;
		}
		 else {
			printf("FALSE\n");
			goToElse = 1;
		}

		if (semanticCheckPassed) {

			if (onWhile || inFunction) {
				loadMIPSVarCond($1->RHS, $3->RHS, $1->nodeType, $3->nodeType);
				emitMIPSCond(val1, val2, $2, ifCount);	
				onWhile = 0;
			} 
			
			else if(!cond) {
				loadMIPSVarCond($1->RHS, $3->RHS, $1->nodeType, $3->nodeType);
				emitMIPSCond(val1, val2, $2, ifCount);
			}
		} 

		semanticCheckPassed = 1;

	}

;




ArrayExpr:

	ID LBRACKET INTEGER RBRACKET EQ Primary {

		printf("\nRECOGNIZED RULE: ARRAY assignment %s\n", $1);

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

		int inSymTab = found($1, currentScope);

		if (inSymTab) {

			char arrayStmt[10]; char newVal[10];
			sprintf(arrayStmt, "%s%s%d%s", $3, $4, $5, $6);

			int arrayVal = atoi(getValue(arrayStmt, currentScope));
			sprintf(newVal, "%d", arrayVal);


			setItemValue($1, newVal, currentScope);
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

		int inSymTab = found($2->RHS, currentScope);
		if (inSymTab == 0) {
			printf("\nSEMANTIC ERROR: Expr %s is NOT in the symbol table\n", $2->nodeType);
		}

	}

	| ID EQ Expr {
		
		printf("\nRECOGNIZED RULE: Assignment Statement ----> %s\n", $1);
		int inSymTab = found($1, currentScope);

		
		int isNullValue = !strcmp(getValue($1, currentScope), "NULL");
		int isFuncCall = !strcmp($3->LHS, "RETURN");


		if (!inSymTab) {

			printf("\nSEMANTIC ERROR: Var %s is NOT in the symbol table\n", $1);
			semanticCheckPassed = 0;
		} 		

		char *type1 = getVariableType($1, currentScope);
		if (strcmp(getVariableType($1, currentScope), $3->nodeType)) {

			printf("ERROR: TYPE MISMATCH ---> Attempting to assign %s to %s\n", $3->nodeType, type1);
			semanticCheckPassed = 0;

		} 
		if (semanticCheckPassed) {
			setItemValue($1, $3->RHS, currentScope);
		}
		

		$$ = AST_assignment("=", $1, $3->RHS);

		if (semanticCheckPassed) {

			char *test = getVariableType($1, currentScope);

			if (!strcmp(test, "char")) {

				emitIRCharDecl($1, $3->RHS);

				if(isNullValue) { 
					setCharVar($1, $3->RHS);
				} else {
					emitMIPSCharDecl($1, $3->RHS);
				}

			}
			else if (!strcmp(test, "int")) {


				emitIntVarIR($1, atoi($3->RHS));

				if(!isNullValue) { 

					if (inFunction && hasMath) {
						setIntVar($1, "$s1");
					} 					

					else if (isFuncCall) {
						setIntVar($1, "$v1");
					}

					else {
						setIntVar($1, $3->RHS);
					}
					
				} else if (inFunction && hasMath) {

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

	
;

FunCall:
	ID LPAREN ParamList RPAREN {

		printf("\nRECOGNIZED RULE: Function Call ----> %s\n", $1);

		char returnVal[25];
		sprintf(returnVal, "%s", getValue($1, $1));
		$$ = AST_assignment("int", "RETURN", returnVal);
		emitMIPSFuncCall($1);
		emitMIPSGetReturn();
		
	}

;


Primary: 
	ID {
		$$ = AST_assignment("id", "" , $1);
	}

	| DECIMAL {
		char numVal[10];
		sprintf(numVal, "%f", $1);
		$$ = AST_assignment("float", "", numVal);
	}
	
	| INTEGER {
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

		char opArray[3];
		sprintf(opArray, "%s", $2);


		sprintf(newVal, "%d", computeEquation($1, $3, opArray[0]));

		$$ = AST_assignment("int", "", newVal);
		hasMath = 1;

	}

	| MathExpr PLUS Trm {
			
		char newVal[5];

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

		char opArray[3];

		$$ = AST_assignment("int", "", newVal);
		hasMath = 1;


	}

	| Trm DIVIDE Factor {
		
		char newVal[5];

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

int evalCondition(struct AST* x, struct AST* y, char logOp[5]) {

	printf("Evaluating condition---->\n");

	int val1; int val2;
	if (!strcmp(x->nodeType, "id") && !strcmp(y->nodeType, "id")) {
		val1 = atoi(getValue(x->RHS, currentScope));
		val2 = atoi(getValue(y->RHS, currentScope));
	} 
	else if (!strcmp(x->nodeType, "id")) {
		val1 = atoi(getValue(x->RHS, currentScope));
		val2 = atoi(y->RHS);
	}
	else if (!strcmp(y->nodeType, "id")) {
		val1 = atoi(x->RHS);
		val2 = atoi(getValue(y->RHS, currentScope));
	} 

	if (!strcmp(logOp, "==")) {
		if (!strcmp(x->RHS, y->RHS) || val1 == val2) {
			return 1;
		}
	} 
	else if (!strcmp(logOp, "!=")) {
		if (val1 != val2) {
			return 1;
		}
	}
	else if (!strcmp(logOp, "<=")) {
		if (val1 <= val2) {
			return 1;
		}
	}
	else if (!strcmp(logOp, ">=")) {
		if (val1 >= val2) {
			return 1;
		}
	}
	else if (!strcmp(logOp, "<")) {
		if (val1 < val2) {
			return 1;
		}
	}
	else if (!strcmp(logOp, ">")) {
		if (val1 > val2) {
			return 1;
		}
	}

	return 0;
}

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

// Main function to initiate the compilation process
int main(int argc, char** argv) {
    printf("\n\nStart of Compiler\n\n");

    // Initialize Intermediate Representation (IR) and Assembly files
    initIRcodeFile();
    initAssemblyFile();

    // Check for input file and open it for parsing
    if (argc > 1) {
        if (!(yyin = fopen(argv[1], "r"))) {
            perror(argv[1]); // Print error if file cannot be opened
            return 1;
        }
    }

    // Start parsing
    yyparse();

    // Emit the end of the assembly code
    emitEndOfAssemblyCode();

    // Display the Symbol Table
    printf("\n\nSymbol Table\n\n");
    showSymTable();

    // Emit the end of the IR code
    printf("\nTAC Made\n");
    emitEndOfAssemblyCodeIR();

    // Signal that the MIPS code has been generated
    printf("\nMIPS Made\n");

    // Append files to generate the final assembly output
    appendFiles();

    // Indicate the end of the compilation process
    printf("\nEnd of Compiler\n");

    return 0; // Exit the program
}
