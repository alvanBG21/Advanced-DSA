#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

const int MAX_SIZE = 10;
typedef struct Node
{
    int key;
    int value;
    struct Node *next;

} Node;

typedef struct LinkedList
{
    struct Node *head;
} LinkedList;

typedef struct HashT
{
    LinkedList **nodes;
    int capacity;

} HashT;

LinkedList *init()
{
    LinkedList *list = (LinkedList *)malloc(sizeof(LinkedList));
    list->head = NULL;
    return list;
}

int insert(LinkedList *, int, int);

int hash(int n)
{
    return n % MAX_SIZE;
}

HashT *hash_init()
{
    HashT *table = (HashT *)malloc(sizeof(HashT));
    table->capacity = MAX_SIZE;
    table->nodes = malloc(sizeof(LinkedList*) * MAX_SIZE);

    for (int i = 0; i < MAX_SIZE; i++)
    {
        table->nodes[i] = NULL;
    }

    return table;
}

int hash_insert(HashT *table, int data, int value)
{
    int index = hash(data);

    if (table->nodes[index] == NULL)
    {
        LinkedList *list = init();

        if (!list)
            return -1;

        insert(list, data, value);
        table->nodes[index] = list;
        return 1;
    }
    LinkedList *list = table->nodes[index];
    insert(list, data, value);
}

int insert(LinkedList *list, int data, int value)
{
    if (list == NULL)
        return -1;
    Node *node = (Node *)malloc(sizeof(struct Node));

    if (!node)
        return -1;

    node->key = data;
    node->value = value;
    node->next = NULL;

    if (list->head == NULL)
    {
        list->head = node;
        return 1;
    }
    // data is greater than the first item
    if(data == list->head->key){
        printf("duplicate key: %d\n", data);
        return -1;
    }
    if (data < list->head->key)
    {
        node->next = list->head;
        list->head = node;
        return 1;
    }

    Node *cur = list->head;
    while (cur->next)
    {
        if(cur->next->key == data){
            printf("Duplicate key :%d, %d\n",data, cur->next->key);
            return -1;
        }else if (cur->next->key > data){
            break;
        }
        cur = cur->next;
    }
    node->next = cur->next;
    cur->next = node;
    return 1;
}

void print(LinkedList *list)
{
    if (list == NULL)
        return;
    Node *cur = list->head;

    while (cur)
    {
        printf("key: %d, value: %d ", cur->key, cur->value);
        cur = cur->next;
    }
    return;
}

Node *list_find(LinkedList *list, int key)
{
    Node *cur = list->head;
    while (cur)
    {
        if (cur->key == key)
            return cur;
        cur = cur->next;
    }

    return NULL;
}
int get(HashT *table, int key)
{
    int index = hash(key);

    if (table->nodes[index] == NULL)
    {
        printf("key not found");
        return -1;
    }
    LinkedList *list = table->nodes[index];
    Node *node = list_find(list, key);

    if (!node)
    {
        printf("Key not found");
        return -1;
    }
    printf("key: %d, value: %d", node->key, node->value);
    return 1;
}

void print_hashT(HashT *table)
{
    for (int i = 0; i < MAX_SIZE; i++)
    {
        if (table->nodes[i] != NULL)
        {
            printf("List Items @index: %d\n", i);
            print((LinkedList *)table->nodes[i]);
            printf("\n");
        }
    }
}

int main()
{

    HashT *table = hash_init();
    hash_insert(table, 5, 5);
    hash_insert(table, 15, 15);
    hash_insert(table, 15, 25);
    hash_insert(table, 11, 11);
    hash_insert(table, 11, 21);

    print_hashT(table);
    return 0;
}