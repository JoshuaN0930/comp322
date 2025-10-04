#include <stdio.h>
#include <string.h>

struct Product {
    int id;
    char name[25];
    float price;
    int quantity;
};

void printInfo(struct Product *ptr);
void verifyAddresses(struct Product *ptr, struct Product *item);
int main (){
    struct Product item = {501, "laptop", 899.99, 15};
    struct Product *itemPtr = &item;

    printf("Product Info:\n");
    printf("ID: %d\n", item.id);
    printf("Name: %s\n", item.name);
    printf("Price: %.2f\n", item.price);
    printf("Quantity: %d\n", item.quantity);

    printInfo(itemPtr);
    verifyAddresses(itemPtr, &item);
    return 0;
}

void printInfo (struct Product *ptr){
    printf("--------------------------\n");
    printf("Product Info via pointer:\n");
    printf("ID: %d\n", (*ptr).id);
    printf("Name: %s\n", (*ptr).name);
    printf("Price: %.2f\n", (*ptr).price);
    printf("Quantity: %d\n", (*ptr).quantity);

}

void verifyAddresses(struct Product *ptr, struct Product *item){
    printf("Address of item:  %p\n", (void*)item);
    printf("Value of itemPtr: %p\n", (void*)ptr);
    if (ptr == item){
        printf("Address verification: Match\n");
    } else {
        printf("Address verification: No Match\n");
    }
    
}
