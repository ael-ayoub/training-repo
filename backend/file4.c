#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Node {
    char key[16];
    int value;
    struct Node *next;
} Node;

#define TABLE_SIZE 32
static Node *table[TABLE_SIZE];

unsigned int hash(const char *key) {
    unsigned int h = 5381;
    while (*key) {
        h = ((h << 5) + h) + (unsigned char)(*key++);
    }
    return h % TABLE_SIZE;
}

void table_set(const char *key, int value) {
    unsigned int idx = hash(key);
    Node *node = table[idx];
    while (node) {
        if (strcmp(node->key, key) == 0) {
            node->value = value;
            return;
        }
        node = node->next;
    }

    Node *new_node = malloc(sizeof(Node));
    snprintf(new_node->key, sizeof(new_node->key), "%s", key);
    new_node->value = value;
    new_node->next = table[idx];
    table[idx] = new_node;
}

int table_get(const char *key, int *out) {
    unsigned int idx = hash(key);
    Node *node = table[idx];
    while (node) {
        if (strcmp(node->key, key) == 0) {
            *out = node->value;
            return 0;
        }
        node = node->next;
    }
    return -1;
}

int main(void) {
    table_set("alpha", 10);
    table_set("beta", 20);
    table_set("gamma", 30);

    int result;
    if (table_get("beta", &result) == 0) {
        printf("beta = %d\n", result);
    }

    return 0;
}
