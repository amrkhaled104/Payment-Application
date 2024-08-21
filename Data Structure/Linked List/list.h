#ifndef LIST_H
#define LIST_H

typedef struct DATA {
    char Name[10];
    int age;
} DATA;

typedef DATA ListEntry;

typedef struct listnode {
    ListEntry entry;
    struct listnode *Next;
} listnode;

typedef struct List {
    listnode *Head;
    int size;
} List;

// Initializes the list to be empty
void CreateList(List *);

// Checks if the list is empty
int ListEmpty(List *);

// Checks if the list is full (for this implementation, it always returns 0)
int ListFull(List *);

// Returns the size of the list
int ListSize(List *);

// Destroys the list and frees all allocated memory
void DestroyList(List *);

// Inserts an entry at the given position
int InsertList(int, ListEntry, List *);

// Deletes an entry at the given position
int DeleteList(int, ListEntry *, List *);

// Traverses the list and applies the Visit function to each entry
void TraverseList(List *, void (*Visit)(ListEntry));

// Retrieves the entry at the given position
void RetrieveList(int, ListEntry *, List *);

// Replaces the entry at the given position with a new entry
void ReplaceList(int, ListEntry, List *);

// Reverses the nodes in a single linked list
void ReverseList(List *);

// Retrieves the middle node of the list
void MiddleNode(ListEntry *, List *);

// Retrieves the maximum age in the list
int MaxList(List *);

// Retrieves the sum of all ages in the list
int SumList(List *);

#endif
