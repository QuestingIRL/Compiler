#include <stdio.h>
#include <ctype.h>

#ifndef SYMBOLTABLE_H

#endif // !SYMBOLTABLE_H

// Set of functions to emit MIPS code
FILE * mainMIPS;
FILE * dataMIPS;
FILE * funcs;
FILE * loops;

int inFunc = 0;
int inLoop = 0;

char paramArray [4][50];
char condString[32];

void emitMIPSString(char myString[50], int stringCount) {

    mainMIPS = fopen("MIPScode.asm", "a");
    if (inFunc == 1) {
        mainMIPS = fopen("funcs.asm", "a");
    }

    dataMIPS = fopen("dataMIPS.asm", "a");

    fprintf(dataMIPS, "msg%d: .asciiz %s\n", stringCount, myString);

    fclose(dataMIPS);

    // mainMIPS = fopen("MIPScode.asm", "a");

    
    /*
    li	$v0, 4		# code for print_str
	la	$a0, msg	# point to string
	syscall
    */
    fprintf(mainMIPS, "li $v0, 4\n");
    fprintf(mainMIPS, "la $a0, msg%d\n", stringCount);
    fprintf(mainMIPS, "syscall\n");
    fclose(mainMIPS);
}

void  initAssemblyFile(){
    // Creates a MIPS file with a generic header that needs to be in every file

    mainMIPS = fopen("MIPScode.asm", "w");
    dataMIPS = fopen("dataMIPS.asm", "w");
    funcs = fopen("funcs.asm", "w");
    
    fprintf(mainMIPS, ".text\n");
    // fprintf(mainMIPS, "main:\n");
    fprintf(mainMIPS, "# -----------------------\n");

    // data
    fprintf(dataMIPS, ".data\n");
    fprintf(dataMIPS, "newLine: .asciiz \"\\n\"\n");

    fclose(mainMIPS);
    fclose(dataMIPS);
    fclose(funcs);

}

void emitMIPSAssignment(char id1[10], char id2[10]){

    mainMIPS = fopen("MIPScode.asm", "a");
    if (inFunc == 1) {
        mainMIPS = fopen("funcs.asm", "a");
    }

    fprintf(mainMIPS, " ,%s\n", id1);

    fclose(mainMIPS);
}

void emitMIPSConstantIntAssignment (int id1, char id2[50]){

    mainMIPS = fopen("MIPScode.asm", "a");
    if (inFunc == 1) {
        mainMIPS = fopen("funcs.asm", "a");
    }
    
  
    fprintf(mainMIPS, "li $t%d,%s\n", id1, id2);

    fclose(mainMIPS);
}

void emitMIPSNewLine () {

    mainMIPS = fopen("MIPScode.asm", "a");
    if (inFunc == 1) {
        mainMIPS = fopen("funcs.asm", "a");
    }
    fprintf(mainMIPS, "# PRINTING NEW LINE ---->\n");
    fprintf(mainMIPS, "li $v0, 4\n");
    fprintf(mainMIPS, "la $a0, newLine\n");
    fprintf(mainMIPS, "syscall\n");

    fclose(mainMIPS);

}

void emitMIPSWriteInt(int n){

    mainMIPS = fopen("MIPScode.asm", "a");
    if (inFunc == 1) {
        mainMIPS = fopen("funcs.asm", "a");
    }

    // This is what needs to be printed, but must manage registers
    // $a0 is the register through which everything is printed in MIPS
    
    //fprintf(mainMIPS, "li $a0,%s\n", id);
    fprintf(mainMIPS, "# Printing -----------\n");
    fprintf(mainMIPS, "li $v0, 1\n");
    fprintf(mainMIPS, "li $a0, %d\n", n);
    fprintf(mainMIPS, "syscall\n");

    fclose(mainMIPS);
}


void emitMIPSWriteId(char id[50], char type[5]){

    mainMIPS = fopen("MIPScode.asm", "a");

    if (inFunc == 1) {
        mainMIPS = fopen("funcs.asm", "a");
    }
    // This is what needs to be printed, but must manage registers
    // $a0 is the register through which everything is printed in MIPS
    
    //fprintf(mainMIPS, "li $a0,%s\n", id);
    fprintf(mainMIPS, "# Printing -----------\n");

    //if id is an int
    if (strcmp(type, "int") == 0) {
        // printf("printing an integer----->\n");
        fprintf(mainMIPS, "li $v0, 1\n");
        fprintf(mainMIPS, "lw $a0, %s\n", id);
    } 

    //if is a character
    else if (strcmp(type, "char") == 0) {
        // printf("printing a char\n");
        fprintf(mainMIPS, "li $v0, 11\n");
        fprintf(mainMIPS, "lb $a0, %s\n", id);
    }

    // if id is a string
    else { 
        fprintf(mainMIPS, "li $v0, 4\n");
        fprintf(mainMIPS, "la $a0, %s\n", id);
    }

    fprintf(mainMIPS, "syscall\n");    

    fclose(mainMIPS);
}


