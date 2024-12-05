//Even Kliewer, Asher Shores, Riley Monwai
// CST-405: Compilers
// Professor Isac Artzi

%{
//Standard libs
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//Other Files 
#include "symbolTable.h"
#include "AST.h"
#include "IRcode.h"
#include "MIPScode.h"

//Bison stuff I assume... IDK what it does
extern int yylex();
extern int yyparse();
extern FILE* yyin;

//Some global variables
int computeEquation(struct AST* num1, struct AST* num2, char operator);
int evalCondition(struct AST* x, struct AST* y, char logOp[5]);
void yyerror(const char* s);
char currentScope[50] = "GLOBAL"; // global or the name of the function
char currReturnType[10];
int semanticCheckPassed = 1; // flags to record correctness of semantic checks
int goToElse = 0;	// is the condition of if() true?
int maxParam = 0; 	//max of 3 paramaters
int paramCount = 0;
int ifCount = 0;
int whileCount = 0;
int onWhile = 0;
int inFunction = 0;
int hasMath = 0;
char mathVal1[10]; char mathVal2[10];
char conditionString[50];
// char typeTemp[50];

int stringCount = 0;
// count strings for   p r i n t i n g !


%}

%union {
	//Tokens declared in C so we can declare them in C--... I think
	int number;
	float floatValue;
	char character;
	char* string;
	struct AST* ast;
}

//Tokes declared in Parser so we can look for them
//%token <string> TYPE

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
%token <string> LOGICOP

%token <string> LBRACKET
%token <string> RBRACKET
%token <string> LPAREN
%token <string> RPAREN
%token <string> LCURLY
%token <string> RCURLY
/* %token <string> APOST */

//TYPES
%token <string> INT
%token <string> CHAR
%token <string> FLOAT

//Keywords??
%token <string> RETURN
%token <string> WRITELN

%token <string> CHARACTER

//Math
%left PLUS //why do we have %token and %left Math Ops?
%left MINUS
%left TIMES
%left DIVIDE

//Idk what this does
%printer { fprintf(yyoutput, "%s", $$); } ID;
%printer { fprintf(yyoutput, "%d", $$); } INTEGER;

//All the program grammar that will come up
//This doesn't seem actually necessary
%type <ast> Program DeclList Decl VarDeclList FunDeclList VarDecl FunDecl FunCall ParamDecList Block ParamDecListTail ParamDecl Type Stmt StmtList IfStmt WhileLoop Condition Else ArrayExpr Expr MathExpr Trm Factor ParamList Primary UnaryOp BinOp 

%start Program

%%

//Head of program
//Everything must tie back here
Program: 
	DeclList {
		$$ = $1;
		// printAST($$, 3);
	}
;//Program --> DeclList

DeclList:	
	Decl DeclList { 
		// printf("\nTest debug DECLDECLLIST\n");
		$1->right = $2;
		$$ = $1;
		// printf("LINK DECLLIST\n");
		// printNode($$->right);
	} 
	| Decl {
		$$ = $1;
		// printf("DECL\n");
	}
	
	| FunDeclList
;//DeclList --> Decl

Decl: 		
	VarDecl {}

	| StmtList {
	}
;//Decl --> VarDecl & StmtList

VarDeclList: /* EPSILON */ { /*printf("\nNo VarDeclList (EPSILON)\n");*/}

	|	VarDecl VarDeclList	{
		$1->right = $2;
		$$ = $1;
	}

	| VarDecl 
;
//This is unreachable-->Big Pogs

