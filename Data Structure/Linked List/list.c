#include "list.h"
#include <stdlib.h>
#include <stdio.h>

void CreateList(List *pl) {
    pl->Head = NULL;
    pl->size = 0;
}

int ListEmpty(List *pl) {
    return pl->size == 0;
}

int ListFull(List *pl) {
    return 0; // For linked lists, we assume it can grow as needed.
}

int ListSize(List *pl) {
    return pl->size;
}

void DestroyList(List *pl) {
    listnode *Help;
    while (pl->Head) {
        Help = pl->Head->Next;
        free(pl->Head);
        pl->Head = Help;
    }
    pl->size = 0;
}

int InsertList(int pos, ListEntry e, List *pl) {
    listnode *Help, *pNew;
    
    if ((pNew = (listnode *)malloc(sizeof(listnode)))) {
        pNew->entry = e;
        pNew->Next = NULL;
        if (pos == 0) {
            pNew->Next = pl->Head;
            pl->Head = pNew;
        } else {
            if (pos <= pl->size) {
                Help = pl->Head;
                for (int i = 0; i < pos - 1; i++) {
                    Help = Help->Next;
                }
                pNew->Next = Help->Next;
                Help->Next = pNew;
            } else {
                free(pNew);
                return 0;
            }
        }
        pl->size++;
        return 1;
    } else {
        return 0;
    }
}

int DeleteList(int pos, ListEntry *pe, List *pl) {
    listnode *Help1, *Help2;
    if (pl->Head != NULL) {
        if (pos == 0) {
            *pe = pl->Head->entry;
            Help1 = pl->Head->Next;
            free(pl->Head);
            pl->Head = Help1;
        } else {
            Help2 = pl->Head;
            for (int i = 0; i < pos - 1; i++) {
                Help2 = Help2->Next;
            }
            *pe = Help2->Next->entry;
            Help1 = Help2->Next->Next;
            free(Help2->Next);
            Help2->Next = Help1;
        }
        pl->size--;
        return 1;
    } else {
        return 0;
    }
}

void TraverseList(List *pl, void (*Visit)(ListEntry)) {
    listnode *p = pl->Head;
    while (p) {
        (*Visit)(p->entry);
        p = p->Next;
    }
}

void RetrieveList(int pos, ListEntry *pe, List *pl) {
    listnode *Help2 = pl->Head;
    for (int i = 0; i < pos; i++) {
        Help2 = Help2->Next;
    }
    *pe = Help2->entry;
}

void ReplaceList(int pos, ListEntry e, List *pl) {
    listnode *Help2 = pl->Head;
    for (int i = 0; i < pos; i++) {
        Help2 = Help2->Next;
    }
    Help2->entry = e;
}

void ReverseList(List *pl) {
    listnode *prev = NULL, *current = pl->Head, *next = NULL;

    while (current != NULL) {
        next = current->Next;
        current->Next = prev;
        prev = current;
        current = next;
    }
    pl->Head = prev;
}

void MiddleNode(ListEntry *pe, List *pl) {
    listnode *Help2 = pl->Head;
    int pos = (pl->size) / 2;
    for (int i = 0; i < pos; i++) {
        Help2 = Help2->Next;
    }
    *pe = Help2->entry;
}

int SumList(List *pl) {
    int sum = 0;
    listnode *current = pl->Head;
    
    while (current != NULL) {
        sum += current->entry.age; // Assuming we're summing the 'age' field
        current = current->Next;
    }
    
    return sum;
}

int MaxList(List *pl) {
    if (pl->Head == NULL) {
        printf("The list is empty.\n");
        return -1; // Indicating an error
    }

    int max = pl->Head->entry.age; // Start with the first element
    listnode *current = pl->Head->Next;
    
    while (current != NULL) {
        if (current->entry.age > max) {
            max = current->entry.age;
        }
        current = current->Next;
    }
    
    return max;
}
