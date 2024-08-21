/**
 **********************************************************************************
 * @file           : queue.h >> Linked-Based Implementation
 * @author         : Amr Khaled
 * @brief          : queue.h that consists of the prototypes of the functions 
 *                   with the definition of the queue element type QueueEntry 
 * @date           : 11/7/2024
 **********************************************************************************
**/

#ifndef _QUEUE_H_
#define _QUEUE_H_


// Define the queue element type
typedef struct DATA {
    char Name[20];
    int id;
} DATA;

typedef DATA QueueEntry;

// Define the queueNode structure
typedef struct queuenode {

    QueueEntry entry;
	struct queuenode *Next;
} queuenode;
// Define the queue structure
typedef struct queue {
     queuenode *Front;
     queuenode *rear;
	 int size;
} Queue;

// Function prototypes

// Function to create a new queue
void CreatQueue(Queue *q);

// Function to check if the queue is empty
int QueueEmpty(Queue *q);

// Function to check if the queue is full
int QueueFull(Queue *q);

// Function to get the size of the queue (number of elements in the queue)
int QueueSize(Queue *q);

// Function to clear all elements from the queue
void ClearQueue(Queue *q);

// Function to add a new element to the queue
void Append(QueueEntry item, Queue *q);

// Function to remove the element at the front of the queue
void Serve(QueueEntry *item, Queue *q);

// Function to retrieve the element at the front of the queue without removing it
void Retrieve(QueueEntry *item, Queue *q);

// Function to apply a specific procedure to each element in the queue
void TraverseQueue(Queue *q, void (*func)(QueueEntry));

#endif // _QUEUE_H_