VarDecl: 
	Type ID SEMICOLON {

		printf(BCYAN "\nRECOGNIZED RULE: VARIABLE declaration %s\n" RESET, $2);


		// ----- SYMBOL TABLE ----- //
		symTabAccess();
		int inSymTab = found($2, currentScope);
		//printf("looking for %s in symtab - found: %d \n", $2, inSymTab);
		

		// ------ SEMANTIC CHECKS ------ //
		if (inSymTab == 0)  {
			addItem($2, "VAR", $1->nodeType, currentScope);
			showSymTable();
		}
		else {
			printf("SEMANTIC ERROR: Var %s is already in the symbol table\n", $2);
			semanticCheckPassed = 0;
		}


		// ------  AST  ------ //
		if (semanticCheckPassed) {

			$$ = AST_Type("TYPE", $1->nodeType, $2);


			// ---- CODE GENERATION ---- //
			// code generation occurs when variable 
			// recieves a value to save space
			
		}

		semanticCheckPassed = 1;
	}
	

	// ------ ARRAY DECL ------ //
	| Type ID LBRACKET INTEGER RBRACKET SEMICOLON {
		
		printf("\nRECOGNIZED RULE: ARRAY declaration %s\n\n", $2);

		// ----- SYMBOL TABLE ----- //
		symTabAccess();

		int inSymTab = found($2, currentScope);

		if (inSymTab == 0) {
			char arrIndex[12];
			for (int i = 0; i < $4; i++) {
				sprintf(arrIndex, "%s[%d]", $2, i);
				addItem(arrIndex, "ARRAY", $1->nodeType, currentScope);				
			}

			showSymTable();
		} else {
			printf("SEMANTIC ERROR: Var %s is already in the symbol table\n", $2);
		}


		// ----- AST ----- //
		char intVal[50]; 
		sprintf(intVal, "%d", $4);
		$$ = AST_assignment("ARR", intVal, $2);


		// ----- CODE GENERATION ----- //
		
		// ---- IR CODE ---- //
		// emitArrayDecl($2, $4);


		// ---- MIPS CODE ---- //
		emitMIPSArrayDecl($2, $4);

		semanticCheckPassed = 1;
	} 
	// | ArrDecl
;

//==========================================

//FunDeclList --> FunDecl 
//                FunDecl FunDeclList
FunDeclList: 
	FunDecl 

	| FunDecl FunDeclList {
		

	}
;

//=========================================

//FunDecl ------> Type id ( ParamDecList ) Block
FunDecl:
	FUNC Type ID LPAREN {

		inFunction = 1;

		printf(BBLUE "\nRECOGNIZED RULE: Function Declaration \"%s\"\n\n" RESET, $3);
		printf("ID = %s\n", $3);
		strcpy(currentScope, $3);
		printf(BORANGE "\n------------------- Scope Change --> ");
		printf("%s", currentScope);
		printf(" -------------------\n" RESET);


		// ----- SYMBOL TABLE ----- //
		symTabAccess();
		int inSymTab = found($3, currentScope);

		// ------ SEMANTIC CHECKS ------ //
 		if (inSymTab == 0) {
			
			addItem($3, "FUNC", $2->nodeType, currentScope);

		} 
		else {
			printf(RED"SEMANTIC ERROR: Function %s is already in the symbol table\n"RESET, $2->nodeType);
			semanticCheckPassed = 0;
		}

		// ---- MIPS CODE ---- //
		if (semanticCheckPassed) {
			emitMIPSFunc($3);
		}

		semanticCheckPassed = 1;

	} 

	ParamDecList RPAREN Block {

		showSymTable(); //updates for function and parameters

		// ----- AST ----- //
		if (semanticCheckPassed) {
			$$ = AST_assignment("FUNC", $2->nodeType, $3);		

			// printNode($$);

			// ---- CODE GENERATION ---- //

			// ---- IR CODE ---- //


		}

		// Leave Function in MIPScode.h
		endOfMIPSFunction($3);
	
		semanticCheckPassed = 1;
		inFunction = 0;
		maxParam = 0;
		paramCount = 0;

	}
;


//==========================================


//ParamDeclList --> epsilon 
//                  ParamDeclListTail
ParamDecList: /* EPSILON */ {printf("No ParamDeclList (EPSILON)\n\n");}

	| ParamDecListTail {
		printf("Parameters Detected--->\n");
		$$ = $1;
	}

