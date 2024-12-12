#include <string.h>
#include <stdlib.h>
#include <stdio.h>

// Structure representing an Abstract Syntax Tree (AST) node
struct AST {
    char nodeType[50];     // Type of the node (e.g., assignment, binary expression)
    char LHS[50];          // Left-hand side (e.g., variable name)
    char RHS[50];          // Right-hand side (e.g., expression or value)

    struct AST* left;      // Pointer to the left child node
    struct AST* right;     // Pointer to the right child node
};

// Creates an AST node for an assignment operation
struct AST* AST_assignment(char nodeType[50], char LHS[50], char RHS[50]) {
    struct AST* ASTassign = malloc(sizeof(struct AST));
    strcpy(ASTassign->nodeType, nodeType);
    strcpy(ASTassign->LHS, LHS);
    strcpy(ASTassign->RHS, RHS);

    return ASTassign;
}

// Creates an AST node for a binary expression
struct AST* AST_BinaryExpression(char nodeType[50], char LHS[50], char RHS[50]) {
    struct AST* ASTBinExp = malloc(sizeof(struct AST));
    strcpy(ASTBinExp->nodeType, nodeType);
    strcpy(ASTBinExp->LHS, LHS);
    strcpy(ASTBinExp->RHS, RHS);

    return ASTBinExp;
}

// Creates an AST node representing a data type
struct AST* AST_Type(char nodeType[50], char LHS[50], char RHS[50]) {
    struct AST* ASTtype = malloc(sizeof(struct AST));
    strcpy(ASTtype->nodeType, nodeType);
    strcpy(ASTtype->LHS, LHS);
    strcpy(ASTtype->RHS, RHS);

    return ASTtype;
}

// Creates an AST node for a function representation
struct AST* AST_Func(char nodeType[50], char LHS[50], char RHS[50]) {
    struct AST* ASTfunc = malloc(sizeof(struct AST));
    strcpy(ASTfunc->nodeType, nodeType);
    strcpy(ASTfunc->LHS, LHS);
    strcpy(ASTfunc->RHS, RHS);

    return ASTfunc;
}

// Creates an AST node for a write operation
struct AST* AST_Write(char nodeType[50], char LHS[50], char RHS[50]) {
    struct AST* ASTwrite = malloc(sizeof(struct AST));
    strcpy(ASTwrite->nodeType, nodeType);
    strcpy(ASTwrite->LHS, LHS);
    strcpy(ASTwrite->RHS, RHS);

    return ASTwrite;
}

// Helper function to print indentation for tree levels
void printDots(int num) {
    for (int i = 0; i < num; i++) {
        printf("      ");
    }
}

// Recursively prints an AST with proper indentation
void printAST(struct AST* tree, int level) {
    if (tree == NULL) return;

    printDots(level);
    printf("%s\n", tree->nodeType);  // Print node type

    printDots(level);
    printf("%s %s\n", tree->LHS, tree->RHS);  // Print left and right-hand sides

    // Recursively print right and left subtrees
    if (tree->right != NULL) {
        printAST(tree->right, level + 1);
    } else {
        return;
    }

    if (tree->left != NULL) {
        printAST(tree->left, level + 1);
    } else {
        return;
    }
}

// Prints details of a single AST node
void printNode(struct AST* node) {
    printf("Current node ---->\n");

    printDots(3);
    printf("%s\n", node->nodeType);  // Print node type

    printDots(3);
    printf("%s %s\n\n", node->LHS, node->RHS);  // Print left and right-hand sides
}
