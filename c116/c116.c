
#define ACTION_JOURNAL 1
#define ACTION_LIBRARY 2
#define ACTION_EMPLOYEE 3

#define ACTION ACTION_JOURNAL

#ifdef ACTION

#if ACTION == ACTION_JOURNAL

#include "student.h"

#define doJob() \
classJournal_t *journal = scanClassJournal(); \
printJournalStatistics(journal);              \
freeJournal(journal)

#elif ACTION == ACTION_LIBRARY

#include "library.h"

#define doJob() \
library_t *library = fillLibrary();\
searchAndPrintBooks(library);\
freeLibrary(library)

#elif ACTION == ACTION_EMPLOYEE

#include "employee.h"

#define doJob() \
company_t *company = fillCompany();\
printCompanyStats(company);\
freeCompany(company)

#else

#include <stdio.h>
#define doJob() printf('FATAL, INVALID ACTION')

#endif

#else

#include <stdio.h>
#define doJob() printf('FATAL, UNDEFINED ACTION')

#endif

int main() {
    doJob();
    return 0;
}