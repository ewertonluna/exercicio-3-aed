/*
 * CESAR SCHOOL
 * ALGORITMOS E ESTRUTURA DE DADOS
 * Ewerton de Araújo Luna
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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
int removeByGroup(struct List *list, float price);
int removeNode(struct List *list, char *name);
void consultList(struct List *list);
void searchItem(struct List *list, char *name);


int main(void)
{
        struct List *list = createList();
        // usrCmd needs instant allocation, otherwise it will point to NULL
        char *usrCmd = malloc(sizeof("REMOVERGRUPO"));
        float price;
        int quantity;

        // cmds is a pointer to a matrix of pointers (pointer to a pointer)
        char *cmds[5] = {
                "INSERIR",
                "REMOVER",
                "REMOVERGRUPO",
                "CONSULTAR",
                "PROCURAR",
        };
        
        while (scanf("%s", usrCmd) != EOF) {
                
                int index = getIndex(cmds, usrCmd, 5);

                if (index == 0) {
                        char *name = malloc(sizeof(char) * 100);
                        scanf("%s %f %d", name, &price, &quantity);
                        struct Item *item = (struct Item*)malloc(sizeof(struct Item));
                        item->name = name;
                        item->price = price;
                        item->quantity = quantity;
                        insertNode(list, item, 0);
                } else if (index == 1) {
                        char *name = malloc(sizeof(char) * 100);
                        scanf("%s %d", name, &quantity);
                        removeByQuantity(list, name, quantity);
                } else if (index == 2) {
                        scanf("%f", &price);
                        removeByGroup(list, price);
                } else if (index == 3) {
                        consultList(list);
                } else if (index == 4) {
                        char *name = malloc(sizeof(char) * 100);
                        scanf("%s", name);
                        searchItem(list, name);
                }

                // printList(list);

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

        // I forgot to initialize head to NULL.
        if (list != NULL)
                list->size = 0;
                // list->head = NULL;
        
        return list;
}

/*
 * Searchs item by a given name and prints its data
 * 
 * 
 * char *name: Item's name to be searched
*/
void searchItem(struct List *list, char *name)
{
        int found = 0;
        struct Node *current = list->head;
        
        while (current) {
                // if (isEqual(current->item->name, name)) {
                if (strcmp(current->item->name, name) == 0) {
                        found = 1;
                        break;
                }
                current = current->nextNode;
        }
        
        if (found) {
                printf("%s\n", current->item->name);
                printf("- %.1f\n", current->item->price);
                printf("- %d\n", current->item->quantity);
        } else {
                printf("%s nao foi encontrado.\n", name);
        }
        printf("\n");
}

/*
 * Prints a message with the total price of the list
*/
void consultList(struct List *list)
{
        float price = 0;
        struct Node *current = list->head;

        for (int i = 0; i < list->size; i++) {
                price += current->item->price * current->item->quantity;
                current = current->nextNode;
        }
        printf("Atualmente a lista esta em R$%.1f\n", price);
        printf("\n");
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
int insertNode(struct List  *list, 
               struct Item  *item, 
               int           index)
{
        struct Node *newNode, *current;
        newNode = malloc(sizeof(struct Node));
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
                // if (isEqual(current->item->name, name)) {
                if (strcmp(current->item->name, name) == 0) {
                        if (!prev) {
                                list->head = current->nextNode;
                                current->nextNode = NULL;
                        } else {
                                prev->nextNode = current->nextNode;
                                current->nextNode = NULL;
                        }
                        list->size--;
                        break;
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
                // if (isEqual(current->item->name, name)) {
                if (strcmp(current->item->name, name) == 0) {
                        current->item->quantity -= quantity;
                        if (current->item->quantity == 0) {
                                removeNode(list, name);
                        }
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
        struct Node *next;

        while (current) {
                if (current->item->price > price) {
                        next = current->nextNode;
                        removeNode(list, current->item->name);
                        // current->nextNode = NULL;
                        itensRemoved += 1;
                }
                
                if (next) {
                        current = next;
                        next = NULL;
                } else {
                        current = current->nextNode;
                }

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
                // if (isEqual(*matrix, str)) {   
                if (strcmp(*matrix, str) == 0) {     
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

        while (current) {
                char *name = current->item->name;
                int quantity = current->item->quantity;
                float price = current->item->price;
                printf("[%s : %d : R$%.2f] ===> ", name, quantity, price);
                current = current->nextNode;
        }
        printf("NULL");
        printf("\n");
}

