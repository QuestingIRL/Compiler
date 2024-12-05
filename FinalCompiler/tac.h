#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// File pointers for IR code and data sections
FILE *IRcode;
FILE *dataIR;

// Initializes the IR code file with a generic header
void initIRcodeFile() {
    IRcode = fopen("IRcode.ir", "w");
    dataIR = fopen("dataIR.ir", "w");

    // Add main section header
    fprintf(IRcode, "MAIN:\n");
    fprintf(IRcode, "# -----------------------\n");

    // Add data section header
    fprintf(dataIR, "DATA:\n");

    fclose(IRcode);
    fclose(dataIR);
}

// Emits IR code for an assignment operation
void emitIRAssignment(char *id1, char *id2) {
    IRcode = fopen("IRcode.ir", "a");

    fprintf(IRcode, "LOAD T1,%s\n", id1);  // Load first variable into T1
    fprintf(IRcode, "LOAD T2,%s\n", id2);  // Load second variable into T2
    fprintf(IRcode, "LOAD T2, T1\n");      // Assign T1's value to T2

    fclose(IRcode);
}

// Emits IR code for assigning a constant integer to a variable
void emitIRConstantIntAssignment(int id1, char id2[50]) {
    IRcode = fopen("IRcode.ir", "a");

    fprintf(IRcode, "LOAD T%d,%s\n", id1, id2);  // Assign constant value to Tn

    fclose(IRcode);
}

// Emits IR code for writing an integer value to the output
void emitIRWriteInt(int n) {
    IRcode = fopen("IRcode.ir", "a");

    fprintf(IRcode, "# Printing -----------\n");
    fprintf(IRcode, "LOAD V0, 1\n");      // Syscall for integer print
    fprintf(IRcode, "LOAD A0, %d\n", n);  // Load the integer into A0
    fprintf(IRcode, "SYSTEM CALL\n");

    fclose(IRcode);
}

// Emits IR code for writing a variable's value to the output
void emitIRWriteId(char id[50], char type[5]) {
    IRcode = fopen("IRcode.ir", "a");

    fprintf(IRcode, "# Printing -----------\n");

    if (strcmp(type, "int") == 0) {
        // Print integer
        fprintf(IRcode, "LOAD V0, 1\n");
        fprintf(IRcode, "LOAD WORD: A0, %s\n", id);
    } else {
        // Print character
        fprintf(IRcode, "LOAD V0, 4\n");
        fprintf(IRcode, "LOAD AD: A0, %s\n", id);
    }
    fprintf(IRcode, "SYSTEM CALL\n");

    fclose(IRcode);
}

// Emits IR code for array declaration
void emitIRArrayDecl(char id[50], int size) {
    dataIR = fopen("dataIR.ir", "a");

    fprintf(dataIR, "%s  BLOCK   %d\n", id, size);  // Declare block for array

    fclose(dataIR);
}

// Emits IR code for character declaration
void emitIRCharDecl(char id[50], char c) {
    dataIR = fopen("dataIR.ir", "a");

    fprintf(dataIR, "%s  BYTE   \'%c\'\n", id, c);  // Declare single character

    fclose(dataIR);
}

// Emits IR code to terminate the program
void emitEndOfAssemblyCodeIR() {
    IRcode = fopen("IRcode.ir", "a");

    fprintf(IRcode, "# -----------------\n");
    fprintf(IRcode, "#  Done, terminate program.\n\n");
    fprintf(IRcode, "LOAD V0,10   # Syscall code for termination\n");
    fprintf(IRcode, "SYSTEM CALL\n");
    fprintf(IRcode, "END MAIN\n");

    fclose(IRcode);
}

// Emits IR code for an integer variable declaration
void emitIntVarIR(char id[50], int val) {
    dataIR = fopen("dataIR.ir", "a");

    fprintf(dataIR, "%s:   WORD  %d\n", id, val);  // Declare integer variable

    fclose(dataIR);
}

// Function to emit a new function's IR code (placeholder)
void emitNewFuncIR(char func[10]) {
    // Implementation pending
}

// Appends IR code from "IRcode.ir" into "dataIR.ir"
void addMainToDataIR() {
    IRcode = fopen("IRcode.ir", "a+");
    dataIR = fopen("dataIR.ir", "a+");

    // Ensure files are successfully opened
    if (!IRcode || !dataIR) {
        printf("Unable to open/detect file(s)\n");
        return;
    }

    char buf[100];

    // Add a newline for readability
    fprintf(dataIR, "\n");

    // Write contents of IRcode to dataIR
    while (!feof(IRcode)) {
        fgets(buf, sizeof(buf), IRcode);
        fprintf(dataIR, "%s", buf);
    }

    fprintf(dataIR, "\n");

    fclose(IRcode);
    fclose(dataIR);
}
