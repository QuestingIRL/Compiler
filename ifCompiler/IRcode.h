// Set of functions to emit IR code
FILE * IRcode;
FILE * dataIR;

void  initIRcodeFile(){
    // Creates an IR file with a generic header that needs to be in every file

    IRcode = fopen("IRcode.ir", "w");
    dataIR = fopen("dataIR.ir", "w");
    
    //fprintf(IRcode, ".text\n");
    fprintf(IRcode, "MAIN:\n");
    fprintf(IRcode, "# -----------------------\n");

    // data
    fprintf(dataIR, "DATA:\n");
    //fprintf(dataIR, "newLOADne: .asciiz \"\\n\"\n");


    fclose(IRcode);
    fclose(dataIR);

}

void emitIRAssignment(char * id1, char * id2){
    IRcode = fopen("IRcode.ir", "a");

    fprintf(IRcode, "LOAD T1,%s\n", id1);
    fprintf(IRcode, "LOAD T2,%s\n", id2);
    fprintf(IRcode, "LOAD T2, T1\n");

    fclose(IRcode);
}

void emitIRConstantIntAssignment (int id1, char id2[50]){
    IRcode = fopen("IRcode.ir", "a");

    fprintf(IRcode, "LOAD T%d,%s\n", id1, id2);

    fclose(IRcode);
}

void emitIRWriteInt(int n){
    IRcode = fopen("IRcode.ir", "a");

    fprintf(IRcode, "# Printing -----------\n");
    fprintf(IRcode, "LOAD V0, 1\n");
    fprintf(IRcode, "LOAD A0, %d\n", n);
    fprintf(IRcode, "SYSTEM CALL\n");

    fclose(IRcode);
}

void emitIRWriteId(char id[50], char type[5]){
    IRcode = fopen("IRcode.ir", "a");

    fprintf(IRcode, "# Printing -----------\n");

    //if id is an int
    if (strcmp(type, "int") == 0) {
        fprintf(IRcode, "LOAD V0, 1\n");
        fprintf(IRcode, "LOAD WORD: A0, %s\n", id);
    } 
    // if id is a char
    else { 
        fprintf(IRcode, "LOAD V0, 4\n");
        fprintf(IRcode, "LOAD AD: A0, %s\n", id);
    }
    fprintf(IRcode, "SYSTEM CALL\n");    

    fclose(IRcode);
}

void emitIRArrayDecl (char id[50], int size) {
    dataIR = fopen("dataIR.ir", "a");

    // int bits = size*4;
    fprintf(dataIR, "%s  BLOCK   %d", id, size);

    fclose(dataIR);
}

void emitIRCharDecl (char id[50], char c) {
    dataIR = fopen("dataIR.ir", "a");

    fprintf(dataIR, "%s  BYTE   \'%c\'", id, c);

    fclose(dataIR);
}

void emitEndOfAssemblyCodeIR(){
    IRcode = fopen("IRcode.ir", "a ");

    fprintf(IRcode, "# -----------------\n");
    fprintf(IRcode, "#  Done, terminate program.\n\n");
    // fprintf(IRcode, "LOAD V0,1   # call code for terminate\n");
    // fprintf(IRcode, "SYSTEM CALL      # system call (terminate)\n");
    fprintf(IRcode, "LOAD V0,10   # call code for terminate\n");
    fprintf(IRcode, "SYSTEM CALL      # system call (terminate)\n");
    fprintf(IRcode, "END MAIN\n");

    fclose(IRcode);    
}

void emitIntVarIR(char id[50], int val) {

    dataIR = fopen("dataIR.ir", "a ");

    fprintf(dataIR, "%s:   WORD  %d\n", id, val);

    fclose(dataIR); 

}

void emitNewFuncIR(char func[10]) {



}

void addMainToDataIR() {

    IRcode = fopen("IRcode.ir", "a+");
    dataIR = fopen("dataIR.ir", "a+");
    //funcs = fopen("funcs.ir", "a+");
 
    // If file is not found then return.
    if (!IRcode && !dataIR) {
        printf("Unable to open/"
               "detect file(s)\n");
        return;
    }
 
    char buf[100];
 
    // expLOADcitly writing "\n"
    // to the destination file
    // so to enhance readabiLOADty.
    fprintf(dataIR, "\n");
 
    // writing the contents of
    // source file to destination file.
    while (!feof(IRcode)) {
        fgets(buf, sizeof(buf), IRcode);
        fprintf(dataIR, "%s", buf);
    }

    fprintf(dataIR, "\n");

    // while (!feof(funcs)) {
    //     fgets(buf, sizeof(buf), funcs);
    //     fprintf(dataIR, "%s", buf);
    // }
 
    // rewind(dataIR);
 
    // printing contents of
    // destination file to stdout.
    // while (!feof(dataIR)) {
    //     fgets(buf, sizeof(buf), dataIR);
    //     printf("%s", buf); //Prints result to console if needed
    // }
}   