// ----- ARRAYS FOR MIPS ----->
void emitMIPSArrayDecl (char id[50], int size) {

    dataMIPS = fopen("dataMIPS.asm", "a");

    fprintf(dataMIPS, "%s:  .space   %d\n", id, size*4);

    fclose(dataMIPS);
}

void emitMIPSIntArrayAssign (char id[50], int index, int val) {

    mainMIPS = fopen("MIPScode.asm", "a");

    if (inFunc) {
        mainMIPS = fopen("funcs.asm", "a");
    }

    fprintf(mainMIPS, "addi $s0, $zero, %d\n", val); //add value to register
    fprintf(mainMIPS, "addi $t0, $t0, %d\n", index*4);
    fprintf(mainMIPS, "sw   $s0, %s($t0)\n", id);

    fclose(mainMIPS);
}


void emitMIPSCharDecl (char id[50], char c[5]) {

    dataMIPS = fopen("dataMIPS.asm", "a");

    fprintf(dataMIPS, "%s:  .byte   %s\n", id, c);

    fclose(dataMIPS);
}

void setCharVar(char id[50], char c[5]) {

    mainMIPS = fopen("MIPScode.asm", "a");
    if (inFunc == 1) {
        mainMIPS = fopen("funcs.asm", "a");
    }

    fprintf(mainMIPS, "la $t0, %s #get address\n", id);
    fprintf(mainMIPS, "li $t1, %s #new value\n", c);
    fprintf(mainMIPS, "sw $t1 0($t0) #save new value\n");
    fclose(mainMIPS);

}

void emitIntVar(char id[50], char val[10]) {
    // if (inFunc == 1) {
    //     mainMIPS = fopen("funcs.asm", "a");
    // }

    dataMIPS = fopen("dataMIPS.asm", "a");

    fprintf(dataMIPS, "%s:   .word  %s\n", id, val);

    fclose(dataMIPS); 

}

void setIntVar(char id[50], char val[10]) {

    mainMIPS = fopen("MIPScode.asm", "a");
    if (inFunc == 1) {
        mainMIPS = fopen("funcs.asm", "a");
    }
    
    char command[5];
    strcpy(command, "li");

    if (!isdigit(val[0])) {
        strcpy(command, "move");
    } 
    
    fprintf(mainMIPS, "la $t0, %s #get address\n", id);
    fprintf(mainMIPS, "%s $t1, %s #new value\n", command, val);
    fprintf(mainMIPS, "sw $t1 0($t0) #save new value\n");

    fclose(mainMIPS);

}

void emitMIPSElseStmt(int ifNum) {

    mainMIPS = fopen("MIPScode.asm", "a");
    if (inFunc == 1) {
        mainMIPS = fopen("funcs.asm", "a");
    }

    fprintf(mainMIPS, "\n# --- ELSE STMT --- #\n");
    fprintf(mainMIPS, "false%d:\n", ifNum);

    fclose(mainMIPS);

}

void emitMIPSEndOfIfBlock(int ifNum) {

    mainMIPS = fopen("MIPScode.asm", "a");
    if (inFunc == 1) {
        mainMIPS = fopen("funcs.asm", "a");
    }

    fprintf(mainMIPS, "# --- JUMP PAST ELSE --- #\n");
    fprintf(mainMIPS, "beq $0, $0, jumpElse%d\n", ifNum);

    fclose(mainMIPS);
}

void emitMIPSPassElse(int ifNum) {
    mainMIPS = fopen("MIPScode.asm", "a");
    if (inFunc == 1) {
        mainMIPS = fopen("funcs.asm", "a");
    }

    fprintf(mainMIPS, "# ---PAST ELSE--->\n");
    fprintf(mainMIPS, "jumpElse%d:\n", ifNum);

    fclose(mainMIPS);
}

void emitMIPSIncrement(char id[10]) {

    mainMIPS = fopen("MIPScode.asm", "a");
    if (inFunc == 1) {
        mainMIPS = fopen("funcs.asm", "a");
    }
    
    fprintf(mainMIPS, "lw $s0, %s\n", id);
    fprintf(mainMIPS, "addi $s0, $s0, 1\n");

    fclose(mainMIPS);

}

void emitMIPSWhile(int n) {

    // loops = fopen("loops.asm", "a");
    mainMIPS = fopen("MIPScode.asm", "a");

    // fprintf(loops, "while%d:", n);
    // fprintf(mainMIPS, "jal while%d\n", n);
    inFunc = 1;
    inLoop = 1;

    fclose(mainMIPS);
}

