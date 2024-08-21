/**
 **********************************************************************************
 * @file           : main.c >> Linked-Based Implementation
 * @author         : Amr Khaled
 * @brief          : main.c that consists test for the implementation level with queue 
 * @date           : 11/7/2023
 **********************************************************************************
**/

#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include "queue.h"

void Display(DATA e)
{
	printf("NAME: %s\nID:%d\n",e.Name,e.id);
}

int main()
{
	DATA element;
	
	Queue q;
	CreatQueue(&q);
	
	do
	{
		printf("\n-----------------------------------------------\n");
		printf("1. Clear the queue.\n");
		printf("2. Read an element then Append it.\n");
		printf("3. Serve an element then display it.\n");
		printf("4. What is the queue size?\n");
		printf("5. Display the First element.\n");
		printf("6. Print all elements in the queue.\n");
		printf("7. Exit.\n");
		printf("-----------------------------------------------\n");
		
		int choose;
		printf("\nEnter Your Order: ");
		scanf("%d",&choose);
		
		switch(choose)
		{
			case 1:
			ClearQueue(&q);
			break;
			
			case 2:
			if(!QueueFull(&q))
			{
				printf("Enter Name: ");scanf("%s",element.Name);
				char term;
                    while (1) {
                        printf("Enter the Age: ");
                        if (scanf("%d%c", &element.id, &term) != 2 || term != '\n') {
                            printf("Invalid input, please enter a number.\n");
                            while (getchar() != '\n'); // Clear the input buffer
                        } else {
                            break; // Valid input
                        }
                    }
				Append(element,&q);				
			}
			else
				printf("The Queue is Full !!\n");
			break;
			
			case 3:
			if(!QueueEmpty(&q))
			{
				Serve(&element,&q);
				printf("the served  Data\nNAME:%s\nID:%d",element.Name,element.id);				
			}
			else
				printf("The Queue is Empty !!\n");
			break;
			
			case 4:
			printf("Queue Size = %d\n",QueueSize(&q));
			break;
			
			case 5:
			if(!QueueEmpty(&q))
			{
				Retrieve(&element,&q);
				printf("the First\nNAME:%s\nID:%d",element.Name,element.id);				
			}
			else
				printf("The Queue is Empty !!\n");
			break;
			
			case 6:
			TraverseQueue(&q,&Display);
			break;
			
			case 7:
			exit(1);
			break;
		}
		
		printf("\nEnter y to continue.... \n");
	}while(getch() == 'y');
	
	return 0;
}