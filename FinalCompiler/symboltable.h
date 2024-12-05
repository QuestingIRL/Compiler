struct Entry {
    int itemID;                // Unique identifier for the symbol
    char itemName[50];         // Name of the identifier
    char itemKind[8];          // Specifies if it's a function or variable
    char itemType[8];          // Data type (int, char, etc.)
    char itemValue[25];        // Value assigned to the identifier
    char scope[50];            // Scope of the identifier (e.g., global or function name)
    int itemUsed;              // Flag indicating if the identifier is used
};

struct Entry symTabItems[100]; // Array to hold symbol table entries
int symTabIndex = 0;           // Tracks the current index in the symbol table
int SYMTAB_SIZE = 20;          // Maximum size of the symbol table

void addItem(char itemName[50], char itemKind[8], char itemType[8], char scope[50]) {
    // Adds a new item to the symbol table
    symTabItems[symTabIndex].itemID = symTabIndex;
    strcpy(symTabItems[symTabIndex].itemName, itemName);
    strcpy(symTabItems[symTabIndex].itemKind, itemKind);
    strcpy(symTabItems[symTabIndex].itemType, itemType);
    strcpy(symTabItems[symTabIndex].itemValue, "NULL");
    strcpy(symTabItems[symTabIndex].scope, scope);
    symTabItems[symTabIndex].itemUsed = 0;
    symTabIndex++;
}

void showSymTable() {
    // Displays all entries in the symbol table
    printf("    ID        Name        Kind        Type      Value      Scope    \n");
    printf("----------------------------------------------------------------------------\n");
    for (int i = 0; i < symTabIndex; i++) {
        printf("%5d  %10s  %10s  %10s %10s %10s \n", 
               symTabItems[i].itemID, 
               symTabItems[i].itemName, 
               symTabItems[i].itemKind, 
               symTabItems[i].itemType, 
               symTabItems[i].itemValue, 
               symTabItems[i].scope);
    }
    printf("----------------------------------------------------------------------------\n");
}

int found(char itemName[50], char scope[50]) {
    // Checks if an identifier exists in the symbol table
    for (int i = 0; i < SYMTAB_SIZE; i++) {
        int isGlobal = strcmp(symTabItems[i].scope, "GLOBAL");
        int str1 = strcmp(symTabItems[i].itemName, itemName);
        int str2 = strcmp(symTabItems[i].scope, scope);

        if (str1 == 0 && (str2 == 0 || isGlobal == 0)) {
            return 1; // Identifier found
        }
    }
    return 0; // Identifier not found
}

int getSymTabIndex() {
    // Returns the current index of the symbol table
    return symTabIndex;
}

int setItemValue(char itemName[50], char itemValue[8], char scope[50]) {
    // Sets the value of a specific identifier in the symbol table
    for (int i = 0; i < SYMTAB_SIZE; i++) {
        int isGlobal = strcmp(symTabItems[i].scope, "GLOBAL");
        int str1 = strcmp(symTabItems[i].itemName, itemName);
        int str2 = strcmp(symTabItems[i].scope, scope);

        if (str1 == 0 && (isGlobal == 0 || str2 == 0)) {
            strcpy(symTabItems[i].itemValue, itemValue);
            printf("\nSetting value of %s to %s ---->\n\n", itemName, itemValue);
            return 1; // Value set successfully
        }
    }
    printf("ERROR: Item %s was not found\n", itemName);
    return 0; // Identifier not found
}

int setItemUsed(char itemName[50], char scope[50]) {
    // Marks an identifier as used in the symbol table
    for (int i = 0; i < SYMTAB_SIZE; i++) {
        int isGlobal = strcmp(symTabItems[i].scope, "GLOBAL");
        int str1 = strcmp(symTabItems[i].itemName, itemName);
        int str2 = strcmp(symTabItems[i].scope, scope);

        if (str1 == 0 && (isGlobal == 0 || str2 == 0)) {
            symTabItems[i].itemUsed = 1;
            return 1; // Identifier marked as used
        }
    }
    printf("Item %s was not found\n", itemName);
    return 0; // Identifier not found
}

char* getValue(char itemName[50], char scope[50]) {
    // Retrieves the value of a given identifier
    for (int i = 0; i < 100 - 1; i++) {
        int isGlobal = strcmp(symTabItems[i].scope, "GLOBAL");
        int str1 = strcmp(symTabItems[i].itemName, itemName);
        int str2 = strcmp(symTabItems[i].scope, scope);

        if (str1 == 0 && str2 == 1) {
            printf("ERROR: variable %s does not exist in this scope %s.", itemName, scope);
        }
        if (str1 == 0 && (str2 == 0 || isGlobal == 0)) {
            return symTabItems[i].itemValue;
        }
    }
    return "NULL"; // Identifier not found
}

int getItemID(char itemName[50], char scope[50]) {
    // Retrieves the ID of a given identifier
    for (int i = 0; i < 100; i++) {
        int isGlobal = strcmp(symTabItems[i].scope, "GLOBAL");
        int str1 = strcmp(symTabItems[i].itemName, itemName);
        int str2 = strcmp(symTabItems[i].scope, scope);

        if (str1 == 0 && (str2 == 0 || isGlobal == 0)) {
            return symTabItems[i].itemID;
        }
    }
    return -1; // Identifier not found
}

char* getVariableType(char itemName[50], char scope[50]) {
    // Retrieves the type of a given identifier
    for (int i = 0; i < SYMTAB_SIZE; i++) {
        int isGlobal = strcmp(symTabItems[i].scope, "GLOBAL");
        int str1 = strcmp(symTabItems[i].itemName, itemName);
        int str2 = strcmp(symTabItems[i].scope, scope);

        if (str1 == 0 && (str2 == 0 || isGlobal == 0)) {
            return symTabItems[i].itemType;
        }
    }
    return NULL; // Identifier not found
}

char* getItemKind(char itemName[50], char scope[50]) {
    // Retrieves the kind of a given identifier
    for (int i = 0; i < SYMTAB_SIZE; i++) {
        int isGlobal = strcmp(symTabItems[i].scope, "GLOBAL");
        int str1 = strcmp(symTabItems[i].itemName, itemName);
        int str2 = strcmp(symTabItems[i].scope, scope);

        if (str1 == 0) {
            return symTabItems[i].itemKind;
        }
    }
    return NULL; // Identifier not found
}

int compareTypes(char itemName1[50], char itemName2[50], char scope[50]) {
    // Compares the types of two identifiers
    const char* idType1 = getVariableType(itemName1, scope);
    const char* idType2 = getVariableType(itemName2, scope);

    printf("%s = %s\n", idType1, idType2);

    return strcmp(idType1, idType2) == 0 ? 1 : 0; // Returns 1 if types match, otherwise 0
}
