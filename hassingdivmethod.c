#include <stdio.h>
#include <stdlib.h>

#define HASH_TABLE_SIZE 10  // Adjust the size of the hash table as needed

// Hash function using the division method
int division_hash(int key, int table_size) {
    return key % table_size;
}

int main() {
    int key;
    
    printf("Enter a key to hash: ");
    scanf("%d", &key);

    // Calculate the hash using the division method
    int hash_value = division_hash(key, HASH_TABLE_SIZE);

    printf("Hash value for key %d is: %d\n", key, hash_value);

    return 0;
}
