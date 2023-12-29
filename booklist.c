#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

#define PRINT_BOOK(book) \
    printf("Title: %s\nPrice: %lu\nPages: %lu\nLanguage: %s\nWeight: %.2fkg\nYear: %lu\n", \
            book->title, book->price, book->pages, book->language, book->weight / 10.0, book->year_of_publishing)

typedef struct Book {
    char title[256];
    uint64_t price;
    uint64_t pages;
    char language[64];
    uint64_t weight;
    uint64_t year_of_publishing;
} Book;

typedef struct Node {
    Book *data;
    struct Node *prev;
    struct Node *next;
} Node;


Book *createBook(const uint8_t *title, uint64_t price, uint64_t pages, const uint8_t *language,
                    uint64_t weight, uint64_t year_of_publishing)
{
    Book *newBook = (Book *)calloc(1, sizeof(Book));
    if (!newBook) {return NULL;}
    if (title) {strncpy(newBook->title, title, sizeof(newBook->title));}
    if (language) {strncpy(newBook->language, language, sizeof(newBook->language));}
    newBook->price = price;
    newBook->pages = pages;
    newBook->weight = weight;
    newBook->year_of_publishing = year_of_publishing;
    return newBook;
}

void freeNode(Node *node) {
    Node *NextNode;
    Node *PrevNode;
    if (node) {
        NextNode = node->next;
        PrevNode = node->prev;
        if (PrevNode) {PrevNode->next = node->next;}
        if (NextNode) {NextNode->prev = node->prev;}
        free(node);
    }
}

Node *insertBook(Book *newBook, Node *Where) {
    Node *NewNode = NULL;
    if (newBook) {
        NewNode = (Node*)calloc(1, sizeof(Node));
        if (NewNode) {
            NewNode->data = newBook;
            NewNode->next = Where ? Where->next : NULL;
            NewNode->prev = Where;
            if (Where) {
                if (Where->next) {(Where->next)->prev = NewNode;}
                Where->next = NewNode;
            }
        }
    }
    return NewNode;
}

void insertLast(Book *newBook, Node *head) {
    if (head) {
        while (head->next) {
            head = head->next;
        }
        insertBook(newBook, head);
    }
}

Node *findBookByTitle(Node *head, const uint8_t *title) {
    if (!title) {return NULL;}
    while (head) {
        if (strcmp(head->data->title, title) == 0) {
            return head;
        }
        head = head->next;
    }
    return NULL;
}

Book *popBookByTitle(Node *head, const uint8_t *title) {
    Node *found = findBookByTitle(head, title);
    if (!found) {return NULL;}
    Book *book = found->data;
    freeNode(found);
    return book;
}

void destroyList(Node *head) {
    Node *deleted = NULL;
    while (head) {
        deleted = head;
        head = head->next;
        free(deleted->data);
        freeNode(deleted);
    }
}

void printList(Node *head) {
    puts("Listing looks this way:");
    while (head) {
        Book *book = head->data;
        PRINT_BOOK(book);
        puts("-----------------------------------------");
        head = head->next;
    }
}

int main() {
    Node *head = NULL;

    Book *book1 = createBook("Harry Potter and the Philosopher's Stone", 100, 320, "Spanish", 2, 1997);
    head = insertBook(book1, NULL);
    Book *book2 = createBook("Harry Potter and the Chamber of Secrets", 200, 352, "Japanese", 12, 1998);
    insertLast(book2, head);
    Book *book3 = createBook("Harry Potter and the Prisoner of Azkaban", 300, 448, "Mandarin", 6, 1999);
    insertLast(book3, head);
    Book *book4 = createBook("Harry Potter and the Goblet of Fire", 2295, 400, "Ukrainian", 15, 2000);
    insertLast(book4, head);
    Book *book5 = createBook("Harry Potter and the Order of the Phoenix", 500, 816, "Dutch", 17, 2003);
    insertLast(book5, head);
    Book *book6 = createBook("Harry Potter and the Half-Blood Prince", 26, 690, "French", 8, 2005);
    insertLast(book6, head);


    /* adding a book here */
    Book *book7 = createBook("Harry Potter and the Deadly Harrows", 26, 672, "Mexican", 201, 2007);
    insertLast(book7, head);
    printList(head);

    destroyList(head);
}
