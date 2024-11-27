#ifndef SKILLBOX_LIBRARY_H
#define SKILLBOX_LIBRARY_H

#define LIBRARY_BOOK_MAX_AUTHORS 3
#define LIBRARY_BOOK_AUTHOR_FIO_SIZE 64
#define LIBRARY_BOOK_NAME_SIZE 64
#define LIBRARY_READ_BOOK_BUFFER_SIZE 256

#define LIBRARY_MAX_BOOKS_COUNT 64

typedef struct {
    char authors[LIBRARY_BOOK_AUTHOR_FIO_SIZE * LIBRARY_BOOK_MAX_AUTHORS];
    char name[LIBRARY_BOOK_NAME_SIZE];
    char ISBN[LIBRARY_BOOK_NAME_SIZE];
    unsigned short int year;
} book_t;

typedef struct {
    book_t *books[LIBRARY_MAX_BOOKS_COUNT];
    int count;
} library_t;

library_t *fillLibrary();

void searchAndPrintBooks(library_t *library);

void freeLibrary(library_t *library);

#endif //SKILLBOX_LIBRARY_H
