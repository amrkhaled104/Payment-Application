# Linked List Implementation in C

This project provides an implementation of a singly linked list in C. It includes various operations for managing the list such as insertion, deletion, traversal, and additional functionalities like reversing the list and finding the middle node. 

## Files

- `list.h`: Header file containing declarations of linked list operations and data structures.
- `list.c`: Source file with implementations of the linked list operations.
- `main.c`: Contains a menu-driven program to interact with the linked list and test various functionalities.

## Data Structures

### `DATA`

- `char Name[10]`: Name of the individual.
- `int age`: Age of the individual.

### `listnode`

- `ListEntry entry`: The data element of type `DATA`.
- `struct listnode *Next`: Pointer to the next node in the list.

### `List`

- `listnode *Head`: Pointer to the first node in the list.
- `int size`: Current size of the list.

## Functions

### `void CreateList(List *pl)`

Initializes an empty linked list.

### `int ListEmpty(List *pl)`

Returns 1 if the list is empty, otherwise returns 0.

### `int ListFull(List *pl)`

Returns 0 (since the linked list implementation does not have a fixed size limit).

### `int ListSize(List *pl)`

Returns the number of elements in the list.

### `void DestroyList(List *pl)`

Frees all allocated memory and clears the list.

### `int InsertList(int pos, ListEntry e, List *pl)`

Inserts an element at the given position in the list. Returns 1 if successful, otherwise 0.

### `int DeleteList(int pos, ListEntry *pe, List *pl)`

Deletes the element at the given position and stores the deleted element in `pe`. Returns 1 if successful, otherwise 0.

### `void TraverseList(List *pl, void (*Visit)(ListEntry))`

Traverses the list and applies the `Visit` function to each element.

### `void RetrieveList(int pos, ListEntry *pe, List *pl)`

Retrieves the element at the specified position and stores it in `pe`.

### `void ReplaceList(int pos, ListEntry e, List *pl)`

Replaces the element at the given position with a new element `e`.

### `void ReverseList(List *pl)`

Reverses the order of nodes in the list.

### `void MiddleNode(ListEntry *pe, List *pl)`

Finds the middle node in the list and stores it in `pe`.

### `int SumList(List *pl)`

Calculates and returns the sum of the `age` fields of all nodes in the list.

### `int MaxList(List *pl)`

Finds and returns the maximum `age` value in the list. Returns -1 if the list is empty.

## Example

```sh
-----------------------------------------------
1. Clear the list.
2. Insert an element.
3. Delete an element.
4. What is the list size?
5. Retrieve an element.
6. Replace an element.
7. Print all elements in the list.
8. Reverse the list.
9. Get the middle node.
10. Get the sum of all ages.
11. Get the maximum age.
12. Exit.
-----------------------------------------------

Enter Your Order: 
```

Follow the prompts to interact with the linked list.

## Notes

- The `Name` field in `DATA` is limited to 10 characters.
- Error handling is provided for edge cases such as empty lists.
