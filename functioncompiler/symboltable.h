#include <string.h>
#include <stdio.h>

// Define the structure for a symbol table entry
struct Entry {
    int itemID;             // Unique identifier for the symbol
    char itemName[50];      // Name of the identifier (variable, function, etc.)
    char itemKind[8];       // Kind of identifier (e.g., function, variable)
    char itemType[8];       // Data type (e.g., int, char, etc.)
    char itemValue[25];     // Assigned value (if any)
    char scope[50];         // Scope of the identifier (e.g., GLOBAL or function name)
    int itemUsed;           // Flag indicating usage (1 = used, 0 = unused)
};

// Symbol table and related global variables
struct Entry symTabItems[100]; // Array to store symbol table entries
int symTabIndex = 0;           // Tracks the next available index in the table
int SYMTAB_SIZE = 20;          // Maximum size of the symbol table

// Utility function to log access to the symbol table
void symTabAccess() {
    printf("Symbol table accessed.\n\n");
}

// Adds a new entry to the symbol table
void addItem(char itemName[50], char itemKind[8], char itemType[8], char scope[50]) {
    symTabItems[symTabIndex].itemID = symTabIndex;
    strcpy(symTabItems[symTabIndex].itemName, itemName);
    strcpy(symTabItems[symTabIndex].itemKind, itemKind);
    strcpy(symTabItems[symTabIndex].itemType, itemType);
    strcpy(symTabItems[symTabIndex].itemValue, "NULL");
    strcpy(symTabItems[symTabIndex].scope, scope);
    symTabItems[symTabIndex].itemUsed = 0;
    symTabIndex++;
}

// Displays the contents of the symbol table
void showSymTable() {
    printf("    ID       Name        Kind         Type      Value     Scope    \n");
    printf("--------------------------------------------------------------------\n");
    for (int i = 0; i < symTabIndex; i++) {
        printf("%5d  %10s  %10s  %10s %10s %10s \n",
            symTabItems[i].itemID,
            symTabItems[i].itemName,
            symTabItems[i].itemKind,
            symTabItems[i].itemType,
            symTabItems[i].itemValue,
            symTabItems[i].scope);
    }
    printf("--------------------------------------------------------------------\n\n");
}

// Checks if an identifier exists in the symbol table within a specific scope
int found(char itemName[50], char scope[50]) {
    for (int i = 0; i < symTabIndex; i++) {
        int isGlobal = strcmp(symTabItems[i].scope, "GLOBAL");
        int str1 = strcmp(symTabItems[i].itemName, itemName);
        int str2 = strcmp(symTabItems[i].scope, scope);

        if (str1 == 0 && (str2 == 0 || isGlobal == 0)) {
            return 1; // Identifier found
        }
    }
    return 0; // Identifier not found
}

// Gets the current size of the symbol table
int getSymTabIndex() {
    return symTabIndex;
}

// Sets the value of an identifier in the symbol table
int setItemValue(char itemName[50], char itemValue[8], char scope[50]) {
    for (int i = 0; i < symTabIndex; i++) {
        int isGlobal = strcmp(symTabItems[i].scope, "GLOBAL");
        int str1 = strcmp(symTabItems[i].itemName, itemName);
        int str2 = strcmp(symTabItems[i].scope, scope);

        if (str1 == 0 && (isGlobal == 0 || str2 == 0)) {
            strcpy(symTabItems[i].itemValue, itemValue);
            printf("Set value of %s to %s\n", itemName, itemValue);
            return 1; // Value set successfully
        }
    }
    printf("ERROR: Item %s not found\n", itemName);
    return 0;
}

// Marks an identifier as used in the symbol table
int setItemUsed(char itemName[50], char scope[50]) {
    for (int i = 0; i < symTabIndex; i++) {
        int isGlobal = strcmp(symTabItems[i].scope, "GLOBAL");
        int str1 = strcmp(symTabItems[i].itemName, itemName);
        int str2 = strcmp(symTabItems[i].scope, scope);

        if (str1 == 0 && (isGlobal == 0 || str2 == 0)) {
            symTabItems[i].itemUsed = 1;
            return 1; // Marked as used
        }
    }
    printf("Item %s not found\n", itemName);
    return 0;
}

// Retrieves the value of an identifier from the symbol table
char *getValue(char itemName[50], char scope[50]) {
    for (int i = 0; i < symTabIndex; i++) {
        int isGlobal = strcmp(symTabItems[i].scope, "GLOBAL");
        int str1 = strcmp(symTabItems[i].itemName, itemName);
        int str2 = strcmp(symTabItems[i].scope, scope);

        if (str1 == 0 && (str2 == 0 || isGlobal == 0)) {
            return symTabItems[i].itemValue;
        }
    }
    return "NULL"; // Identifier not found
}

// Retrieves the ID of an identifier from the symbol table
int getItemID(char itemName[50], char scope[50]) {
    for (int i = 0; i < symTabIndex; i++) {
        int isGlobal = strcmp(symTabItems[i].scope, "GLOBAL");
        int str1 = strcmp(symTabItems[i].itemName, itemName);
        int str2 = strcmp(symTabItems[i].scope, scope);

        if (str1 == 0 && (str2 == 0 || isGlobal == 0)) {
            return symTabItems[i].itemID;
        }
    }
    return -1; // Identifier not found
}

// Retrieves the data type of a variable
char *getVariableType(char itemName[50], char scope[50]) {
    for (int i = 0; i < symTabIndex; i++) {
        int isGlobal = strcmp(symTabItems[i].scope, "GLOBAL");
        int str1 = strcmp(symTabItems[i].itemName, itemName);
        int str2 = strcmp(symTabItems[i].scope, scope);

        if (str1 == 0 && (str2 == 0 || isGlobal == 0)) {
            return symTabItems[i].itemType;
        }
    }
    return NULL; // Type not found
}

// Retrieves the kind of an identifier
char *getItemKind(char itemName[50], char scope[50]) {
    for (int i = 0; i < symTabIndex; i++) {
        int isGlobal = strcmp(symTabItems[i].scope, "GLOBAL");
        int str1 = strcmp(symTabItems[i].itemName, itemName);

        if (str1 == 0) {
            return symTabItems[i].itemKind;
        }
    }
    return NULL; // Kind not found
}

// Compares the types of two identifiers
int compareTypes(char itemName1[50], char itemName2[50], char scope[50]) {
    const char *type1 = getVariableType(itemName1, scope);
    const char *type2 = getVariableType(itemName2, scope);

    if (type1 && type2) {
        return strcmp(type1, type2) == 0; // Returns 1 if types match, 0 otherwise
    }
    return 0; // Types do not match or not found
}
