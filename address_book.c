#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef struct Person {
    char fullName[50];
    int age;
    char phone[20];
} Person;

typedef struct AddressBook{
    Person* persons;
    int size;
} Address_book;

void print_person(const Person* person);
void print_address_book(const Address_book* address_book);
Address_book* create_address_book(void);
void destroy_address_book(Address_book* address_book);

int main (){
    
    Address_book *ptr = create_address_book();
    print_address_book(ptr);
    destroy_address_book(ptr);
    return 0;
}

void print_person(const Person* person){
    printf("Name: %s\n", person->fullName);
    printf("Age: %d\n", person->age);
    printf("Phone number: +%s\n", person->phone);
}
void print_address_book(const Address_book* address_book){
    printf("==== Address book(%d entries) =====\n\n", address_book->size);
    for(int i = 0; i < address_book->size; i++){
        print_person(&address_book->persons[i]);
        if (i < address_book->size -1){ // print a line between each entry excluding the last one
            printf("\n");
        }
    }
}

Address_book* create_address_book (void){
    int n; 
    scanf("%d", &n);
    getchar();

    Address_book *book = malloc(sizeof(*book));
    if (!book) return NULL;

    book->size = n;
    book->persons = malloc(n * sizeof(*book->persons));
    if(!book->persons) {
        free(book);
        return NULL;
    }

    // populate persons array 
    for(int i = 0; i < n; i++){
        // get name from user
        printf("Enter details for person %d\n", i + 1);

        printf("Enter full name: ");
        fgets(book->persons[i].fullName, sizeof(book->persons[i].fullName), stdin);
        book->persons[i].fullName[strcspn(book->persons[i].fullName, "\n")] = '\0';

        printf("Enter age: ");
        scanf("%d", &book->persons[i].age);
        getchar();

        printf("Enter phone: ");
        fgets(book->persons[i].phone, sizeof(book->persons[i].phone), stdin);
        book->persons[i].phone[strcspn(book->persons[i].phone, "\n")] = '\0';

        printf("\n");
    }
    return book;
}

void destroy_address_book(Address_book *address_book){
    if (!address_book) return;
    free(address_book->persons);
    free(address_book);
    printf("\nAddress_book destroyed successfully\n");
}