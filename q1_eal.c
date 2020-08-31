#include <stdio.h>
#include <stdlib.h>

struct Item {
        float price;
        int quantity;
        char *name;
};

struct Node {
        struct Item *item;
        struct Node *nextNode;
};

struct List {
        struct Node *head;
        int size;
};

struct List* createList(void);
void printList(struct List *list);
int isEqual(char *str1, char *str2);
int getIndex(char **matrix, char *str, int size);
int insertNode(struct List *list, struct Item *item, int index);
int removeByQuantity(struct List *list, char *name, int quantity);


int main(void)
{
        struct List *list = createList();
        // usrCmd needs instant allocation, otherwise it will point to NULL
        char *usrCmd = malloc(sizeof("REMOVERGRUPO"));
        // Both variables below initialized with -1 so we'll be able
        // to tell if it was reasigned later.
        char *name;
        float price = -1.0;
        int quantity = -1;

        // cmds is a pointer to a matrix of pointers (pointer to a pointer)
        char *cmds[5] = {
                "INSERIR",
                "REMOVER",
                "REMOVERGRUPO",
                "CONSULTAR",
                "PROCURAR",
        };

        // scanf("%s %s %f %d", usrCmd, name, &price, &quantity);
        scanf("%s", usrCmd);
        int index = getIndex(cmds, usrCmd, 5);

        if (index == 0) {
                scanf("%s %f %d", name, &price, &quantity);
                struct Item *item = (struct Item*)malloc(sizeof(struct Item));
                item->name = name;
                item->price = price;
                item->quantity = quantity;
                insertNode(list, item, 0);
                printList(list);
        } else if (index == 1) {
                scanf("%s %d", name, &quantity);
                removeByQuantity(list, name, quantity);
        } else if (index == 2) {
                scanf("%f", &price);
                removeByGroup(list, price);
        }
}

/*
 * Creates an empty List
 * 
 * Returns: pointer to List
*/
struct List* createList(void)
{
        struct List *list;
        list = (struct List*)malloc(sizeof(struct List));

        if (list != NULL)
                list->size = 0;
        
        
        return list;
}

/*
 * Inserts Node at a given index of the list
 * 
 * struct List *list: pointer to struct list
 * int value: integer value to be added to the list
 * int index: index to insert the value
 * 
 * Returns 1 if the insertion was successfull. Otherwise returns 0.
*/
int insertNode(struct List *list, 
               struct Item  *item, 
               int          index)
{
        struct Node *newNode, *current;
        newNode = (struct Node*)malloc(sizeof(struct Node));
        newNode->item = item;

        if (index > list->size)
                return 0;
        
        if (index == 0) {
                newNode->nextNode = list->head;
                list->head = newNode;
        } else {
                current = list->head;
        
                for (int i = 0; i < index - 1; i++) {
                        current = current->nextNode;
                }

                newNode->nextNode = current->nextNode;
                current->nextNode = newNode;
        }
        list->size++;
        
        return 1;
};

/*
 * Removes node that contains the item's name. 
 * 
 * Returns: list size after the function execution
*/
int removeNode(struct List *list, char *name)
{       
        struct Node *prev = NULL;
        struct Node *current = list->head;

        while (current) {
                if (isEqual(current->item->name, name)) {
                        // if prev is NULL
                        if (!prev) {
                                list->head = current->nextNode;
                                current->nextNode = NULL;
                        } else {
                                prev->nextNode = current->nextNode;
                                current->nextNode = NULL;
                        }
                        list->size--;
                }
                prev = current;
                current = current->nextNode;
                
        }

        return list->size;
};

/*
 * Reduces the item's quantity by quantity requested
 * 
 * Returns: 1 if item was removed, otherwise 0.
*/
int removeByQuantity(struct List *list, char *name, int quantity)
{       
        int wasRemoved = 0;
        struct Node *current = list->head;

        while (current) {
                if (isEqual(current->item->name, name)) {
                        current->item->quantity -= quantity;
                        wasRemoved = 1;
                        break;
                }
                current = current->nextNode;
                
        }

        return wasRemoved;
};

/*
 * Removes all items with individual price bigger than
 * the one provided by the user.
 * 
 * Returns: Number of itens removed
*/
int removeByGroup(struct List *list, float price) {
        int itensRemoved = 0;
        struct Node *current = list->head;

        while (current) {
                if (price > current->price) {
                        removeNode(list, current->name);
                        itensRemoved += 1;
                }
                current = current->nextNode;
        }

        return itensRemoved;
}


/*
 * Compares str1 and str2 to see if they are equal
 * 
 * char *str1: pointer to string to be compared against
 * char *str2: pointer to string to be compared with
 * 
 * Returns: 1 if they are equal, otherwise 0.
*/
int isEqual(char *str1, char *str2)
{
        while (*str1 && *str1 == *str2) {
                str1++;
                str2++;
        }
        return *str1 - *str2 == 0 ? 1 : 0;
};

/*
 * Gets index of given String inside a matrix of Strings
 * 
 * returns: the index of the given String. If String is not
 *          found, returns -1.
*/
int getIndex(char **matrix, 
             char  *str, 
             int    size)
{
        int index = -1;
        int i = 0;

        while (i < size) {
                if (isEqual(*matrix, str)) {     
                        index = i;
                        break; 
                }
                i++;
                matrix++;
        }

        return index;
};

/*
 * Prints string representation of the list
*/
void printList(struct List *list)
{
        struct Node *current = list->head;

        while(current) {
                char *name = current->item->name;
                int quantity = current->item->quantity;
                float price = current->item->price;
                printf("%s : %d : %.2f ===>", name, quantity, price);
                current = current->nextNode;
        }
        printf("\n");
}
