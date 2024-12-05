// Set of functions to emit Intermediate Representation (IR) code

FILE *IRcode;  // File for storing IR code instructions
FILE *dataIR;  // File for storing data section of IR code

// Initializes IR code files and writes a generic header
void initIRcodeFile() {
    IRcode = fopen("IRcode.ir", "w");  // Open IR code file for writing
    dataIR = fopen("dataIR.ir", "w");  // Open data IR file for writing

    // Write headers to the files
    fprintf(IRcode, "MAIN:\n");
    fprintf(IRcode, "# -----------------------\n");

    fprintf(dataIR, "DATA:\n");  // Header for data section

    fclose(IRcode);
    fclose(dataIR);
}

// Emits IR code for assigning the value of one identifier to another
void emitIRAssignment(char *id1, char *id2) {
    IRcode = fopen("IRcode.ir", "a");  // Open IR code file for appending

    fprintf(IRcode, "LOAD T1,%s\n", id1); // Load value of id1 into temporary register T1
    fprintf(IRcode, "LOAD T2,%s\n", id2); // Load value of id2 into temporary register T2
    fprintf(IRcode, "LOAD T2, T1\n");     // Store the value of T1 into T2

    fclose(IRcode);
}

// Emits IR code for assigning a constant integer to a variable
void emitIRConstantIntAssignment(int id1, char id2[50]) {
    IRcode = fopen("IRcode.ir", "a");

    fprintf(IRcode, "LOAD T%d,%s\n", id1, id2); // Load constant integer into temporary register

    fclose(IRcode);
}

// Emits IR code to print an integer value
void emitIRWriteInt(int n) {
    IRcode = fopen("IRcode.ir", "a");

    fprintf(IRcode, "# Printing -----------\n");
    fprintf(IRcode, "LOAD V0, 1\n");       // Set system call code for printing an integer
    fprintf(IRcode, "LOAD A0, %d\n", n);   // Load the integer value into A0 register
    fprintf(IRcode, "SYSTEM CALL\n");      // Trigger system call

    fclose(IRcode);
}

// Emits IR code to print the value of an identifier
void emitIRWriteId(char id[50], char type[5]) {
    IRcode = fopen("IRcode.ir", "a");

    fprintf(IRcode, "# Printing -----------\n");

    if (strcmp(type, "int") == 0) {        // If the identifier is an integer
        fprintf(IRcode, "LOAD V0, 1\n");   // Set system call code for printing an integer
        fprintf(IRcode, "LOAD WORD: A0, %s\n", id); // Load the value into A0 register
    } else {                              // If the identifier is a character
        fprintf(IRcode, "LOAD V0, 4\n");   // Set system call code for printing a character
        fprintf(IRcode, "LOAD AD: A0, %s\n", id);  // Load the value into A0 register
    }

    fprintf(IRcode, "SYSTEM CALL\n");      // Trigger system call

    fclose(IRcode);
}

// Emits IR code for declaring an array
void emitIRArrayDecl(char id[50], int size) {
    dataIR = fopen("dataIR.ir", "a");

    fprintf(dataIR, "%s  BLOCK   %d", id, size); // Allocate a block of memory for the array

    fclose(dataIR);
}

// Emits IR code for declaring a character variable
void emitIRCharDecl(char id[50], char c) {
    dataIR = fopen("dataIR.ir", "a");

    fprintf(dataIR, "%s  BYTE   \'%c\'", id, c); // Declare a byte for the character

    fclose(dataIR);
}

// Emits the termination code for the IR program
void emitEndOfAssemblyCodeIR() {
    IRcode = fopen("IRcode.ir", "a");

    fprintf(IRcode, "# -----------------\n");
    fprintf(IRcode, "#  Done, terminate program.\n\n");
    fprintf(IRcode, "LOAD V0,10   # call code for terminate\n");
    fprintf(IRcode, "SYSTEM CALL      # system call (terminate)\n");
    fprintf(IRcode, "END MAIN\n");

    fclose(IRcode);
}

// Emits IR code for declaring an integer variable with a value
void emitIntVarIR(char id[50], int val) {
    dataIR = fopen("dataIR.ir", "a");

    fprintf(dataIR, "%s:   WORD  %d\n", id, val); // Declare a word for the integer with its value

    fclose(dataIR);
}

// Adds IR code for a new function (currently unimplemented)
void emitNewFuncIR(char func[10]) {
    // Future implementation placeholder
}

// Merges the contents of IR code into the data section
void addMainToDataIR() {
    IRcode = fopen("IRcode.ir", "a+");
    dataIR = fopen("dataIR.ir", "a+");

    if (!IRcode || !dataIR) {
        printf("Unable to open/detect file(s)\n");
        return;
    }

    char buf[100];

    fprintf(dataIR, "\n"); // Add a newline for readability

    // Append contents of IRcode to dataIR
    while (!feof(IRcode)) {
        fgets(buf, sizeof(buf), IRcode);
        fprintf(dataIR, "%s", buf);
    }

    fprintf(dataIR, "\n");

    fclose(IRcode);
    fclose(dataIR);
}
