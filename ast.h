

#include <string.h> // Required for string manipulation functions like strcpy

// Define the structure of an Abstract Syntax Tree (AST) node
struct AST {
    char nodeType[50]; // Stores the type of the AST node
    char LHS[50];      // Stores the left-hand side operand
    char RHS[50];      // Stores the right-hand side operand

    struct AST *left;  // Pointer to the left child node
    struct AST *right; // Pointer to the right child node
};

// Function to create an assignment node in the AST
struct AST *AST_assignment(char nodeType[50], char LHS[50], char RHS[50]) {
    struct AST* ASTassign = malloc(sizeof(struct AST)); // Allocate memory for the new AST node
    strcpy(ASTassign->nodeType, nodeType);             // Set the node type
    strcpy(ASTassign->LHS, LHS);                       // Set the left-hand side operand
    strcpy(ASTassign->RHS, RHS);                       // Set the right-hand side operand
    return ASTassign;                                  // Return the newly created node
}

// Function to create a binary expression node in the AST
struct AST *AST_BinaryExpression(char nodeType[50], char LHS[50], char RHS[50]) {
    struct AST* ASTBinExp = malloc(sizeof(struct AST)); // Allocate memory for the new AST node
    strcpy(ASTBinExp->nodeType, nodeType);             // Set the node type
    strcpy(ASTBinExp->LHS, LHS);                       // Set the left-hand side operand
    strcpy(ASTBinExp->RHS, RHS);                       // Set the right-hand side operand
    return ASTBinExp;                                  // Return the newly created node
}

// Function to create a type node in the AST
struct AST *AST_Type(char nodeType[50], char LHS[50], char RHS[50]) {
    struct AST* ASTtype = malloc(sizeof(struct AST));  // Allocate memory for the new AST node
    strcpy(ASTtype->nodeType, nodeType);              // Set the node type
    strcpy(ASTtype->LHS, LHS);                        // Set the left-hand side operand
    strcpy(ASTtype->RHS, RHS);                        // Set the right-hand side operand
    return ASTtype;                                   // Return the newly created node
}

// Function to create a function-related node in the AST
struct AST *AST_Func(char nodeType[50], char LHS[50], char RHS[50]) {
    struct AST* ASTtype = malloc(sizeof(struct AST));  // Allocate memory for the new AST node
    strcpy(ASTtype->nodeType, nodeType);              // Set the node type
    strcpy(ASTtype->LHS, LHS);                        // Set the left-hand side operand
    strcpy(ASTtype->RHS, RHS);                        // Set the right-hand side operand
    return ASTtype;                                   // Return the newly created node
}

// Function to create a write operation node in the AST
struct AST *AST_Write(char nodeType[50], char LHS[50], char RHS[50]) {
    struct AST* ASTtype = malloc(sizeof(struct AST));  // Allocate memory for the new AST node
    strcpy(ASTtype->nodeType, nodeType);              // Set the node type
    strcpy(ASTtype->LHS, LHS);                        // Set the left-hand side operand
    strcpy(ASTtype->LHS, RHS);                        // Possible bug: overwriting LHS with RHS
    return ASTtype;                                   // Return the newly created node
}

// Function to print indentation (dots) based on the level of the tree
void printDots(int num) {
    for (int i = 0; i < num; i++)
        printf("      "); // Print six spaces for each level
}

// Function to print the AST in a structured format
void printAST(struct AST* tree, int level) {
    if (tree == NULL) return;                           // Base case: if the tree is NULL, return
    printDots(level);                                   // Print dots for the current level
    printf("%s\n", tree->nodeType);                    // Print the node type
    printDots(level);                                   // Print dots again for alignment
    printf("%s %s\n", tree->LHS, tree->RHS);           // Print the operands
    if (tree->right != NULL) printAST(tree->right, level + 1); // Recursively print the right subtree
    if (tree->left != NULL) printAST(tree->left, level + 1);   // Recursively print the left subtree
}

// Function to print details of a single node
void printNode(struct AST* node) {
    printf("Current node ---->\n");                    // Header for node details
    printDots(3);                                      // Indentation for the node
    printf("%s\n", node->nodeType);                   // Print the node type
    printDots(3);                                      // Indentation for operands
    printf("%s %s\n\n", node->LHS, node->RHS);        // Print the operands
}

