#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

typedef struct Table
{
    int id;
    int arrival;
    int total;
    int start;
    int end;
    int turnAround;
}TableInfo;

TableInfo *tbPtr;
int tableSize;

void printTableInfo();
void intializeTable();
void firstComeFirstServed();
void shortestJobFirst();
void shortReaminingTime();
void terminateProg();

int main () {
    int choice = 0;
    while (choice != 5){
        printf("Batch scheduling\n");
        printf("--------------------\n");
        printf("1) Enter parameters\n");
        printf("2) Schedule processes with FIFO algorithm\n");
        printf("3) Schedule processes with SJF algorithm\n");
        printf("4) Schedule processes with SRT algorithm\n");
        printf("5) Quit and free memory\n");

        printf("\nEnter selection: ");

        scanf("%d", &choice);
        getchar();
    

        switch (choice)
        {
        case 1:
            intializeTable();
            printTableInfo();
            break;
        case 5:
            terminateProg();
            choice = 5;
            break;
        default:
            break;
        }
    }
}

void intializeTable(){
    printf("Enter Total number of processes: ");
    scanf("%d", &tableSize);
    getchar();

   tbPtr = (TableInfo*)malloc(sizeof(TableInfo) * tableSize);
   if (!tbPtr) return;

   for (int i = 0; i < tableSize; i++){
    tbPtr[i].id = i + 1; // id

    //gets arrival 
    printf("Enter arrival cycle for process %d: ", tbPtr[i].id);
    scanf("%d", &tbPtr[i].arrival);
    getchar();

    //gets total
    printf("Enter toatl cycles for process %d: ", tbPtr[i].id);
    scanf("%d", &tbPtr[i].total);
    getchar();

    //place holder values for print fucntion logic 
    tbPtr[i].start = -1;
    tbPtr[i].end = -1;
    tbPtr[i].turnAround = -1;

   }
   printf("\n");

}

void printTableInfo(){
   char *header[] = {"PID", "Arrival", "Total", "Start", "End", "Turnaround"};

   printf("%-8s %-8s %-6s %-6s %-6s %-20s\n", header[0], header[1], header[2], header[3], header[4], header[5]);
   printf("---------------------------------------------------\n");
   for (int i = 0; i < tableSize; i++){
    printf("%-8d %-8d %-6d ", tbPtr[i].id, tbPtr[i].arrival, tbPtr[i].total);

    (tbPtr[i].start == -1) ? printf("") : printf("%-6d ", tbPtr[i].start);
    (tbPtr[i].end == -1) ? printf("") : printf("%-6d ", tbPtr[i].end);
    (tbPtr[i].turnAround == -1) ? printf("\n") : printf("%-20d\n", tbPtr[i].turnAround);

   }
   printf("\n");

}


void firstComeFirstServed(void) {}
void shortestJobFirst(void) {}
void shortRemainingTime(void) {}

void terminateProg(){
    free(tbPtr);
    tbPtr = NULL;
    printf("Quitting program");
}