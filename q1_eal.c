#include <stdio.h>
#include <stdlib.h>

int isEqual(char *str1, char *str2);
int getIndex(char **matrix, char *str, int size);

struct Item {
        float price;
        int quantity;
        char *name;
};

struct Node {
        struct Item item;
        struct Node *nextNode;
};

struct List {
        struct Node head;
        int size;
};


int main(void)
{
        // userInput needs instant allocation, otherwise it will point to NULL
        char *usrCmd = malloc(sizeof("REMOVERGRUPO"));
        // Both variables below initialized with -1 so we know if 
        // it was reasigned later.
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

        scanf("%s %f %d", usrCmd, &price, &quantity);
        int index = getIndex(cmds, usrCmd, 5);

        printf("Input: %s\n", usrCmd);
        printf("Price: %f\n", price);
        printf("Quantity: %d\n", quantity);

        // TODO: Create functions to work with the linked list
        // insert(char *name, float price, int quantity)
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

        if (list != NULL) {
                list->size = 0;
        }
        
        return list;
}

/*
 * Inserts Node in a given index of the list
 * 
 * struct List *list: pointer to struct List
 * int value: integer value to be added to the list
 * int index: index to insert the value
 * 
 * Returns 0 if the insertion was successfull. Otherwise returns 1.
*/
int insertNode(struct List *list, struct Item item, int index)
{
        struct Node *newNode, *current;
        newNode = (struct Node*)malloc(sizeof(struct Node));
        node->item;

        if (index > list->size) {
                return 1;
        }

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
        list->size++
        
        return 0
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
int getIndex(char **matrix, char *str, int size)
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