;

//==========================================

//ParamDeclListTail --> ParamDecl 
//                      ParamDecl, ParamDeclListTail 
ParamDecListTail: 
	ParamDecl {	

		if (maxParam < 4) {
			maxParam++;
		} else {
			printf(RED "WARNING!! Too many parameters in FunDecl" RESET);
		}
	}

	| ParamDecl ParamDecListTail {
		$1->right = $2; 
		$$ = $1;
	}

;

//==========================================

//ParamDecl ----> Type id
//                Type id[]
ParamDecl: 
	Type ID {

		printf(BCYAN "\nRECOGNIZED RULE: Parameter VARIABLE declaration %s\n\n" RESET, $2);

		//Asher's Semantic Checks
		// ---- Symbol Table ---- //
		// symTabAccess();

		//Var Decl Check
		int inSymTab = found($2, currentScope);
		//printf("looking for %s in symtab - found: %d \n", $2, inSymTab);

		if (inSymTab == 0) {
			addItem($2, "PARAM", $1->nodeType, currentScope);
			showSymTable();
		} 
		else {
			printf("\nSEMANTIC ERROR: Var %s is already in the symbol table\n", $2);
		} 

		emitMIPSParameters($2, paramCount);
		paramCount++;

	}

	/* | Type ID LBRACKET RBRACKET {
		printf("\n RECOGNIZED RULE: Parameter ARRAY declaration %s\n", $2);
		//Asher's Semantic Checks
		//Symbol Table	
		symTabAccess();
		int inSymTab = found($2, currentScope);
		//printf("looking for %s in symtab - found: %d \n", $2, inSymTab);
		if (inSymTab == 0) {
			addItem($2, "ARRAY", $1, $4, currentScope);
		} else {
			printf("\nSEMANTIC ERROR: ARR %s is already in the symbol table\n", $2);
		} 
		showSymTable();
	} */
;

//==========================================

//Block --------> { VarDeclList StmtList } 
Block: 
	LCURLY DeclList RCURLY {
		$$ = $2;
		// printf("right: %s\n", $$->right->RHS);
	}
;

//==========================================

Type: INT {}
	| FLOAT {}
	| CHAR {}

//==========================================

StmtList: 
	Stmt 

	| Stmt StmtList {
		$1->right = $2;
		$$ = $1;
		// printNode($$);
	}
;

//==========================================

