#include <stdio.h>
#include <ctype.h>
#include <string.h>

// File pointers for different assembly files
FILE *mainMIPS;
FILE *dataMIPS;
FILE *funcs;

// Flags for context tracking
int inFunc = 0; // Indicates if currently inside a function
int inLoop = 0; // Indicates if currently inside a loop

// Global variables
char paramArray[4][50]; // Placeholder for parameters
char condString[32];    // Conditional string buffer

/**
 * Emits a string to the MIPS assembly files.
 * @param myString The string to emit.
 * @param stringCount Unique identifier for the string in .data.
 */
void emitMIPSString(char myString[50], int stringCount) {
    mainMIPS = fopen("MIPScode.asm", "a");
    if (inFunc == 1) {
        mainMIPS = fopen("funcs.asm", "a");
    }

    dataMIPS = fopen("dataMIPS.asm", "a");

    // Write the string to the .data section
    fprintf(dataMIPS, "msg%d: .asciiz %s\n", stringCount, myString);
    fclose(dataMIPS);

    // Write the instructions to print the string
    fprintf(mainMIPS, "li $v0, 4\n");
    fprintf(mainMIPS, "la $a0, msg%d\n", stringCount);
    fprintf(mainMIPS, "syscall\n");
    fclose(mainMIPS);
}

/**
 * Initializes the assembly files by creating necessary sections and placeholders.
 */
void initAssemblyFile() {
    mainMIPS = fopen("MIPScode.asm", "w");
    dataMIPS = fopen("dataMIPS.asm", "w");
    funcs = fopen("funcs.asm", "w");

    // Initialize the .text section
    fprintf(mainMIPS, ".text\n");
    fprintf(mainMIPS, "# -----------------------\n");

    // Initialize the .data section with a new line definition
    fprintf(dataMIPS, ".data\n");
    fprintf(dataMIPS, "newLine: .asciiz \"\\n\"\n");

    fclose(mainMIPS);
    fclose(dataMIPS);
    fclose(funcs);
}

/**
 * Emits an assignment statement in MIPS assembly.
 * @param id1 Destination identifier.
 * @param id2 Source identifier.
 */
void emitMIPSAssignment(char id1[10], char id2[10]) {
    mainMIPS = fopen("MIPScode.asm", "a");
    if (inFunc == 1) {
        mainMIPS = fopen("funcs.asm", "a");
    }

    fprintf(mainMIPS, "move %s, %s\n", id1, id2); // Generates a MIPS move instruction
    fclose(mainMIPS);
}

/**
 * Assigns a constant integer value to a register in MIPS assembly.
 * @param id1 Register index (e.g., t0, t1, etc.).
 * @param id2 Constant value as a string.
 */
void emitMIPSConstantIntAssignment(int id1, char id2[50]) {
    mainMIPS = fopen("MIPScode.asm", "a");
    if (inFunc == 1) {
        mainMIPS = fopen("funcs.asm", "a");
    }

    fprintf(mainMIPS, "li $t%d, %s\n", id1, id2); // Loads an immediate value into a register
    fclose(mainMIPS);
}

/**
 * Emits a newline in MIPS assembly.
 */