void emitMIPSEndWhile(char var1[10], char var2[10], char type1[10], char type2[10], int n) {

    mainMIPS = fopen("MIPScode.asm", "a");
    if (inFunc) {
        mainMIPS = fopen("funcs.asm", "a");
    }

    if (!strcmp(type1, "id")) {
        fprintf(mainMIPS, "lw $t0, %s\n", var1);
    } else {
        fprintf(mainMIPS, "li $t0, %s\n", var1);        
    }

    if (!strcmp(type2, "id")) {
        fprintf(mainMIPS, "lw $t1, %s\n", var2);
    } else {
        fprintf(mainMIPS, "li $t1, %s\n", var2);        
    }

    fprintf(mainMIPS, "%s\n", condString);
    fprintf(mainMIPS, ".end while%d\n", n);
    inFunc = 0;
    inLoop = 0;

    fclose(mainMIPS);
} 

void loadMIPSVarCond(char var1[10], char var2[10], char type1[10], char type2[10]) {

    mainMIPS = fopen("MIPScode.asm", "a");
    if (inFunc == 1 && !inLoop) {
        mainMIPS = fopen("funcs.asm", "a");
    }
    // printf("type1=%s , type2=%s", type1, type2);

    if (!strcmp(type1, "id")) {
        fprintf(mainMIPS, "lw $t0, %s\n", var1);
    } else {
        fprintf(mainMIPS, "li $t0, %s\n", var1);        
    }

    if (!strcmp(type2, "id")) {
        fprintf(mainMIPS, "lw $t1, %s\n", var2);
    } else {
        fprintf(mainMIPS, "li $t1, %s\n", var2);        
    }
    
    fclose(mainMIPS);    

}

char* emitMIPSCond(char var1[10], char var2[10], char operator[5], int n) {

    char op[5];
    char loopType[5] = "false";
    // printf("In loop = %d\n", inLoop);
    
    mainMIPS = fopen("MIPScode.asm", "a");
    if (inFunc == 1) {
        //TODO fix this now
        // fprintf(mainMIPS, "jal while%d\n", n);      
        // fclose (mainMIPS);  
        mainMIPS = fopen("funcs.asm", "a");
    }


    // fprintf(mainMIPS, "li $t0, %s\n", var1);
    // fprintf(mainMIPS, "li $t1, %s\n", var2);
    fprintf(mainMIPS, "# --- CONDITION --- #\n");

    if (!strcmp(operator, "!=")) {
        strcpy(op, "beq");
    } 
    else if (!strcmp(operator, "==")) {
        strcpy(op, "bne");
    }
    else if (!strcmp(operator, ">=")) {
        strcpy(op, "ble");
    }
    else if (!strcmp(operator, "<=")) {
        strcpy(op, "bge");
    }
    else if (!strcmp(operator, ">")) {
        strcpy(op, "blt");
    }
    else if (!strcmp(operator, "<")) {
        strcpy(op, "bgt");
    }

    if (!inLoop) {
        fprintf(mainMIPS, "%s $t0, $t1, %s%d\n", op,  loopType, n);
        
        // Basically we use the reverse of the operator becuase
        // the "if" block executes before the "else" block
    }

    // for while loops
    else {
        sprintf(condString, "%s $t1, $t0, while%d", op, n);
        fprintf(mainMIPS, "\nwhile%d:\n", n);
        fclose(mainMIPS);
        mainMIPS = fopen("MIPScode.asm", "a");
        fprintf(mainMIPS, "%s $t1, $t0, while%d\n", op, n);
    }

    fclose(mainMIPS);

    return condString;

}

void emitMIPSParameters(char param[50], int count) {

    // scrapped code
    // mainMIPS = fopen("MIPScode.asm", "a");
    // if (inFunc == 1) {
    //     mainMIPS = fopen("funcs.asm", "a");
    // }

    dataMIPS = fopen("dataMIPS.asm", "a");

    strcpy(paramArray[count], param);
    printf("paramArray[%d] = %s\n", count, paramArray[count]);

    fclose(dataMIPS);
}

void setMIPSParameters(char *param, int n) {

    mainMIPS = fopen("MIPScode.asm", "a");
    if (inLoop) {
        mainMIPS = fopen("funcs.asm", "a");
    }

    if (!isdigit(param[0])) {

        fprintf(mainMIPS, "lw $a%d, %s\n", n, param);

    } else {

        fprintf(mainMIPS, "li $a%d, %s\n", n, param);
    }

    fclose(mainMIPS);
}

void emitMIPSFunc (char func[50]) {

    funcs = fopen("funcs.asm", "a");
    mainMIPS = fopen("MIPScode.asm", "a");

    if (strcmp(func, "main")) {
        inFunc = 1;
        fprintf(funcs, "\n%s:\n", func);
    } 
    else {
        fprintf(mainMIPS, "\n%s:\n", func);
    }
    fclose(funcs);
    fclose(mainMIPS);

}

