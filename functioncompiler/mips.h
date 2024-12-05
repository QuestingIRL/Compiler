#include <stdio.h>
#include <ctype.h>

// File pointers for different MIPS sections
FILE *mainMIPS;
FILE *dataMIPS;
FILE *funcs;
FILE *loops;

// Flags for function and loop context
int inFunc = 0;
int inLoop = 0;

// Buffers for parameters and conditions
char paramArray[4][50];
char condString[32];

// Emits a string in the MIPS assembly
void emitMIPSString(char myString[50], int stringCount) {
    // Open appropriate file for writing MIPS assembly
    mainMIPS = fopen(inFunc ? "funcs.asm" : "MIPScode.asm", "a");
    dataMIPS = fopen("dataMIPS.asm", "a");

    // Write the string to the data section
    fprintf(dataMIPS, "msg%d: .asciiz %s\n", stringCount, myString);
    fclose(dataMIPS);

    // Write instructions to print the string
    fprintf(mainMIPS, "li $v0, 4\n");
    fprintf(mainMIPS, "la $a0, msg%d\n", stringCount);
    fprintf(mainMIPS, "syscall\n");
    fclose(mainMIPS);
}

// Initializes MIPS assembly files with standard headers
void initAssemblyFile() {
    // Create and initialize assembly files
    mainMIPS = fopen("MIPScode.asm", "w");
    dataMIPS = fopen("dataMIPS.asm", "w");
    funcs = fopen("funcs.asm", "w");

    // Write headers to the text section
    fprintf(mainMIPS, ".text\n");
    fprintf(mainMIPS, "# -----------------------\n");

    // Write headers to the data section
    fprintf(dataMIPS, ".data\n");
    fprintf(dataMIPS, "newLine: .asciiz \"\\n\"\n");

    // Close all files
    fclose(mainMIPS);
    fclose(dataMIPS);
    fclose(funcs);
}

// Emits an assignment instruction in MIPS assembly
void emitMIPSAssignment(char id1[10], char id2[10]) {
    // Open appropriate file for writing
    mainMIPS = fopen(inFunc ? "funcs.asm" : "MIPScode.asm", "a");

    // Write assignment instruction
    fprintf(mainMIPS, "sw %s, %s\n", id2, id1);

    fclose(mainMIPS);
}

// Emits a constant integer assignment in MIPS assembly
void emitMIPSConstantIntAssignment(int id1, char id2[50]) {
    // Open appropriate file for writing
    mainMIPS = fopen(inFunc ? "funcs.asm" : "MIPScode.asm", "a");

    // Write the instruction to load a constant integer into a register
    fprintf(mainMIPS, "li $t%d, %s\n", id1, id2);

    fclose(mainMIPS);
}

// Emits a newline instruction in MIPS assembly
void emitMIPSNewLine() {
    // Open appropriate file for writing
    mainMIPS = fopen(inFunc ? "funcs.asm" : "MIPScode.asm", "a");

    // Write instructions to print a newline
    fprintf(mainMIPS, "# PRINTING NEW LINE ---->\n");
    fprintf(mainMIPS, "li $v0, 4\n");
    fprintf(mainMIPS, "la $a0, newLine\n");
    fprintf(mainMIPS, "syscall\n");

    fclose(mainMIPS);
}


// Emits an integer print instruction in MIPS assembly
void emitMIPSWriteInt(int n) {
    // Open the appropriate file for writing
    mainMIPS = fopen(inFunc ? "funcs.asm" : "MIPScode.asm", "a");

    // Write MIPS instructions to print an integer
    fprintf(mainMIPS, "# Printing integer -----------\n");
    fprintf(mainMIPS, "li $v0, 1\n");        // Set syscall code for print integer
    fprintf(mainMIPS, "li $a0, %d\n", n);    // Load the integer value into $a0
    fprintf(mainMIPS, "syscall\n");          // Trigger the syscall

    fclose(mainMIPS);
}

