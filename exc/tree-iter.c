#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

// Tree node structure
typedef struct TreeNode {
    int value;
    struct TreeNode* left;
    struct TreeNode* right;
} TreeNode;

// Stack item structure to hold node and moment
typedef struct StackItem {
    TreeNode* node;
    int moment;
} StackItem;

// Simple stack implementation
typedef struct Stack {
    StackItem* items;
    int top;
    int capacity;
} Stack;

// Create a new stack
Stack* createStack(int capacity) {
    Stack* stack = (Stack*)malloc(sizeof(Stack));
    stack->capacity = capacity;
    stack->top = -1;
    stack->items = (StackItem*)malloc(stack->capacity * sizeof(StackItem));
    return stack;
}

// Check if stack is empty
bool isEmpty(Stack* stack) {
    return stack->top == -1;
}

// Push item to stack
void push(Stack* stack, TreeNode* node, int moment) {
    if (stack->top == stack->capacity - 1) {
        printf("🧨 Stack overflow! Expanding capacity...\n");
        stack->capacity *= 2;
        stack->items = (StackItem*)realloc(stack->items, stack->capacity * sizeof(StackItem));
    }
    
    StackItem item;
    item.node = node;
    item.moment = moment;
    stack->items[++stack->top] = item;
    printf("📥 PUSH: Node %d, Moment %d\n", node->value, moment);
}

// Pop item from stack
StackItem pop(Stack* stack) {
    StackItem item = stack->items[stack->top--];
    printf("📤 POP: Node %d, Moment %d\n", item.node->value, item.moment);
    return item;
}

// Print the current stack content
void printStack(Stack* stack) {
    printf("\n📊 STACK: ");
    if (isEmpty(stack)) {
        printf("(empty)");
    } else {
        for (int i = 0; i <= stack->top; i++) {
            printf("(%d,%d)", stack->items[i].node->value, stack->items[i].moment);
            if (i < stack->top) printf(", ");
        }
    }
    printf("\n");
}

// Create a new tree node
TreeNode* createNode(int value) {
    TreeNode* node = (TreeNode*)malloc(sizeof(TreeNode));
    node->value = value;
    node->left = NULL;
    node->right = NULL;
    return node;
}

// In-order traversal without recursion
void inOrderTraversalNonRecursive(TreeNode* root) {
    if (root == NULL) {
        printf("🌱 Tree is empty. Nothing to traverse!\n");
        return;
    }
    
    // Create a stack with initial capacity
    Stack* stack = createStack(10);
    int* result = (int*)malloc(100 * sizeof(int)); // Assuming max 100 nodes
    int resultIdx = 0;
    
    printf("🚀 Starting in-order traversal\n");
    // Push root node with moment 1
    push(stack, root, 1);
    
    while (!isEmpty(stack)) {
        printStack(stack);
        
        StackItem item = pop(stack);
        TreeNode* node = item.node;
        int moment = item.moment;
        
        if (moment == 1) {
            // Push the same node with moment 2
            push(stack, node, 2);
            
            // If there's a left child, push it with moment 1
            if (node->left) {
                push(stack, node->left, 1);
            } else {
                printf("🍃 No left child for node %d\n", node->value);
            }
        } else if (moment == 2) {
            // Visit the node in moment 2 (in-order traversal)
            result[resultIdx++] = node->value;
            printf("🎯 VISIT: Node %d\n", node->value);
            
            // If there's a right child, push it with moment 1
            if (node->right) {
                push(stack, node->right, 1);
            } else {
                printf("🍃 No right child for node %d\n", node->value);
            }
        }
        // No action for moment 3 in in-order traversal
    }
    
    printf("\n✅ In-order traversal complete!\n");
    printf("🔢 Result: ");
    for (int i = 0; i < resultIdx; i++) {
        printf("%d", result[i]);
        if (i < resultIdx - 1) printf(", ");
    }
    printf("\n");
    
    // Clean up
    free(stack->items);
    free(stack);
    free(result);
}

int main() {
    // Create the example tree
    TreeNode* root = createNode(10);
    root->left = createNode(8);
    root->left->right = createNode(12);
    root->right = createNode(7);
    
    /*
         10
        /  \
       8    7
        \
         12
    */
    
    inOrderTraversalNonRecursive(root);
    
    // Clean up the tree (to avoid memory leaks)
    free(root->left->right);
    free(root->left);
    free(root->right);
    free(root);
    
    return 0;
}