#include <stdio.h>
#include <stdlib.h>

struct hash_node {
    int key;
    int value;
    struct hash_node *next;
};

struct hash_table {
    int size;
    struct hash_node **table;
};

int h(int key, int size) {
    return key % size;
}

void assign(struct hash_table *ht, int key, int value) {
    int index = h(key, ht->size);
    struct hash_node *current = ht->table[index];
    struct hash_node *previous = NULL;
    while (current != NULL) {
        if (current->key == key) {
            current->value = value;
            return;
        }
        previous = current;
        current = current->next;
    }
    struct hash_node *new_node = malloc(sizeof(struct hash_node));
    new_node->key = key;
    new_node->value = value;
    new_node->next = NULL;
    if (previous == NULL) {
        ht->table[index] = new_node;
    } else {
        previous->next = new_node;
    }
}

int at(struct hash_table *ht, int key) {
    int index = h(key, ht->size);
    struct hash_node *current = ht->table[index];
    while (current != NULL) {
        if (current->key == key) {
            return current->value;
        }
        current = current->next;
    }
    return 0;
}

void free_hash_table(struct hash_table *ht) {
    for (int i = 0; i < ht->size; i++) {
        struct hash_node *current = ht->table[i];
        while (current != NULL) {
            struct hash_node *next = current->next;
            free(current);
            current = next;
        }
    }
    free(ht->table);
    free(ht);
}

int main() {
    int m;
    scanf("%i", &m);
    struct hash_table *ht = malloc(sizeof(struct hash_table));
    ht->size = m;
    ht->table = calloc(m, sizeof(struct hash_node *));
    while (1) {
        char operation[7];
        scanf("%s", operation);
        if (operation[0] == 'A' && operation[1] == 'S') {
            int key, value;
            scanf("%i %i", &key, &value);
            assign(ht, key, value);
        } else if (operation[0] == 'E') {
            break;
        } else {
            int key;
            scanf("%i", &key);
            printf("%i\n", at(ht, key));
        }
    }
    free_hash_table(ht);
    return 0;
}
