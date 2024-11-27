#include <stdlib.h>
#include <stdio.h>
#include "employee.h"

employee_t *scanEmployee(char *buffer) {
    employee_t *result = malloc(sizeof(employee_t));
    char *inputMask = "%s %s %s %c %hu %s";
    int success = sscanf(
            buffer,
            inputMask,
            result->lastName,
            result->firstName,
            result->middleName,
            &result->gender,
            &result->age,
            result->post
    );

    if (success < 6) {
        free(result);
        return NULL;
    }

    return result;
}

company_t *fillCompany() {
    company_t *result = malloc(sizeof(company_t));
    result->count = 0;
    result->femaleCnt = 0;
    result->maleCnt = 0;

    printf("%s\n", "Enter company data");

    char buffer[READ_EMPLOYEE_BUFFER_SIZE];
    employee_t *employee;
    fgets(buffer, READ_EMPLOYEE_BUFFER_SIZE, stdin);
    while ((employee = scanEmployee(buffer)) != NULL) {

        // посчитаем кол-во мужчин и женщин
        if (employee->gender == 'M') {
            result->maleCnt++;
        } else {
            result->femaleCnt++;
        }

        /**
         * и сразу сортировка по возрасту
         */
        for (int i = 0; i < result->count; i++) {
            if (employee->age < result->employees[i]->age) {
                employee_t *tmp = result->employees[i];
                result->employees[i] = employee;
                employee = tmp;
            }
        }
        result->employees[result->count++] = employee;

        fgets(buffer, READ_EMPLOYEE_BUFFER_SIZE, stdin);
    }

    return result;
}

unsigned int *getMedianIndex(const unsigned int length) {
    unsigned int *result = malloc(sizeof(int) * 2);
    result[0] = length ? (length / 2) + (length % 2) - 1 : 0;
    result[1] = length ? (length / 2) : 0;
    return result;
}

void printCompanyStats(company_t *company) {

    unsigned int allAgesSum = 0;
    unsigned int maleAgesSum = 0;
    unsigned int femaleAgesSum = 0;
    unsigned int medianAgeAll = 0;
    unsigned int medianAgeMale = 0;
    unsigned int medianAgeFemale = 0;

    unsigned int *medianIndexAll = getMedianIndex(company->count);
    unsigned int *medianIndexMale = getMedianIndex(company->maleCnt);
    unsigned int *medianIndexFemale = getMedianIndex(company->femaleCnt);

    for (int i = 0, m = 0, f = 0; i < company->count; i++) {
        employee_t *employee = company->employees[i];

        for (int j = 0; j < 2; j++)
            if (i == medianIndexAll[j])
                medianAgeAll += employee->age;

        allAgesSum += employee->age;

        if (employee->gender == 'M') {

            for (int j = 0; j < 2; j++)
                if (m == medianIndexMale[j])
                    medianAgeMale += employee->age;
            maleAgesSum += employee->age;
            m++;

        } else if (employee->gender == 'F') {

            for (int j = 0; j < 2; j++)
                if (f == medianIndexFemale[j])
                    medianAgeFemale += employee->age;
            femaleAgesSum += employee->age;
            f++;

        }
    }
    free(medianIndexAll);
    free(medianIndexMale);
    free(medianIndexFemale);

    printf("Total employees count is %d\n", company->count);
    printf("Total male count is %d\n", company->maleCnt);
    printf("Total female count is %d\n", company->femaleCnt);

    printf("All average age is %.2f\n", (float) allAgesSum / (float) company->count);
    printf("Male average age is %.2f\n", (float) maleAgesSum / (float) company->maleCnt);
    printf("Female average age is %.2f\n", (float) femaleAgesSum / (float) company->femaleCnt);

    printf("All median age is %.2f\n", (float) medianAgeAll / 2.0f);
    printf("Male median age is %.2f\n", (float) medianAgeMale / 2.0f);
    printf("Female median age is %.2f\n", (float) medianAgeFemale / 2.0f);
}

void freeCompany(company_t *company) {
    for (int i = 0; i < company->count; i++) {
        free(company->employees[i]);
    }
    free(company);
}