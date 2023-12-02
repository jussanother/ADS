#include <stdio.h>
#include <stdlib.h>

#define TABLE_SIZE 10

// Node structure for linked list (used for collision resolution)
struct Node {
    int key;
    struct Node* next;
};

// Hash table structure
struct HashTable {
    struct Node* table[TABLE_SIZE];
};

// Hash function using the division method
int division_hash(int key) {
    return key % TABLE_SIZE;
}

// Insert a key into the hash table
void insert(struct HashTable* hashTable, int key) {
    // Create a new node for the key
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
    newNode->key = key;
    newNode->next = NULL;

    // Calculate hash value using the division method
    int hashValue = division_hash(key);

    // Handle collisions using separate chaining
    if (hashTable->table[hashValue] == NULL) {
        // No collision, insert the node
        hashTable->table[hashValue] = newNode;
    } else {
        // Collision occurred, add the node to the linked list
        struct Node* current = hashTable->table[hashValue];
        while (current->next != NULL) {
            current = current->next;
        }
        current->next = newNode;
    }
}

// Print the contents of the hash table
void printHashTable(struct HashTable* hashTable) {
    for (int i = 0; i < TABLE_SIZE; i++) {
        printf("%d: ", i);
        struct Node* current = hashTable->table[i];
        while (current != NULL) {
            printf("%d -> ", current->key);
            current = current->next;
        }
        printf("NULL\n");
    }
}

int main() {
    struct HashTable hashTable;

    // Initialize the hash table
    for (int i = 0; i < TABLE_SIZE; i++) {
        hashTable.table[i] = NULL;
    }

    // Insert keys into the hash table
    insert(&hashTable, 5);
    insert(&hashTable, 15);
    insert(&hashTable, 25);
    insert(&hashTable, 6);
    insert(&hashTable, 16);
    insert(&hashTable, 26);
    insert(&hashTable, 7);
    insert(&hashTable, 17);
    insert(&hashTable, 27);

    // Print the contents of the hash table
    printHashTable(&hashTable);

    return 0;
}
