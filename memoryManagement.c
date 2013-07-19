#include <stdio.h>
#include <stdlib.h>

struct node
{
    int pid;
    struct node *next;
};

void insertProcessNumber(struct node **, struct node **);
void evaluateOptimalPage(struct node **);
int recentlyUsedCheck(struct node *, int);
void recentlyUsedUpdate(struct node *, struct node **, int);
void releaseMemory(struct node **);

int main()
{
    struct node *headList = NULL, *headListRear = NULL;
    int choice;

    do
    {
        printf("What do you want to do?\n1. Insert a process id\n2. Perform Optimal Page Replacement\n3. Clear the Memory\n4. Exit\nYour choice: ");
        scanf("%d", &choice);
        switch (choice)
        {
            case 1: insertProcessNumber(&headList, &headListRear);
                    break;
            case 2: evaluateOptimalPage(&headList);
                    break;
            case 3: releaseMemory(&headList);
                    break;
            case 4: printf("\n\nDeveloped by: Prasoon Telang");
                    break;
            default:printf("Invalid choice entered.\nTry again");
                    break;
        }
        printf("\n\n");
    } while(choice != 4);

    if (headList != NULL)
    {
        printf("Memory was not cleared.\n");
        releaseMemory(&headList);
    }

    return 0;
}

void insertProcessNumber(struct node **headList, struct node **headListRear)
{
    struct node *tempNode;
    int processId;

    printf("\nEnter the process id: ");
    scanf("%d", &processId);
    tempNode = (struct node *)malloc(sizeof(struct node));
    tempNode->pid = processId;
    tempNode->next = NULL;
    if (*headList == NULL)
        *headList = tempNode;
    else
        (*headListRear)->next = tempNode;
    *headListRear = tempNode;
}

void evaluateOptimalPage(struct node **headList)
{
    struct node *recentlyUsedList = NULL, *tempNode, *rearNode;
    int i, processId, pageHit = 0, pageFault = 0;

    for (i = 0; i < 3; i++)
    {
        tempNode = (struct node *)malloc(sizeof(struct node));
        tempNode->next = recentlyUsedList;
        tempNode->pid = 999999;
        if (i == 0)
        {
            rearNode = tempNode;
        }
        recentlyUsedList = tempNode;
    }
    rearNode->next = recentlyUsedList;

    while (*headList != NULL)
    {
        processId = (*headList)->pid;
        if (recentlyUsedCheck(recentlyUsedList, processId))
        {
            pageHit++;
        }
        else
        {
            pageFault++;
            recentlyUsedUpdate(*headList, &recentlyUsedList, processId);
        }
        tempNode = *headList;
        *headList = (*headList)->next;
        free(tempNode);
    }

    printf("\n\n\nTotal no. of Page Hits: %d\n", pageHit);
    printf("Total no. of Page Faults: %d\n", pageFault);
    printf("Success ratio is %d:%d\n\n\n", pageHit, pageFault);

    tempNode = recentlyUsedList;
    recentlyUsedList = recentlyUsedList->next;
    tempNode->next = NULL;
    releaseMemory(&recentlyUsedList);
}

int recentlyUsedCheck (struct node *recentlyUsedList, int processId)
{
    if (recentlyUsedList->pid == processId || recentlyUsedList->next->pid == processId || recentlyUsedList->next->next->pid == processId)
        return 1;
    else
        return 0;
}

void recentlyUsedUpdate(struct node *headList, struct node **recentlyUsedList, int processId)
{
    int nextProcessId;
    struct node *tempNode = *recentlyUsedList;

    if (headList->next != NULL)
    {
        nextProcessId = headList->next->pid;
        if (nextProcessId == tempNode->pid || nextProcessId == tempNode->next->pid || nextProcessId == tempNode->next->next->pid)
        {
            tempNode = tempNode->next;
            if (headList->next->next != NULL)
            {
                nextProcessId = headList->next->next->pid;
                if (nextProcessId == tempNode->pid || nextProcessId == tempNode->next->pid || nextProcessId == tempNode->next->next->pid)
                {
                    tempNode = tempNode->next;
                }
                tempNode->pid = processId;
            }
            tempNode->pid = processId;
        }
    }
    tempNode->pid = processId;
    *recentlyUsedList = (*recentlyUsedList)->next;
}

void releaseMemory(struct node **listToDelete)
{
    struct node *tempNode;

    if (*listToDelete == NULL)
    {
        printf("\nNo memory reserved by the program\n");
        return;
    }
    while ((*listToDelete) != NULL)
    {
        tempNode = *listToDelete;
        *listToDelete = (*listToDelete)->next;
        free(tempNode);
    }

    printf("Memory cleared.\n");
}
