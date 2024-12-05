//Symbol table header
#include <string.h>
#define GREEN   "\x1b[32m"
#define BGREEN  "\x1b[1;32m"
#define RED     "\x1b[1;31m"
#define ORANGE     "\x1b[33m"
#define BORANGE "\x1b[1;33m"
#define PINK    "\x1b[95m"
#define BPINK    "\x1b[1;95m"
#define BLUE    "\x1b[34m"
#define BBLUE   "\x1b[1;94m"
#define CYAN    "\x1b[96m"
#define BCYAN    "\x1b[1;96m"
#define BYELLOW "\x1b[1;103m"
#define GRAY    "\x1b[90m"
#define BOLD    "\e[1;37m"
#define RESET   "\x1b[0m"

struct Entry
{
	int itemID;
	char itemName[50];  //the name of the identifier
	char itemKind[8];  //is it a function or a variable?
	char itemType[8];  // Is it int, char, etc.?
    char itemValue[25];
	char scope[50];     // global, or the name of the function
	int itemUsed;
};

struct Entry symTabItems[100];
int symTabIndex = 0;
int SYMTAB_SIZE = 20;

void symTabAccess(void){
	printf(GRAY "::::> Symbol table accessed.\n\n" RESET);
}

void addItem(char itemName[50], char itemKind[8], char itemType[8], char scope[50]){
	

		// what about scope? should you add scope to this function?
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
	printf("itemID    itemName    itemKind    itemType  itemValue  itemSope    itemUsed?\n");
	printf("----------------------------------------------------------------------------\n");
	for (int i=0; i<symTabIndex; i++){
		printf("%5d  %10s  %10s  %10s %10s %10s %10d \n",symTabItems[i].itemID, symTabItems[i].itemName, symTabItems[i].itemKind, symTabItems[i].itemType, symTabItems[i].itemValue, symTabItems[i].scope, symTabItems[i].itemUsed);
	}	

	printf("----------------------------------------------------------------------------\n\n");
}

int found(char itemName[50], char scope[50]) {
    // Lookup an identifier in the symbol table
    // what about scope?
    // return TRUE or FALSE
    // Later on, you may want to return additional information

    // Dirty loop, becuase it counts SYMTAB_SIZE times, no matter the size of the symbol table

    for(int i=0; i < SYMTAB_SIZE; i++){

		int isGlobal = strcmp(symTabItems[i].scope, "GLOBAL");

        int str1 = strcmp(symTabItems[i].itemName, itemName);
        //printf("\n\n---------> str1=%d: COMPARED: %s vs %s\n\n", str1, symTabItems[i].itemName, itemName);

        int str2 = strcmp(symTabItems[i].scope,scope);
        //printf("\n\n---------> str2=%d: COMPARED %s vs %s\n\n", str2, symTabItems[i].itemName, itemName);

        if( str1 == 0 && (str2 == 0 || isGlobal == 0)) {
            return 1; // found the ID in the table
        }
    }

    return 0;
}

int getSymTabIndex() {
    return symTabIndex; //Genius method for index retrieval: copyright Evan Kliwer
}

// Adds value to an ID in the symbol table
int setItemValue(char itemName[50], char itemValue[8], char scope[50]) {
	
	for (int i = 0; i < SYMTAB_SIZE; i++) {
		int isGlobal = strcmp(symTabItems[i].scope, "GLOBAL");
		int str1 = strcmp(symTabItems[i].itemName, itemName); 
		int str2 = strcmp(symTabItems[i].scope,scope);
		
		if (str1 == 0 && (isGlobal == 0 || str2 == 0)) {
			strcpy(symTabItems[i].itemValue, itemValue);
			printf(BGREEN"\nSetting value of %s to %s ---->\n\n"RESET, symTabItems[i].itemName, itemValue);
			showSymTable();
			return 1; //value added 
		}
	}

	printf(RED"ERROR: Item %s was not found\n" RESET, itemName);	
	return 0;
}

int setItemUsed(char itemName[50],  char scope[50]) {
	
	for (int i = 0; i < SYMTAB_SIZE; i++) {
		int isGlobal = strcmp(symTabItems[i].scope, "GLOBAL");
		int str1 = strcmp(symTabItems[i].itemName, itemName); 
		int str2 = strcmp(symTabItems[i].scope,scope);
		
		if (str1 == 0 && (isGlobal == 0 || str2 == 0)) {
			symTabItems[i].itemUsed = 1;
			showSymTable();
			return 1; //value added 
		}
	}

	printf("Item %s was not found\n", itemName);	
	return 0;
}

// Returns the value of a given ID
char *getValue(char itemName[50], char scope[50]) {

	for(int i=0; i<100-1; i++) { 
		int isGlobal = strcmp(symTabItems[i].scope, "GLOBAL");
		int str1 = strcmp(symTabItems[i].itemName, itemName);
		int str2 = strcmp(symTabItems[i].scope,scope);

		//If the variable is referenced in the wrong scope, we print a message and then cry
		if (str1 == 0 && str2 == 1){
			printf("ERROR: variable %s does not exist in this scope %s.",itemName,scope);
		}

		if( str1 == 0 && (str2 == 0 || isGlobal == 0)){
			// printf("Item Value:%s\n", symTabItems[i].itemValue);
			return symTabItems[i].itemValue;
		}
	}

	return "NULL"; //item not found;
}

// Returns the ID of a given itemName
int getItemID(char itemName[50], char scope[50]) {

	for(int i=0; i<100; i++) {
		int isGlobal = strcmp(symTabItems[i].scope, "GLOBAL");
		int str1 = strcmp(symTabItems[i].itemName, itemName);
		int str2 = strcmp(symTabItems[i].scope, scope);
		if( str1 == 0 && (str2 == 0 || isGlobal == 0)){
			return symTabItems[i].itemID;
		}
	}

	return -1; //item not found
}

char* getVariableType(char itemName[50], char scope[50]){
    //char *name = "int";
    //return name;
    for(int i=0; i<SYMTAB_SIZE; i++){
		int isGlobal = strcmp(symTabItems[i].scope, "GLOBAL");
        int str1 = strcmp(symTabItems[i].itemName, itemName);
        //printf("\n\n---------> str1=%d: COMPARED: %s vs %s\n\n", str1, symTabItems[i].itemName, itemName);
        int str2 = strcmp(symTabItems[i].scope,scope);
        //printf("\n\n---------> str2=%d: COMPARED %s vs %s\n\n", str2, symTabItems[i].itemName, itemName);
        if( str1 == 0 && (str2 == 0 || isGlobal == 0)){
			// printf("Debug: %s\n\n", symTabItems[i].itemType);
            return symTabItems[i].itemType; 
        }
    }
    return NULL;// ID not found in the table
}

char* getItemKind(char itemName[50], char scope[50]){
    //char *name = "int";
    //return name;
    for(int i=0; i<SYMTAB_SIZE; i++){

		int isGlobal = strcmp(symTabItems[i].scope, "GLOBAL");
        int str1 = strcmp(symTabItems[i].itemName, itemName);
        int str2 = strcmp(symTabItems[i].scope, scope);

        if(str1 == 0) {
            return symTabItems[i].itemKind; 
        }
    }
    return NULL;// ID not found in the table
}

int compareTypes(char itemName1[50], char itemName2[50], char scope[50]){
    const char* idType1 = getVariableType(itemName1, scope);
    const char* idType2 = getVariableType(itemName2, scope);
    
    printf("%s = %s\n", idType1, idType2);
    
    int typeMatch = strcmp(idType1, idType2);
    if(typeMatch == 0){
        return 1; // types are matching
    }
    else return 0;
}