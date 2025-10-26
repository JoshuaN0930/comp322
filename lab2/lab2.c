#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

typedef struct Table{
    int id;
    int arrival;
    int total;
    int start;
    int end;
    int turnAround;
    int done;
    int already_start;
    int totalRemaining;
}TableInfo;

TableInfo *tbPtr;
int tableSize;

void printTableInfo();
void intializeTable();
void firstComeFirstServed();
void shortestJobFirst();
void shortRemainingTime();
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
        case 2:
            firstComeFirstServed();
            break;
        case 3:
            shortestJobFirst();
            break;
        case 4:
            shortRemainingTime();
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

void firstComeFirstServed() {
   // for each process, reset "done" field to 0
   for (int i = 0; i < tableSize; i++){
    tbPtr[i].done = 0;
   }
   int sum = 0;
   int i = 0;
   while (i < tableSize){
    // keep track of what process is has the earliest arrival time 
    int indexArr;
    int earliestArrival = INT_MAX;
    
    
    for (int j = 0; j < tableSize; j++){
        //check if curr process j has been schedule or not so done = 0
        if (tbPtr[j].done == 0){
            //check if curr arrival time for j is smaller than value in earliestArrival if so set new min
            if (tbPtr[j].arrival < earliestArrival){
                earliestArrival = tbPtr[j].arrival;
                indexArr = j;
            }

        }
    }

    //calculate start, end, turnaround for earliest process
    tbPtr[indexArr].start = sum;
    tbPtr[indexArr].end = sum + tbPtr[indexArr].total;
    tbPtr[indexArr].turnAround = tbPtr[indexArr].end - tbPtr[indexArr].arrival;
    tbPtr[indexArr].done = 1; 

    sum = tbPtr[indexArr].end;
    i++;
   }
   printTableInfo();
}

void shortestJobFirst() {
    for (int i = 0; i < tableSize; i ++){
        tbPtr[i].done = 0;
    }

    int i = 0;
    int sum = 0;
    while (i < tableSize) {
        int indexTotal;
        int smallestBurstTime = INT_MAX;

        for (int j = 0; j < tableSize; j++){
            if (tbPtr[j].done == 0 && tbPtr[j].arrival <= sum){
                if (tbPtr[j].total < smallestBurstTime ){
                    smallestBurstTime = tbPtr[j].total;
                    indexTotal = j;
                }
            }
        }

        tbPtr[indexTotal].start = sum;
        tbPtr[indexTotal].end = sum + tbPtr[indexTotal].total;
        tbPtr[indexTotal].turnAround = tbPtr[indexTotal].end - tbPtr[indexTotal].arrival;
        tbPtr[indexTotal].done = 1;

        sum = tbPtr[indexTotal].end;
        i++;
    }

    printTableInfo();
}

void shortRemainingTime() {
    for (int i = 0; i < tableSize; i++){
        tbPtr[i].done = 0;
        tbPtr[i].already_start = 0;
        tbPtr[i].totalRemaining = tbPtr[i].total;
    }


    int current_time = 0;
    int i = 0;
    while (i < tableSize) {
        int index = -1;
        int lowRemainingT = INT_MAX;

        for(int j = 0; j < tableSize; j++){
            if (tbPtr[j].done == 0 && tbPtr[j].arrival <= current_time){
                if (tbPtr[j].totalRemaining < lowRemainingT){
                    lowRemainingT = tbPtr[j].totalRemaining;
                    index = j;
                }

            }

        }

        // check if the process picked has been previously schedule if not then toogle to yes 
        if (tbPtr[index].already_start == 0){
            tbPtr[index].already_start = 1;
            tbPtr[index].start = current_time;
        } 
        

        tbPtr[index].totalRemaining -= 1;
        current_time += 1;

        if (tbPtr[index].totalRemaining == 0){
            tbPtr[index].end = current_time;
            tbPtr[index].turnAround = tbPtr[index].end - tbPtr[index].arrival;
            tbPtr[index].done = 1;
            i++;
        }
    }
    printTableInfo();
}

void terminateProg(){
    free(tbPtr);
    tbPtr = NULL;
    printf("Quitting program");
}