void emitMIPSFuncCall (char func[50]) {


    mainMIPS = fopen("MIPScode.asm", "a");
    if (inLoop) {
        mainMIPS = fopen("funcs.asm", "a");
    }
    fprintf(mainMIPS, "jal  %s\n", func);
    fclose(mainMIPS);

}

void emitMIPSReturn (char rv[50], char type[50]) {

    funcs = fopen("funcs.asm", "a");

    if (!strcmp(type, "int")) {
        fprintf(funcs, "li $v1, %s\n", rv);
    } else {
        fprintf(funcs, "lw $v1, %s\n", rv);
    }

    // fprintf(funcs, "jr  $ra\n");

    fclose(funcs);
    
}

void emitMIPSGetReturn () {

    mainMIPS = fopen("MIPScode.asm", "a");
    if (inFunc == 1) {
        mainMIPS = fopen("funcs.asm", "a");
    }

    

    fclose(mainMIPS);

}


void endOfMIPSFunction (char funcName[50]) {

    funcs = fopen("funcs.asm", "a");

    if (inLoop) {
        
    }

    if (strcmp(funcName, "main")) {

        fprintf(funcs, "jr  $ra\n");
        fprintf(funcs, ".end %s\n\n", funcName);
        inFunc = 0;

    }

    fclose(funcs);

}

void emitEndOfAssemblyCode(){
    mainMIPS = fopen("MIPScode.asm", "a");

    fprintf(mainMIPS, "# -----------------\n");
    fprintf(mainMIPS, "#  Done, terminate program.\n\n");
    // fprintf(mainMIPS, "li $v0,1   # call code for terminate\n");
    // fprintf(mainMIPS, "syscall      # system call (terminate)\n");
    fprintf(mainMIPS, "li $v0,10   # call code for terminate\n");
    fprintf(mainMIPS, "syscall      # system call (terminate)\n");
    fprintf(mainMIPS, ".end main\n");

    fclose(mainMIPS);    
}

void emitMIPSEquation(char var1[10], char var2[10], char op) {

    // int isDigit1 = isdigit(var1[0]);
    // int isDigit2 = isdigit(var2[0]);

    // printf("input: var1=%s | Var2=%s | op=%c", var1, var2, op);
    funcs = fopen("funcs.asm", "a");

    if (!isdigit(var1[0])) {
        int index = getParamNum(var1);
        if (index != -1) {
            fprintf(funcs, "move $t0, $a%d\n", index);
        } 
        else {
            fprintf(funcs, "lw $t0, %s\n", var1);
        }
    // digit load
    } else {
        fprintf(funcs, "li $t0, %s\n", var1);
    }

    if (!isdigit(var2[0])) {       
        int index = getParamNum(var2);
        if (index != -1) {
            fprintf(funcs, "move $t1, $a%d\n", index);
        } 
        else {
            fprintf(funcs, "lw $t1, %s\n", var1);
        }
    // digit load
    } else {
        fprintf(funcs, "li $t1, %s\n", var2);
    }

    // all expression results are stored in $s1
    switch (op) {
		case '+':
			fprintf(funcs, "add $s1, $t0, $t1\n");
			break;
		case '-':
			fprintf(funcs, "sub $s1, $t0, $t1\n");
			break;
		case '*':
			fprintf(funcs, "mul $s1, $t0, $t1\n");
			break;
		case '/':
			fprintf(funcs, "div $s1, $t0, $t1\n");
			break;
	}
    
    fclose(funcs);

}

void appendFiles() {

    char ch;

    mainMIPS = fopen("MIPScode.asm", "r");
    funcs = fopen("funcs.asm", "r");
    dataMIPS = fopen("dataMIPS.asm", "a");

    fprintf(dataMIPS, "\n");

    while((ch = getc(mainMIPS)) != EOF)
        putc(ch, dataMIPS);

    fprintf(dataMIPS, "\n");

    while((ch = getc(funcs)) != EOF)
        putc(ch, dataMIPS);

    fprintf(dataMIPS, "\n");

    // while((ch = getc(loops)) != EOF)
    //     putc(ch, dataMIPS);
 
    // printf("\nCONTENTS COPIED TO FILE: \"dataMIPS.asm\"\n");
    fclose(mainMIPS);
    fclose(funcs);
    fclose(dataMIPS);

}

int getParamNum (char name[50]) {

    for (size_t i = 0; i < 4; i++) {
        if (!strcmp(paramArray[i], name)) {
            // printf("currIndex = %s", paramArray[i]);
            return i; 
            break;
        }
    }

    return -1;   
}