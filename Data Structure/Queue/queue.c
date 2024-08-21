
/**
 **********************************************************************************
 * @file           : queue.c >> Linked-Based Implementation
 * @author         : Amr Khaled
 * @brief          : queue.c that consists of the implementation of the functions 
 * @date           : 11/7/2023
 **********************************************************************************
**/
#include <stdlib.h>
#include "queue.h"

//initialize the queue.
void CreatQueue(Queue *pq)
{
	pq->Front = NULL;
	pq->rear = NULL;
	pq->size = 0;
}

//check if the queue is empty or not.
int QueueEmpty(Queue *pq)
{
	return pq->rear==NULL;
	//return !(pq->size);
	//return !(pq->front);
	//return !(pq->rear);
}

//check if the queue is full or not.
int QueueFull(Queue *pq)
{
	return 0;
}

//calculate the number of elements in the queue.
int QueueSize(Queue *pq)
{
	return pq->size;
}

// Clear queue and destroy all elements in it.
void ClearQueue(Queue *pq)
{
    while (pq->Front != NULL) {
        pq->rear = pq->Front->Next;
        free(pq->Front);
		pq->Front=pq->rear;
    }
    pq->size = 0;
}

//append an element to the queue. (FIFO)
void Append(QueueEntry e,Queue *pq)
{
	queuenode *pn=(queuenode *)malloc(sizeof(queuenode ));
	pn->entry=e;
	pn->Next=NULL;
	if(!pq->Front) pq->Front=pn;
	else pq->rear->Next=pn;
	pq->rear=pn;
	pq->size++;
}

//serve an element from the queue. (FIFO)
void Serve(QueueEntry *pe,Queue *pq)
{
	*pe = pq->Front->entry;
	queuenode *pn=pq->Front;
	pq->Front=pq->Front->Next;
	free(pn);
	if(!pq->Front) pq->rear=NULL;
	pq->size--;
}

//get the value of the first element in the queue without change it.
void Retrieve(QueueEntry *pe,Queue *pq)
{
	*pe = pq->Front->entry;
}

//travese queue to do specific function like display all elements in it.
void TraverseQueue(Queue *pq,void (*pf)(QueueEntry))
{
	
	
	for(queuenode*pn=pq->Front; pn;pn=pn->Next)
	{
		(*pf)(pn->entry);
	}
}
