#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

// Structure for a binary tree node
typedef struct Node {
    int data;
    struct Node* left;
    struct Node* right;
} Node;

// Function to create a new node
Node* createNode(int value) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    if (newNode == NULL) {
        printf("Memory allocation failed\n");
        exit(1);
    }
    newNode->data = value;
    newNode->left = NULL;
    newNode->right = NULL;
    return newNode;
}

// Function to insert a value into the BST
Node* insert(Node* root, int value) {
    if (root == NULL) return createNode(value);

    if (value < root->data)
        root->left = insert(root->left, value);
    else if (value > root->data)
        root->right = insert(root->right, value);

    return root;
}

// Function to find the node with minimum value
Node* findMin(Node* root) {
    if (root == NULL) return NULL;

    while (root->left != NULL) root = root->left;

    return root;
}

// Function to delete a node from the BST
Node* deleteNode(Node* root, int value) {
    if (root == NULL) return root;

    if (value < root->data)
        root->left = deleteNode(root->left, value);
    else if (value > root->data)
        root->right = deleteNode(root->right, value);
    else {
        // Node with only one child or no child
        if (root->left == NULL) {
            Node* temp = root->right;
            free(root);
            return temp;
        } else if (root->right == NULL) {
            Node* temp = root->left;
            free(root);
            return temp;
        }

        // Node with two children
        Node* temp = findMin(root->right);
        root->data = temp->data;
        root->right = deleteNode(root->right, temp->data);
    }
    return root;
}

// Function to perform in-order traversal
void inOrderTraversal(Node* root) {
    if (root != NULL) {
        inOrderTraversal(root->left);
        printf("%d ", root->data);
        inOrderTraversal(root->right);
    }
}

// Function to search for a value
bool search(Node* root, int value) {
    if (root == NULL) return false;

    if (root->data == value) return true;

    if (value < root->data)
        return search(root->left, value);
    else
        return search(root->right, value);
}

// Function to free the memory of the tree
void freeTree(Node* root) {
    if (root != NULL) {
        freeTree(root->left);
        freeTree(root->right);
        free(root);
    }
}

// Main function to demonstrate the binary tree operations
int main() {
    Node* root = NULL;

    // Insert elements
    root = insert(root, 50);
    insert(root, 30);
    insert(root, 20);
    insert(root, 40);
    insert(root, 70);
    insert(root, 60);
    insert(root, 80);

    printf("In-order traversal: ");
    inOrderTraversal(root);
    printf("\n");

    printf("Deleting 20\n");
    root = deleteNode(root, 20);
    printf("In-order traversal: ");
    inOrderTraversal(root);
    printf("\n");

    printf("Searching for 40: %s\n", search(root, 40) ? "Found" : "Not found");
    printf("Searching for 100: %s\n",
           search(root, 100) ? "Found" : "Not found");

    // Free the memory
    freeTree(root);

    return 0;
}