// Emits an identifier print instruction in MIPS assembly
void emitMIPSWriteId(char id[50], char type[5]) {
    // Open the appropriate file for writing
    mainMIPS = fopen(inFunc ? "funcs.asm" : "MIPScode.asm", "a");

    fprintf(mainMIPS, "# Printing identifier -----------\n");

    // Check the type of the identifier and write the corresponding MIPS instructions
    if (strcmp(type, "int") == 0) {
        fprintf(mainMIPS, "li $v0, 1\n");    // Syscall for printing an integer
        fprintf(mainMIPS, "lw $a0, %s\n", id); // Load the value of the integer
    } else if (strcmp(type, "char") == 0) {
        fprintf(mainMIPS, "li $v0, 11\n");   // Syscall for printing a character
        fprintf(mainMIPS, "lb $a0, %s\n", id); // Load the character value
    } else {
        fprintf(mainMIPS, "li $v0, 4\n");    // Syscall for printing a string
        fprintf(mainMIPS, "la $a0, %s\n", id); // Load the address of the string
    }

    fprintf(mainMIPS, "syscall\n");          // Trigger the syscall

    fclose(mainMIPS);
}

// Emits an array declaration in MIPS assembly
void emitMIPSArrayDecl(char id[50], int size) {
    // Open the data section file for writing
    dataMIPS = fopen("dataMIPS.asm", "a");

    // Write MIPS instructions to declare an array
    fprintf(dataMIPS, "%s: .space %d\n", id, size * 4); // Allocate space for the array

    fclose(dataMIPS);
}

// Emits an array assignment in MIPS assembly
void emitMIPSIntArrayAssign(char id[50], int index, int val) {
    // Open the appropriate file for writing
    mainMIPS = fopen(inFunc ? "funcs.asm" : "MIPScode.asm", "a");

    // Write MIPS instructions to assign a value to an array index
    fprintf(mainMIPS, "addi $s0, $zero, %d\n", val);     // Load the value into $s0
    fprintf(mainMIPS, "addi $t0, $t0, %d\n", index * 4); // Calculate the address offset
    fprintf(mainMIPS, "sw $s0, %s($t0)\n", id);          // Store the value at the calculated address

    fclose(mainMIPS);
}

// Emits a character declaration in MIPS assembly
void emitMIPSCharDecl(char id[50], char c[5]) {
    // Open the data section file for writing
    dataMIPS = fopen("dataMIPS.asm", "a");

    // Write MIPS instructions to declare a character variable
    fprintf(dataMIPS, "%s: .byte %s\n", id, c); // Declare a byte for the character

    fclose(dataMIPS);
}

// Sets the value of a character variable in MIPS assembly
void setCharVar(char id[50], char c[5]) {
    // Open the appropriate file for writing
    mainMIPS = fopen(inFunc ? "funcs.asm" : "MIPScode.asm", "a");

    // Write MIPS instructions to set the value of a character variable
    fprintf(mainMIPS, "la $t0, %s # Load address of %s\n", id, id);
    fprintf(mainMIPS, "li $t1, %s # Load new value into $t1\n", c);
    fprintf(mainMIPS, "sw $t1, 0($t0) # Store new value at address\n");

    fclose(mainMIPS);
}


