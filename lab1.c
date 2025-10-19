#include <stdio.h>
#include <stdlib.h>


#define MAX_PROCESSES 10
typedef struct ChildNode {
    int childId;
    struct ChildNode* next;
}Child;

typedef struct PCB {
    int parent;
    Child* children;
}PCB;

PCB *pcbArr[MAX_PROCESSES] = {0}; // global process array 

void initalizePCB();
void printPCB();
void createNewChild();
void destroyChildren();
void destroyChildrenHelper(Child* node);
void freeAllMemory();

int main (){

    int choice = 0; 
    while (choice != 4){
        printf("1) Initialize process hierarchy\n");
        printf("2) Create a new child process\n");
        printf("3) Destroy all decendants of a parent process\n");
        printf("4) Quit program and free memory\n");

        if (scanf("%d", &choice) != 1) {      // robust read
            int ch; while ((ch = getchar()) != '\n' && ch != EOF) {}
            puts("Invalid input. Try again.");
            choice = 0;
            continue;
        }
        getchar(); 

        switch (choice){
            case 1:
                initalizePCB();
                break;
            case 2:
                createNewChild();
                break;
            case 3:
                destroyChildren();
                break;
            case 4:
                freeAllMemory();
                choice = 4;
                break;
            default: 
                puts("Unknown choice."); 
                break;
        }
    }

    return 0;
}


void initalizePCB(){
    pcbArr[0] = (PCB*)malloc(sizeof(PCB));
    if (!pcbArr[0]) {
    printf("failed to allocated memory\n");
    return;
    }

    pcbArr[0]->parent = 0;          
    pcbArr[0]->children = NULL;

    for (int i = 1; i < MAX_PROCESSES; i++){
        pcbArr[i] = NULL;
    }

    printPCB();
}

void createNewChild(){
    int p;
    int q = 0;
    Child* n = malloc(sizeof(*n));
    printf("\nEnter parent process index: \n");
    scanf("%d", &p);
    getchar();

    // index provided has not been inialized properly 
    if (pcbArr[p] == NULL) {
        printf("process does not exist\n\n");
        return; 
    }
    // search for empty slot 
    while (q < MAX_PROCESSES && pcbArr[q] != NULL){
        q++;
    }
    // check if maximum number of processes was reached 
    if (q == MAX_PROCESSES ) {
    printf("No more avaiable PCB's\n");
    return; 
    }
    // allocate memory for child process 
    pcbArr[q] = (PCB*)malloc (sizeof(PCB));
    if (!pcbArr[q]) {
        printf("Failed to allocate memory for child process.\n");
        return;
    }
    //record the parent's index p
    pcbArr[q]->parent = p;
    //initialize the list of children of PCB[q] as empty */
    pcbArr[q]->children = NULL;
    //insert child
    n->childId = q;
    n->next = NULL;
    // Append q to parent's children list
    Child **tail = &pcbArr[p]->children;
    while (*tail) {
        tail = &(*tail)->next;
    }
    *tail = n;

    printPCB();

}

void destroyChildren(){
    //prompt for process index p 
    int p;
    printf("\nEnter process index to delete\n");
    scanf("%d", &p);
    getchar();

    //call recursive procedure to destroy children of PCB[p]
    destroyChildrenHelper(pcbArr[p]->children);

    //reset children of PCB[p] to NULL
    pcbArr[p]->children = NULL;
    
    //print hierrarchy 
    printPCB();
}

void destroyChildrenHelper(Child* node){
    // check if end of lined list is so return base case 
    if (node == NULL) return;
    
    //call self on next node in linked list
    destroyChildrenHelper(node->next);

    //set variable q to current node's process index field
    int q = node->childId;

    //call self on children of pcbArr[q] 
    if (q >= 0 && q < MAX_PROCESSES && pcbArr[q] != NULL){
        destroyChildrenHelper(pcbArr[q]->children);
        free(pcbArr[q]);
        pcbArr[q] = NULL;
    }
    //free memory of paramter and set to NULL
    free(node);
    

}

void freeAllMemory(){
   //if pcb[0] is non null
   if(pcbArr[0] != NULL){
    //if children of PCB is not null
    if(pcbArr[0]->children != NULL){
        //call recursive procedure to destroy children of PCB[0]
        destroyChildrenHelper(pcbArr[0]->children);
    }
   }

   //free memory of all PCB's
   for(int i = 0; i < MAX_PROCESSES; i++){
    free(pcbArr[i]);
    pcbArr[i] = NULL;
   }
   puts("All memory freed.");
}

void printPCB(void) {
    for (int i = 0; i < MAX_PROCESSES; i++) {
        PCB *p = pcbArr[i];
        if (p != NULL) {
            printf("process ID: %d, parent ID: %d, children: ", i, p->parent);

            for (Child *c = p->children; c != NULL; c = c->next) {
                printf("%d", c->childId);
                if (c->next) printf(" ");
            }
            printf("\n");
        }
    }
}
