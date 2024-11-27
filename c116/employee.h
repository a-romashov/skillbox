#ifndef SKILLBOX_EMPLOYEE_H
#define SKILLBOX_EMPLOYEE_H

#define EMPLOYEES_MAX_COUNT 15
#define READ_EMPLOYEE_BUFFER_SIZE 64
#define EMPLOYEE_STRING_SIZE 16


typedef struct {
    char firstName[EMPLOYEE_STRING_SIZE];
    char lastName[EMPLOYEE_STRING_SIZE];
    char middleName[EMPLOYEE_STRING_SIZE];
    unsigned short int age;
    char gender;
    char post[EMPLOYEE_STRING_SIZE];
} employee_t;

typedef struct {
    employee_t *employees[EMPLOYEES_MAX_COUNT];
    unsigned int count;
    unsigned int maleCnt;
    unsigned int femaleCnt;
} company_t;

company_t *fillCompany();

void printCompanyStats(company_t *company);

void freeCompany(company_t *company);

#endif //SKILLBOX_EMPLOYEE_H