Stmt: 
	SEMICOLON {
		printf("\nRECOGNIZED RULE: SEMICOLON %s\n", $1);	
	} 

	| WhileLoop {}

	| IfStmt {}

	| Expr SEMICOLON {
		hasMath = 0;
		$$ = $1;
	}

	| RETURN Expr SEMICOLON {		

		printf("RETURN Statement Recognized!\n");


		// ----- AST ----- //
		$$ = AST_assignment("RETURN", "", $2->RHS);

		char *returnType = $2->nodeType;
		// printf("value test = %d\n", atoi($2->RHS));
		// printf("Return type: %s\n", returnType);

		// ---- SYMBOL TABLE ---- //
	
		char val[25];
		if (!strcmp(returnType, "id")) {
			strcpy(val, getValue($2->RHS, currentScope));
		} else {
			strcpy(val, $2->RHS);
		}
		setItemValue(currentScope, val, currentScope);

		// ---- CODE GENERATION ---- //
		

		// ---- IR CODE ---- //


		// ---- MIPS CODE ---- //
		// if (hasMath) {
		// 	emitMIPSReturn("$s1", returnType);
		// } 
		if (strcmp(currentScope, "main")) {
			emitMIPSReturn($2->RHS, returnType);
		}

		hasMath = 0;

	}


	| WRITE Expr SEMICOLON {
		printf("\nRECOGNIZED RULE: Write Statement\n");


		// ---- AST ---- //
		$$ = AST_Write("WRITE", "", $2->RHS);


		// ---- CODE GENERATION ---- //

		// ------ IR CODE ------ //
		emitIRWriteId($2->RHS, getVariableType($2->RHS, currentScope));
		// ------ ¯\_(ツ)_/¯ ------ //

			// ---- MIPS CODE ---- //
		
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

IfStmt:	
	IF LPAREN Condition RPAREN Block {

		//skip mips else if condidtion is true
		emitMIPSEndOfIfBlock(ifCount);

		emitMIPSElseStmt(ifCount);
		

	} Else {

		printf(BPINK "IF STATEMENT RECOGNIZED ---->\n" RESET);
		$$ = AST_assignment("IF", "COND", "BLOCK");
		$$->left = $3;
		$$->right = $5;

		// ---- May go back to this implementation....
		// ---- using MIPS atm ---->
		// if (!goToElse) {			
		// 	onElse = 0;
		// }

		// else {
		// 	onElse = 1;
		// 	printf("GoTo Else statment----->\n");
		// }	

		emitMIPSPassElse(ifCount);

		ifCount++;

		semanticCheckPassed = 1;

	}

;

Else: 
	// EPSILON
	{printf("NO ELSE STATEMENT\n\n");}
	
	| ELSE  Block {
		// DO STUFF
		// printf("else{%s}", code);
		//big brain time
		// emitMIPSPassElse(ifCount);
	}

;

WhileLoop: 
	WHILE LPAREN {

		printf("WHILE LOOP FOUND\n");

		onWhile = 1;

		emitMIPSWhile(whileCount); //all this does is change the 'inLoop' value to true

	} Condition RPAREN Block {

		
		// ----- CODE GENERATION ----- //

		// ---- MIPS CODE ---- //
		// printNode($);
		char type1[8]; char type2[8];
		char val1[10]; char val2[10];
		strcpy(type1, $4->left->nodeType); 
		strcpy(type2, $4->right->nodeType); 
		strcpy(val1, $4->LHS);
		strcpy(val2, $4->RHS);
		
		emitMIPSEndWhile(val1, val2, type1, type2, whileCount);
		// printf("condString = %s\n", condString);

		printf(BGREEN"Emmiting end of while loop!\n"RESET);
		
	}

;

Condition:
	Primary LOGICOP Primary {

		// ----- SEMANTIC CHECKS ----- //

		symTabAccess();

		int inSymTab = found($1, currentScope);
		int inSymTab2 = found($3, currentScope);

		if (inSymTab != 0 && inSymTab2 != 0) {
			printf(RED"\nSEMANTIC ERROR: ARR %s is NOT in the symbol table\n"RESET, $2);
			semanticCheckPassed = 0;
		} else {
			printf("\nSEMANTIC CHECK PASSED\n");
			
			//emitArrayAssignment();
		}

		// get item types
		char type1[8]; char type2[8];
		char val1[10]; char val2[10];
		//if both primaries are id's ---->
		if (!strcmp($1->nodeType, "id") && !strcmp($3->nodeType, "id")) {
			strcpy(type1, getVariableType($1->RHS, currentScope));
			strcpy(type2, getVariableType($3->RHS, currentScope));
			strcpy(val1, getValue($1->RHS, currentScope));
			strcpy(val2, getValue($3->RHS, currentScope));
		} 
		// if first primary is an id ---->
		else if (!strcmp($1->nodeType, "id")) {
			strcpy(type1, getVariableType($1->RHS, currentScope));
			strcpy(type2, $3->nodeType);
			strcpy(val1, getValue($1->RHS, currentScope));
		}
		// if second primary is an id ---->
		else if (!strcmp($3->nodeType, "id")) {
			strcpy(type1, $1->nodeType);
			strcpy(type2, getVariableType($3->RHS, currentScope));
			strcpy(val2, getValue($3->RHS, currentScope));
		} 


		//check if types match
		if (!strcmp(type1, type2)) {

			printf("TYPES ARE COMPATIBLE\n");

		} else {

			printf(RED"ERROR TYPE MISMATCH: Attempting to compare %s to %s"RESET, type2, type1);
			// printf("\nTypes are %s", type1);
			// printf("\nTypes are %s", type2);
			printf("\n");
			semanticCheckPassed = 0;
		}

		// ---- AST ---- //
		$$ = AST_assignment($2, $1->RHS, $3->RHS);
		$$->left = $1->nodeType;
		$$->right = $3->nodeType;

		// may not need this if MIPS stuff works :) 
		// also... Riley wants to smash his computer screen
		// (Riley 2 weeks later) - MIPS works but we still need this
		// and my computer is disfunctional now *smile*.
		int cond = evalCondition($1, $3, $2);

		printf("%s %s %s is ", $1->RHS, $2, $3->RHS);

		if (cond) {
			printf(BGREEN"TRUE\n"RESET);
			goToElse = 0;
		}
		 else {
			printf(RED"FALSE\n"RESET);
			goToElse = 1;
		}

		// ---- CODE GEN ---- //

		if (semanticCheckPassed) {
			// ---- IR CODE ---- //


			// ---- MIPS CODE ---- //
			// OPTIMIZATION --->MIPS for if conditions will only generate
			// if condition is true or if they are in a function/loop

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

//==========================================

ArrayExpr:

	ID LBRACKET INTEGER RBRACKET EQ Primary {

		printf("\nRECOGNIZED RULE: ARRAY assignment %s\n", $1);

		//Asher's Semantic Checks
		symTabAccess();
		int inSymTab = found($1, currentScope);

		if (inSymTab != 0) {
			printf("\nSEMANTIC ERROR: ARR %s is NOT in the symbol table\n", $2);
			semanticCheckPassed = 0;
		} else {
			printf("\nSEMANTIC CHECK PASSED\n");
			
			//emitArrayAssignment();
		}
		// ------ SYMBOL TABLE ------ //

		// Setting array value in the symbol table
		char arrayStmt[10]; char newVal[10];
		sprintf(arrayStmt, "%s%s%d%s", $1, $2, $3, $4);
		// printf("setVal %s\n", $6);
		// sprintf(newVal, "%d", $6);
		setItemValue(arrayStmt, $6->RHS, currentScope);


		// ----- AST ----- //
		$$ = AST_assignment("=", arrayStmt, newVal);		


		// ---- CODE GENERATION ---- //

			// ---- IR CODE ---- //


			// ---- MIPS CODE ---- //
		//TODO we only have functionality to add to ints at the moment 
		emitMIPSIntArrayAssign($1, $3, atoi($6->RHS));

	}


	| ID EQ ID LBRACKET INTEGER RBRACKET {

		symTabAccess();
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


			// ---- CODE GENERATION ---- //

			// ---- IR CODE ---- //
			//TODO

			// ---- MIPS CODE ---- //
			
		}

	}

;


Expr: 
	Primary 

	| MathExpr

	| ArrayExpr

	| FunCall {paramCount = 0; $$ = $1;}

	| UnaryOp Expr { 

		//Asher's Semantic Checls
		// ------- SYMBOL TABLE ------- //
		symTabAccess();
		int inSymTab = found($2->RHS, currentScope);
		//printf("looking for %s in symtab - found: %d \n", $2, inSymTab);
		if (inSymTab == 0) {
			printf(RED"\nSEMANTIC ERROR: Expr %s is NOT in the symbol table\n" RESET, $2->nodeType);
		}
		showSymTable();

	}

	| ID EQ Expr {
		
		printf("\nRECOGNIZED RULE: Assignment Statement ----> %s\n", $1);
		int inSymTab = found($1, currentScope);

		
		// Variable to tell if value has been assigned yet; 1 is true
		int isNullValue = !strcmp(getValue($1, currentScope), "NULL");
		int isFuncCall = !strcmp($3->LHS, "RETURN");


		// ------ SEMANTIC CHECKS ------ //
		if (!inSymTab) {

			printf(RED"\nSEMANTIC ERROR: Var %s is NOT in the symbol table\n"RESET, $1);
			semanticCheckPassed = 0;

		} 		

		char *type1 = getVariableType($1, currentScope);
		// char *type2 = getVariableType($3->RHS, currentScope);

		// if (!compareTypes($1, $3->RHS, currentScope)) {
		// 	// printf(RED"ERROR TYPE MISMATCH: Attempting to assign %s to %s"RESET, type2, type1);
		// 	semanticCheckPassed = 0; 
		// }


		// Check if types are equal
		if (strcmp(getVariableType($1, currentScope), $3->nodeType)) {

			printf(RED"ERROR: TYPE MISMATCH ---> Attempting to assign %s to %s\n"RESET, $3->nodeType, type1);
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

			// printf("varType = %s\n", test);
 			//¯\_(ツ)_/¯ ¯\_(ツ)_/¯ ¯\_(ツ)_/¯

			// ---- CODE GENERATION ---- //

				// ---- CHAR CODE ---- // 
			if (!strcmp(test, "char")) {

				// ---- IR CODE ---- // 
				emitIRCharDecl($1, $3->RHS);
				
				// ---- MIPS CODE ---- // 
				// if (inFunction) {
				// 	setIntVar($1, "s9");
				// }

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

					printf(BBLUE"generating mips var\n"RESET);
					emitIntVar($1, $3->RHS);

				}
			}

		}

		semanticCheckPassed = 1;
	}

	// | ID PLUS PLUS {

	// 	// ---- SEMANTIC CHECKS ---- //

	// 	char idVal[25];
	// 	strcpy(idVal, getValue($1, currentScope));

	// 	if (!strcmp(idVal, "NULL")) {
	// 		fprintf(RED "ERROR: ID %s is not defined" RESET, $1);
	// 		semanticCheckPassed = 0;
	// 	}

	// 	// ---- CODE GENERATION ---- //

	// 	// ---- MIPS CODE ---- //
	// 	emitMIPSIncrement($1);

	// }
	
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

	/* | LPAREN Expr RPAREN  */

;

MathExpr: 
	Trm	
	
	| MathExpr MINUS Trm {
		
		char newVal[5];

		// Evaluate expression
		char opArray[3];
		sprintf(opArray, "%s", $2);

		// if (inFunction) {
		// 	emitMIPSEquation($1->RHS, $3->RHS, $2);
		// } 

		sprintf(newVal, "%d", computeEquation($1, $3, opArray[0]));
		// sprintf(newVal, "%d", computeEquation(atoi($1->RHS), atoi($3->RHS), opArray[0]));

		// printf("newVal = %s\n", newVal);

		$$ = AST_assignment("int", "", newVal);
		hasMath = 1;

	}

	| MathExpr PLUS Trm {
			
		char newVal[5];

		// Evaluate expression
		char opArray[3];
		sprintf(opArray, "%s", $2);

		// printf("$1 = %s and $3 = %s\n", $1->RHS, $3->RHS);

		// if (inFf
		
		sprintf(newVal, "%d", computeEquation($1, $3, opArray[0]));
		// sprintf(newVal, "%d", computeEquation(atoi($1->RHS), atoi($3->RHS), opArray[0]));
		// printf("newVal = %s\n", newVal);

		$$ = AST_assignment("int", "", newVal);
		hasMath = 1;

	}

;

Trm: 
	Factor {
		// -- THIS IS COMMENTED OUT FOR MIPS PURPOSES, I DON'T REMEMBER WHAT IT DID LOL - Riley
		// ----------------------------------------------------->
		// char numVal[10];
		// if (strcmp($1->nodeType,"id") == 0) {
		// 	// printf("ID Found!\n");
		// 	// sprintf(numVal, "%s", getValue($1->LHS, currentScope));
		// 	// $$ = AST_assignment("=", $1->LHS, numVal);

		// 	// Set item to used 
		// 	//setItemUsed($1->RHS, currentScope);

		// } else {
		// 	//primary is a number, do nothing
		// 	$$ = $1;
		// }
	}	

	| Trm TIMES Factor {
		
		char newVal[5];

		// Evaluate expression
		char opArray[3];
		sprintf(opArray, "%s", $2);

		// sprintf(newVal, "%d", computeEquation(atoi($1->RHS), atoi($3->RHS), opArray[0]));
		// printf("newVal = %s\n", newVal);

		$$ = AST_assignment("int", "", newVal);
		hasMath = 1;


	}

	| Trm DIVIDE Factor {
		
		char newVal[5];

		// Evaluate expression
		char opArray[3];
		sprintf(opArray, "%s", $2);

		// sprintf(newVal, "%d", computeEquation(atoi($1->RHS), atoi($3->RHS), opArray[0]));
		// printf("newVal = %s\n", newVal);

		$$ = AST_assignment("int", "", newVal);
		hasMath = 1;


	}
;

Factor:
	ID {

		// printf("ID detected\n");
		char val[25];
		strcpy(val, getValue($1, currentScope));
		if (!strcmp(val, "NULL")) {
			printf(RED"ERROR: ID %s is null\n"RESET, $1);
			// exit;
		}
		$$ = AST_assignment("id", $1 , val);
	}

	| INTEGER {
		// printf("int detected\n");
		char numVal[10];
		sprintf(numVal, "%d", $1);
		$$ = AST_assignment("int", "", numVal);
	}

	| LPAREN MathExpr RPAREN {
		// printf("Factor test\n");
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
		 
		printf(BCYAN "ParamValue = %s\n" RESET, paramValue);

		//change values of parameters in main
		// char paramName[50];
		// sprintf(paramName, "param%d", paramCount);
		paramCount++;

	} ParamList {}
;


//=================================================================================================



UnaryOp: MINUS {printf("\nRECOGNIZED RULE: Unary Operation, NEGATIVE VALUE %s\n", $1);}


BinOp: PLUS {}
    | MINUS {}
	| TIMES {}
	| DIVIDE {}

%%

int evalCondition(struct AST* x, struct AST* y, char logOp[5]) {

	printf(ORANGE"Evaluating condition---->\n" RESET);

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
/* 
	int test = strcmp(x->RHS, y->RHS);
	printf("val1 = %d | val2 = %d\n", val1, val2);  */

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

	/* char newVal[3]; */
	int newVal;
	/* printf("Equation detected: %d %c %d", val1, operator, val2); */

	switch (operator) {
		case '+':
			newVal = val1 + val2;
			/* sprintf(newVal, "%d", val1 + val2); */
			/* printf("Addtion Expr found!\n"); */
			break;
		case '-':
			newVal = val1 - val2;
			/* sprintf(newVal, "%d", val1 - val2); */
			/* printf("Subtraction Expr found!\n"); */
			break;
		case '*':
			newVal = val1 * val2;
			/* sprintf(newVal, "%d", val1 * val2); */
			/* printf("Multiplication Expr found!\n"); */
			break;
		case '/':
			newVal = val1 / val2;
			/* sprintf(newVal, "%d", val1 / val2); */
			/* printf("Division Expr found!\n"); */
			break;
	}

	/* printf("Newval = %d\n", newVal); */

}

void yyerror(const char* s) {
	fprintf(stderr, "Parse error: %s\n", s);
	exit(1);
}

int main(int argc, char**argv)
{
/* 
	#ifdef YYDEBUG
		yydebug = 1;
	#endif */

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

	printf(PINK"\n##### IR CODE GENERATED #####\n\n"RESET);

	emitEndOfAssemblyCodeIR();
	printf(PINK"\n##### MIPS CODE GENERATED #####\n\n"RESET);

	// Merge data and main sections in MIPS
	appendFiles();

	printf(PINK"\n##### COMPILER ENDED #####\n\n"RESET);


	/* fprintf (GarbageMIPS, "syscall\n"); */
}