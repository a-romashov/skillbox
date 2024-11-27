#include "library.h"
#include "stdlib.h"
#include "stdio.h"


book_t *scanBook(char* buffer) {
    book_t *result = malloc(sizeof(book_t));
    char *inputMask = "%[^;];%[^;];%[^;];%hu";
    int success = sscanf(
            buffer,
            inputMask,
            result->authors,
            result->name,
            result->ISBN,
            &result->year
    );

    if (success < 4) {
        free(result);
        return NULL;
    }

    return result;
}

library_t *fillLibrary() {
    library_t * result = malloc(sizeof(library_t));
    result->count = 0;

    printf("%s\n", "Enter library data");

    char buffer[LIBRARY_READ_BOOK_BUFFER_SIZE];
    book_t *book;
    fgets(buffer, LIBRARY_READ_BOOK_BUFFER_SIZE, stdin);
    while ((book = scanBook(buffer)) != NULL) {
        result->books[result->count++] = book;
        fgets(buffer, LIBRARY_READ_BOOK_BUFFER_SIZE, stdin);
    }

    return result;
}

void searchAndPrintBooks(library_t *library) {
    struct {
        book_t ** books;
        unsigned int count;
    } result;

    result.count = 0;
    result.books = malloc(1);

    printf("%s", "Enter term:\n");
    char buffer[LIBRARY_BOOK_NAME_SIZE];
    fgets(buffer, LIBRARY_BOOK_NAME_SIZE, stdin);

    for (int i = 0; i < library->count; i++) {

        int f = 0;

        for (int n = 0; n < sizeof(library->books[i]->name) / sizeof(char); n++) {
            if (buffer[f] == '\0' || buffer[f] == '\n') {
                //дошли до конца поисковой строки, значит это подстрока, добавим книгу к результату
                book_t ** new = realloc(result.books, ++result.count * sizeof(void*));
                if (new == NULL) {
                    free(result.books);
                    return;
                }
                result.books = new;
                result.books[result.count - 1] = library->books[i];
                break;
            }
            if (library->books[i]->name[n] == '\0') {
                break;
            }
            if (library->books[i]->name[n] == buffer[f]) {
                // совпала буква, идем дальше
                f++;
            } else {
                n -= f; //откатываемся на следующую букву после начала цепочки совпадений
                f = 0;
            }
        }
    }

    printf("%s", "search results:\n");
    if (result.count) {
        for (int i = 0; i < result.count; i++) {
            printf(
                    "%d. %s;%s;%s;%hu\n",
                    i + 1,
                    result.books[i]->name,
                    result.books[i]->authors,
                    result.books[i]->ISBN,
                    result.books[i]->year
            );
        }
    } else {
        printf("%s", "...no results...\n");
    }

    free(result.books);
}


void freeLibrary(library_t *library) {
    for (int i = 0; i < library->count; i++) {
        free(library->books[i]);
    }
    free(library);
}