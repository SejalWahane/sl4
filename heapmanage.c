#include <malloc.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct memory_node
{
    int size;
    struct memory_node *next;
    struct memory_node *prev;
    int sr_no;
} memoryBlock;
memoryBlock *first = NULL;

typedef struct process_node
{
    int size;
    struct process_node *prev;
    struct process_node *next;
    int fromBlockNo;
    int sr_no;
} processBlock;
processBlock *pFirst = NULL;

// to count no. of blocks :
int memoryBlockCount = 1;                                                       //global variable
int processBlockCount = 1;                                                      //global variable
//creating memory blocks as per need
void createMemoryBlock(memoryBlock *p, int n)
{
    int i = 0;

    if (first != NULL)
    {
        while (p->next != NULL)
        {
            p = p->next;
        }
    }

    for (i = 0; i < n; i++)
    {

        memoryBlock *temp;
        temp = (memoryBlock *)malloc(sizeof(memoryBlock));
        printf("Enter the size of memory block no. %d - ", memoryBlockCount);
        scanf("%d", &temp->size);
        temp->sr_no = memoryBlockCount;

        if (first == NULL)
        {
            temp->next = NULL;
            temp->prev = NULL;
            first = temp;
        }
        else
        {
            temp->next = NULL;
            temp->prev = p;

            if (first->next == NULL)
            {
                first->next = temp;
            }
            else
            {
                p->next = temp;
            }
        }

        p = temp;
        memoryBlockCount = memoryBlockCount + 1;
    }

    p->next = NULL;
}

void startProcess(memoryBlock *p, processBlock *q, int n)
{
    int i;

    if (pFirst != NULL)
    {
        while (q->next != NULL)
        {
            q = q->next;
        }
    }

    for (i = 0; i < n; i++)
    {

        processBlock *temp;
        temp = (processBlock *)malloc(sizeof(processBlock));
        printf("Enter the size of memory block no. %d - ", processBlockCount);
        scanf("%d", &temp->size);

        while (p != NULL)
        {
            if (p->size >= temp->size)
            {
                break;
            }
            else
            {
                p = p->next;
            }
        }

        if (p == NULL)
        {
            printf("\nInsufficient space\n");
            i = i - 1;
            p = first;
            free(temp);
            continue;
        }

        if (pFirst == NULL)
        {
            temp->next = NULL;
            temp->prev = NULL;
            pFirst = temp;
        }
        else
        {
            temp->next = NULL;
            temp->prev = q;

            if (pFirst->next == NULL)
            {
                pFirst->next = temp;
            }
            else
            {
                q->next = temp;
            }
        }

        temp->sr_no = processBlockCount;
        p->size = p->size - temp->size;
        temp->fromBlockNo = p->sr_no;
        q = temp;
        p = first;
        processBlockCount = processBlockCount + 1;
    }
}
//printing memory block number and its size
void print1(memoryBlock *p)
{
    printf("Memory blocks : ");
    while (p != NULL)
    {
        printf("[%d - %d]", p->sr_no, p->size);
        p = p->next;
    }
}
//printing process block number and size
void print2(processBlock *p)
{
    printf("Processes : ");
    while (p != NULL)
    {
        printf("[%d - %d]", p->sr_no, p->size);
        p = p->next;
    }
}

void reassign(processBlock *p)
{
    int n = 1;

    while (p != NULL)
    {
        p->sr_no = n;
        p = p->next;
        n = n + 1;
    }

    print2(pFirst);
}
//we are going to free the memory used by the processes
void freeprocessmemory(memoryBlock *p, processBlock *q, int n)
{

    for (int i = 0; i < n; i++)
    {

        int sr;
        printf("Enter the process no. you want to terminate : ");
        scanf("%d", &sr);

        while (q != NULL && q->sr_no != sr)
        {
            q = q->next;
        }

        while (p != NULL && p->sr_no != q->fromBlockNo)
        {
            p = p->next;
        }
        p->size = p->size + q->size;

        while (q)
        {

            // case 1 - only one block in process
            if (q->next == NULL && p->prev == NULL)
            {
                pFirst = NULL;
                free(q);
                processBlockCount = processBlockCount - 1;
                break;
            }

            // case 2 - for first block
            else if (q->next != NULL && q->prev == NULL)
            {
                q->next->prev = NULL;
                pFirst = q->next;
                free(q);
                processBlockCount = processBlockCount - 1;
                break;
            }

            // case 3 - any other block
            else
            {
                q->prev->next = q->next;
                free(q);
                processBlockCount = processBlockCount - 1;
                break;
            }
        }

        reassign(pFirst);
        printf("\n\n");
        p = first;
        q = pFirst;

    }
}

int main()

{
    int choice = 0;

    while (choice != 4)
    {
        int n;
        printf("1 - Create memory blocks\n");
        printf("2 - Start processes\n");
        printf("3 - Free a process memory\n");
        printf("4 - Exit program\n\n");

        printf("Enter your choice : ");                                     //asking for the choice
        scanf("%d", &choice);

        switch (choice)
        {

        case 1:
        {
            printf("Enter no. of memory blocks to add : ");
            scanf("%d", &n);
            createMemoryBlock(first, n);
            printf("\n");
            break;
        }

        case 2:
        {
            printf("Enter no. of processes to start : ");
            scanf("%d", &n);
            startProcess(first, pFirst, n);
            printf("\n");
            break;
        }

        case 3:
        {
            printf("Enter no. of processes to terminate : ");
            scanf("%d", &n);
            freeprocessmemory(first, pFirst, n);
            printf("\n");
            break;
        }

        case 4:
        {
            // exit the loop
            break;
        }

        default:
        {
            printf("Invalid Choice. Try again\n");                          //default case if user give any invalid option no
            printf("\n");
            break;
        }
        }

        print1(first);                                                      //printning memory block 
        printf("\n\n");
        print2(pFirst);                                                     //printing process memory 
        printf("\n\n");
    }

    return 0;
}