void emitMIPSNewLine() {
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

/**
 * Writes an integer to the console in MIPS assembly.
 * @param n The integer to write.
 */
void emitMIPSWriteInt(int n) {
    mainMIPS = fopen("MIPScode.asm", "a");
    if (inFunc == 1) {
        mainMIPS = fopen("funcs.asm", "a");
    }

    fprintf(mainMIPS, "# Printing integer -----------\n");
    fprintf(mainMIPS, "li $v0, 1\n");
    fprintf(mainMIPS, "li $a0, %d\n", n);
    fprintf(mainMIPS, "syscall\n");
    fclose(mainMIPS);
}


/**
 * Writes the value of a variable to the console in MIPS assembly.
 * @param id The variable identifier.
 * @param type The data type of the variable ("int", "char", or others).
 */
void emitMIPSWriteId(char id[50], char type[5]) {
    mainMIPS = fopen("MIPScode.asm", "a");
    if (inFunc == 1) {
        mainMIPS = fopen("funcs.asm", "a");
    }

    fprintf(mainMIPS, "# Printing -----------\n");

    if (strcmp(type, "int") == 0) {
        fprintf(mainMIPS, "li $v0, 1\n"); // Set syscall for integer print
        fprintf(mainMIPS, "lw $a0, %s\n", id); // Load integer value
    } else if (strcmp(type, "char") == 0) {
        fprintf(mainMIPS, "li $v0, 11\n"); // Set syscall for character print
        fprintf(mainMIPS, "lb $a0, %s\n", id); // Load character value
    } else {
        fprintf(mainMIPS, "li $v0, 4\n"); // Set syscall for string print
        fprintf(mainMIPS, "la $a0, %s\n", id); // Load string address
    }

    fprintf(mainMIPS, "syscall\n"); // Execute syscall
    fclose(mainMIPS);
}

/**
 * Declares an integer array in the MIPS data section.
 * @param id The identifier of the array.
 * @param size The number of elements in the array.
 */
void emitMIPSArrayDecl(char id[50], int size) {
    dataMIPS = fopen("dataMIPS.asm", "a");
    fprintf(dataMIPS, "%s:  .space   %d\n", id, size * 4); // Allocate memory for the array
    fclose(dataMIPS);
}

/**
 * Assigns a value to an element of an integer array in MIPS assembly.
 * @param id The identifier of the array.
 * @param index The index of the element.
 * @param val The value to assign.
 */
void emitMIPSIntArrayAssign(char id[50], int index, int val) {
    mainMIPS = fopen("MIPScode.asm", "a");
    if (inFunc) {
        mainMIPS = fopen("funcs.asm", "a");
    }

    fprintf(mainMIPS, "addi $s0, $zero, %d\n", val); // Load value into $s0
    fprintf(mainMIPS, "addi $t0, $zero, %d\n", index * 4); // Calculate offset
    fprintf(mainMIPS, "sw   $s0, %s($t0)\n", id); // Store value in array element
    fclose(mainMIPS);
}

/**
 * Declares a character variable in the MIPS data section.
 * @param id The identifier of the variable.
 * @param c The initial value of the character as a string.
 */
void emitMIPSCharDecl(char id[50], char c[5]) {
    dataMIPS = fopen("dataMIPS.asm", "a");
    fprintf(dataMIPS, "%s:  .byte   %s\n", id, c); // Define character variable
    fclose(dataMIPS);
}

/**
 * Sets a character variable to a new value in MIPS assembly.
 * @param id The identifier of the variable.
 * @param c The new value of the character as a string.
 */
void setCharVar(char id[50], char c[5]) {
    mainMIPS = fopen("MIPScode.asm", "a");
    if (inFunc == 1) {
        mainMIPS = fopen("funcs.asm", "a");
    }

    fprintf(mainMIPS, "la $t0, %s # Load address of variable\n", id);
    fprintf(mainMIPS, "li $t1, %s # Load new value into $t1\n", c);
    fprintf(mainMIPS, "sb $t1, 0($t0) # Store new value at the address\n");
    fclose(mainMIPS);
}


/**
 * Declares an integer variable in the MIPS data section.
 * @param id The identifier of the variable.
 * @param val The initial value of the variable.
 */
void emitIntVar(char id[50], char val[10]) {
    dataMIPS = fopen("dataMIPS.asm", "a");
    fprintf(dataMIPS, "%s:   .word  %s\n", id, val); // Define integer variable with initial value
    fclose(dataMIPS);
}

/**
 * Sets a new value to an integer variable in MIPS assembly.
 * @param id The identifier of the variable.
 * @param val The new value to assign.
 */
void setIntVar(char id[50], char val[10]) {
    mainMIPS = fopen("MIPScode.asm", "a");
    if (inFunc == 1) {
        mainMIPS = fopen("funcs.asm", "a");
    }

    char command[5];
    strcpy(command, "li"); // Default to "load immediate"

    if (!isdigit(val[0])) { // If the value is not a number, change to "move"
        strcpy(command, "move");
    }

    fprintf(mainMIPS, "la $t0, %s # Get address of variable\n", id);
    fprintf(mainMIPS, "%s $t1, %s # Load new value into $t1\n", command, val);
    fprintf(mainMIPS, "sw $t1, 0($t0) # Store new value at the address\n");
    fclose(mainMIPS);
}

/**
 * Emits the start of an else statement in MIPS assembly.
 * @param ifNum Unique identifier for the if block.
 */
void emitMIPSElseStmt(int ifNum) {
    mainMIPS = fopen("MIPScode.asm", "a");
    if (inFunc == 1) {
        mainMIPS = fopen("funcs.asm", "a");
    }

    fprintf(mainMIPS, "\n# --- ELSE STMT --- #\n");
    fprintf(mainMIPS, "false%d:\n", ifNum); // Label for the false branch
    fclose(mainMIPS);
}

/**
 * Emits the end of an if block in MIPS assembly.
 * @param ifNum Unique identifier for the if block.
 */
void emitMIPSEndOfIfBlock(int ifNum) {
    mainMIPS = fopen("MIPScode.asm", "a");
    if (inFunc == 1) {
        mainMIPS = fopen("funcs.asm", "a");
    }

    fprintf(mainMIPS, "# --- JUMP PAST ELSE --- #\n");
    fprintf(mainMIPS, "beq $0, $0, jumpElse%d\n", ifNum); // Unconditional branch to skip the else block
    fclose(mainMIPS);
}

/**
 * Emits the label to jump past the else block in MIPS assembly.
 * @param ifNum Unique identifier for the if block.
 */
void emitMIPSPassElse(int ifNum) {
    mainMIPS = fopen("MIPScode.asm", "a");
    if (inFunc == 1) {
        mainMIPS = fopen("funcs.asm", "a");
    }

    fprintf(mainMIPS, "# --- PAST ELSE --->\n");
    fprintf(mainMIPS, "jumpElse%d:\n", ifNum); // Label for code after else block
    fclose(mainMIPS);
}

/**
 * Increments the value of a variable in MIPS assembly.
 * @param id The identifier of the variable.
 */
void emitMIPSIncrement(char id[10]) {
    mainMIPS = fopen("MIPScode.asm", "a");
    if (inFunc == 1) {
        mainMIPS = fopen("funcs.asm", "a");
    }

    fprintf(mainMIPS, "lw $s0, %s\n", id); // Load the value
    fprintf(mainMIPS, "addi $s0, $s0, 1\n"); // Increment the value
    fprintf(mainMIPS, "sw $s0, %s\n", id); // Store the updated value
    fclose(mainMIPS);
}



/**
 * Loads two variables for conditional evaluation in MIPS assembly.
 * @param var1 The first variable.
 * @param var2 The second variable.
 * @param type1 The type of the first variable ("id" or "immediate").
 * @param type2 The type of the second variable ("id" or "immediate").
 */
void loadMIPSVarCond(char var1[10], char var2[10], char type1[10], char type2[10]) {
    mainMIPS = fopen("MIPScode.asm", "a");
    if (inFunc == 1 && !inLoop) {
        mainMIPS = fopen("funcs.asm", "a");
    }

    if (!strcmp(type1, "id")) {
        fprintf(mainMIPS, "lw $t0, %s\n", var1); // Load first variable
    } else {
        fprintf(mainMIPS, "li $t0, %s\n", var1); // Load immediate value
    }

    if (!strcmp(type2, "id")) {
        fprintf(mainMIPS, "lw $t1, %s\n", var2); // Load second variable
    } else {
        fprintf(mainMIPS, "li $t1, %s\n", var2); // Load immediate value
    }

    fclose(mainMIPS);
}

/**
 * Emits a conditional branch instruction in MIPS assembly.
 * @param var1 The first variable.
 * @param var2 The second variable.
 * @param operator The comparison operator (e.g., "==", "!=").
 * @param n Unique identifier for the condition.
 * @return A string representing the condition instruction.
 */
char* emitMIPSCond(char var1[10], char var2[10], char operator[5], int n) {
    char op[5];
    char loopType[5] = "false";
    mainMIPS = fopen("MIPScode.asm", "a");
    if (inFunc == 1) {
        mainMIPS = fopen("funcs.asm", "a");
    }

    fprintf(mainMIPS, "# --- CONDITION --- #\n");

    // Determine the correct MIPS branch instruction
    if (!strcmp(operator, "!=")) {
        strcpy(op, "beq");
    } else if (!strcmp(operator, "==")) {
        strcpy(op, "bne");
    } else if (!strcmp(operator, ">=")) {
        strcpy(op, "ble");
    } else if (!strcmp(operator, "<=")) {
        strcpy(op, "bge");
    } else if (!strcmp(operator, ">")) {
        strcpy(op, "blt");
    } else if (!strcmp(operator, "<")) {
        strcpy(op, "bgt");
    }

    if (!inLoop) {
        fprintf(mainMIPS, "%s $t0, $t1, %s%d\n", op, loopType, n); // Emit branch instruction
    } else {
        sprintf(condString, "%s $t1, $t0, while%d", op, n); // Save condition for looping
        fprintf(mainMIPS, "\nwhile%d:\n", n); // Loop label
        fclose(mainMIPS);
        mainMIPS = fopen("MIPScode.asm", "a");
        fprintf(mainMIPS, "%s $t1, $t0, while%d\n", op, n);
    }

    fclose(mainMIPS);
    return condString;
}

/**
 * Stores parameters into a parameter array and prints them for debugging.
 * @param param The parameter to store.
 * @param count The index of the parameter.
 */
void emitMIPSParameters(char param[50], int count) {
    dataMIPS = fopen("dataMIPS.asm", "a");
    strcpy(paramArray[count], param);
    printf("paramArray[%d] = %s\n", count, paramArray[count]);
    fclose(dataMIPS);
}

/**
 * Sets the MIPS argument registers with given parameters.
 * @param param The parameter value.
 * @param n The argument register index.
 */
void setMIPSParameters(char *param, int n) {
    mainMIPS = fopen("MIPScode.asm", "a");
    if (inLoop) {
        mainMIPS = fopen("funcs.asm", "a");
    }

    if (!isdigit(param[0])) {
        fprintf(mainMIPS, "lw $a%d, %s\n", n, param); // Load parameter from memory
    } else {
        fprintf(mainMIPS, "li $a%d, %s\n", n, param); // Load immediate parameter
    }

    fclose(mainMIPS);
}

/**
 * Emits a function declaration in MIPS assembly.
 * @param func The name of the function.
 */
void emitMIPSFunc(char func[50]) {
    funcs = fopen("funcs.asm", "a");
    mainMIPS = fopen("MIPScode.asm", "a");

    if (strcmp(func, "main")) {
        inFunc = 1; // Set context to within a function
        fprintf(funcs, "\n%s:\n", func); // Function label
    } else {
        fprintf(mainMIPS, "\n%s:\n", func); // Main label
    }

    fclose(funcs);
    fclose(mainMIPS);
}

/**
 * Emits a function call instruction in MIPS assembly.
 * @param func The name of the function to call.
 */
void emitMIPSFuncCall(char func[50]) {
    mainMIPS = fopen("MIPScode.asm", "a");
    if (inLoop) {
        mainMIPS = fopen("funcs.asm", "a");
    }
    fprintf(mainMIPS, "jal  %s\n", func); // Jump and link to the function
    fclose(mainMIPS);
}


/**
 * Emits the return value for a function in MIPS assembly.
 * @param rv The return value.
 * @param type The type of the return value ("int" or others).
 */
void emitMIPSReturn(char rv[50], char type[50]) {
    funcs = fopen("funcs.asm", "a");

    if (!strcmp(type, "int")) {
        fprintf(funcs, "li $v1, %s\n", rv); // Load immediate return value for integer
    } else {
        fprintf(funcs, "lw $v1, %s\n", rv); // Load return value from memory
    }

    fclose(funcs);
}

/**
 * Placeholder for emitting instructions to retrieve the return value.
 */
void emitMIPSGetReturn() {
    mainMIPS = fopen("MIPScode.asm", "a");
    if (inFunc == 1) {
        mainMIPS = fopen("funcs.asm", "a");
    }

    // Currently does nothing; add implementation as needed

    fclose(mainMIPS);
}

/**
 * Ends a function definition in MIPS assembly.
 * @param funcName The name of the function.
 */
void endOfMIPSFunction(char funcName[50]) {
    funcs = fopen("funcs.asm", "a");

    if (strcmp(funcName, "main")) {
        fprintf(funcs, "jr $ra\n"); // Return to caller
        fprintf(funcs, ".end %s\n\n", funcName); // End function label
        inFunc = 0; // Reset function context
    }

    fclose(funcs);
}

/**
 * Emits the end of the assembly code, terminating the program.
 */
void emitEndOfAssemblyCode() {
    mainMIPS = fopen("MIPScode.asm", "a");

    fprintf(mainMIPS, "# -----------------\n");
    fprintf(mainMIPS, "# Done, terminate program.\n\n");
    fprintf(mainMIPS, "li $v0,10   # call code for terminate\n");
    fprintf(mainMIPS, "syscall      # system call (terminate)\n");
    fprintf(mainMIPS, ".end main\n");

    fclose(mainMIPS);
}

/**
 * Emits an equation operation in MIPS assembly.
 * @param var1 The first operand.
 * @param var2 The second operand.
 * @param op The operator ('+', '-', '*', '/').
 */
void emitMIPSEquation(char var1[10], char var2[10], char op) {
    funcs = fopen("funcs.asm", "a");

    // Load first operand
    if (!isdigit(var1[0])) {
        int index = getParamNum(var1);
        if (index != -1) {
            fprintf(funcs, "move $t0, $a%d\n", index); // Load from argument
        } else {
            fprintf(funcs, "lw $t0, %s\n", var1); // Load from memory
        }
    } else {
        fprintf(funcs, "li $t0, %s\n", var1); // Load immediate
    }

    // Load second operand
    if (!isdigit(var2[0])) {
        int index = getParamNum(var2);
        if (index != -1) {
            fprintf(funcs, "move $t1, $a%d\n", index); // Load from argument
        } else {
            fprintf(funcs, "lw $t1, %s\n", var2); // Load from memory
        }
    } else {
        fprintf(funcs, "li $t1, %s\n", var2); // Load immediate
    }

    // Perform operation and store result in $s1
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

/**
 * Appends the main, function, and data assembly files into one file.
 */
void appendFiles() {
    char ch;

    mainMIPS = fopen("MIPScode.asm", "r");
    funcs = fopen("funcs.asm", "r");
    dataMIPS = fopen("dataMIPS.asm", "a");

    fprintf(dataMIPS, "\n");

    // Append main assembly code
    while ((ch = getc(mainMIPS)) != EOF)
        putc(ch, dataMIPS);

    fprintf(dataMIPS, "\n");

    // Append function assembly code
    while ((ch = getc(funcs)) != EOF)
        putc(ch, dataMIPS);

    fprintf(dataMIPS, "\n");

    fclose(mainMIPS);
    fclose(funcs);
    fclose(dataMIPS);
}

/**
 * Retrieves the parameter number for a given name from the parameter array.
 * @param name The name of the parameter.
 * @return The parameter index or -1 if not found.
 */
int getParamNum(char name[50]) {
    for (size_t i = 0; i < 4; i++) {
        if (!strcmp(paramArray[i], name)) {
            return i; // Return parameter index
        }
    }
    return -1; // Not found
}