void emitIntVar(char id[50], char val[10]) {

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

void emitMIPSParameters(char param[50], int count) {


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


    fclose(funcs);
    
}

// Retrieves the return value in MIPS assembly (placeholder for implementation)
void emitMIPSGetReturn() {
    // Open the appropriate file for writing
    mainMIPS = fopen(inFunc ? "funcs.asm" : "MIPScode.asm", "a");
    // Currently no additional functionality; placeholder for future enhancements
    fclose(mainMIPS);
}

// Ends a function in MIPS assembly
void endOfMIPSFunction(char funcName[50]) {
    funcs = fopen("funcs.asm", "a");

    // Emit return instructions for non-main functions
    if (strcmp(funcName, "main") != 0) {
        fprintf(funcs, "jr $ra\n");               // Return to the caller
        fprintf(funcs, ".end %s\n\n", funcName);  // Mark the end of the function
        inFunc = 0;                               // Reset function context flag
    }

    fclose(funcs);
}

// Emits the end of the MIPS assembly program
void emitEndOfAssemblyCode() {
    mainMIPS = fopen("MIPScode.asm", "a");

    // Emit program termination instructions
    fprintf(mainMIPS, "# -----------------\n");
    fprintf(mainMIPS, "#  Done, terminate program.\n\n");
    fprintf(mainMIPS, "li $v0,10   # System call for program termination\n");
    fprintf(mainMIPS, "syscall\n");
    fprintf(mainMIPS, ".end main\n");

    fclose(mainMIPS);
}

// Emits an equation in MIPS assembly
void emitMIPSEquation(char var1[10], char var2[10], char op) {
    funcs = fopen("funcs.asm", "a");

    // Load the first operand into $t0
    if (!isdigit(var1[0])) {  // Variable or parameter
        int index = getParamNum(var1);
        if (index != -1) {
            fprintf(funcs, "move $t0, $a%d\n", index); // Load parameter into $t0
        } else {
            fprintf(funcs, "lw $t0, %s\n", var1);      // Load variable into $t0
        }
    } else {
        fprintf(funcs, "li $t0, %s\n", var1);          // Load literal into $t0
    }

    // Load the second operand into $t1
    if (!isdigit(var2[0])) {  // Variable or parameter
        int index = getParamNum(var2);
        if (index != -1) {
            fprintf(funcs, "move $t1, $a%d\n", index); // Load parameter into $t1
        } else {
            fprintf(funcs, "lw $t1, %s\n", var2);      // Load variable into $t1
        }
    } else {
        fprintf(funcs, "li $t1, %s\n", var2);          // Load literal into $t1
    }

    // Perform the operation and store the result in $s1
    switch (op) {
        case '+':
            fprintf(funcs, "add $s1, $t0, $t1\n"); // Addition
            break;
        case '-':
            fprintf(funcs, "sub $s1, $t0, $t1\n"); // Subtraction
            break;
        case '*':
            fprintf(funcs, "mul $s1, $t0, $t1\n"); // Multiplication
            break;
        case '/':
            fprintf(funcs, "div $s1, $t0, $t1\n"); // Division
            break;
        default:
            fprintf(funcs, "# Unsupported operation\n");
            break;
    }

    fclose(funcs);
}


// Appends the content of MIPScode.asm and funcs.asm into dataMIPS.asm
void appendFiles() {
    char ch;

    // Open files for reading and appending
    mainMIPS = fopen("MIPScode.asm", "r");
    funcs = fopen("funcs.asm", "r");
    dataMIPS = fopen("dataMIPS.asm", "a");

    fprintf(dataMIPS, "\n"); // Add a newline for readability

    // Append the contents of mainMIPS to dataMIPS
    while ((ch = getc(mainMIPS)) != EOF) {
        putc(ch, dataMIPS);
    }

    fprintf(dataMIPS, "\n"); // Add a newline for separation

    // Append the contents of funcs to dataMIPS
    while ((ch = getc(funcs)) != EOF) {
        putc(ch, dataMIPS);
    }

    fprintf(dataMIPS, "\n"); // Add a final newline

    // Close all files
    fclose(mainMIPS);
    fclose(funcs);
    fclose(dataMIPS);
}

// Retrieves the parameter index for a given parameter name
int getParamNum(char name[50]) {
    for (size_t i = 0; i < 4; i++) {
        if (strcmp(paramArray[i], name) == 0) { // Compare with stored parameter names
            return i; // Return the index if the parameter is found
        }
    }
    return -1; // Return -1 if the parameter is not found
}
