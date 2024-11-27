#include "student.h"
#include "stdio.h"
#include "stdlib.h"

#define READ_STUDENT_BUFFER_SIZE 1 << 8

student_t *scanStudent(char *buffer) {
    student_t *result = malloc(sizeof(student_t));
    char *inputMask = "%s %s %s %c %s %s %hu";
    int success = sscanf(
            buffer,
            inputMask,
            result->lastName,
            result->firstName,
            result->middleName,
            &result->gender,
            result->className,
            result->subject,
            &result->grade
    );

    if (success < 7) {
        free(result);
        return NULL;
    }

    return result;
}

classJournal_t *scanClassJournal() {

    printf("%s\n", "Enter journal data");

    classJournal_t *result = malloc(sizeof(classJournal_t));
    result->count = 0;

    char buffer[READ_STUDENT_BUFFER_SIZE];
    student_t *student;
    fgets(buffer, READ_STUDENT_BUFFER_SIZE, stdin);
    while ((student = scanStudent(buffer)) != NULL) {
        result->students[result->count++] = student;
        fgets(buffer, READ_STUDENT_BUFFER_SIZE, stdin);
    }

    return result;
}

unsigned short int isStrEqual(const char *str1, const char *str2) {
    int i = 0;
    while (1) {
        if (str1[i] == '\0' || str2[i] == '\0') {
            return str1[i] == str2[i];
        }
        if (str1[i] != str2[i]) {
            return 0;
        }
        i++;
    }
}

void printJournalStatistics(classJournal_t *journal) {
    struct studentStats {
        char *firstName;
        char *lastName;
        char *middleName;
        char gender;
        int gradeSum;
        int gradeCnt;
        float gradeAvg;
    };

    struct studentStats **studentsStats = malloc(1);
    int uniqueStudentsCnt = 0;
    for (int i = 0; i < journal->count; i++) {
        int found = 0;
        // поиск нужной записи по ФИО
        for (int j = 0; j < uniqueStudentsCnt; j++) {

            if (isStrEqual(studentsStats[j]->firstName, journal->students[i]->firstName)) {
                if (isStrEqual(studentsStats[j]->lastName, journal->students[i]->lastName)) {
                    if (isStrEqual(studentsStats[j]->middleName, journal->students[i]->middleName)) {
                        found = j + 1;
                        break;
                    }
                }
            }
        }

        if (found) {
            //нашли обновляем статистику
            studentsStats[found - 1]->gradeSum += journal->students[i]->grade;
            studentsStats[found - 1]->gradeCnt++;
            studentsStats[found - 1]->gradeAvg = (float) studentsStats[found - 1]->gradeSum / (float) studentsStats[found - 1]->gradeCnt;
        } else {
            //не нашли добавим к статистике
            struct studentStats **newStudentStats = realloc(
                    studentsStats,
                    sizeof(struct studentStats *) * (++uniqueStudentsCnt)
            );
            if (newStudentStats == NULL) {
                free(studentsStats);
                printf("fatal, can`t allocate memory");
                return;
            }
            studentsStats = newStudentStats;
            struct studentStats *stats = malloc(sizeof(struct studentStats));
            stats->firstName = journal->students[i]->firstName;
            stats->lastName = journal->students[i]->lastName;
            stats->middleName = journal->students[i]->middleName;
            stats->gender = journal->students[i]->gender;
            stats->gradeSum = journal->students[i]->grade;
            stats->gradeCnt = 1;
            stats->gradeAvg = (float) stats->gradeSum;

            studentsStats[uniqueStudentsCnt - 1] = stats;
        }
    }

    printf("Students count %d\n", uniqueStudentsCnt);

    /**
     *
     * ранжировать учеников в классе по успеваемости
     */
    printf("%s", "Students average grades:\n");
    for (int i = 5; i > 2; i--) {

        printf("Students with average grades between %d and %d:\n", i - 1, i);
        int cnt = 0;
        for (int j = 0; j < uniqueStudentsCnt; j++) {
            if (studentsStats[j]->gradeAvg < (float) i && studentsStats[j]->gradeAvg >= (float) (i - 1)) {
                cnt++;
                printf(
                        "%s %s %s: %.2f\n",
                        studentsStats[j]->lastName,
                        studentsStats[j]->firstName,
                        studentsStats[j]->middleName,
                        studentsStats[j]->gradeAvg
                );
            }
        }
        if (!cnt) {
            printf("%s\n", "...no students...");
        }
    }

    const char *genders[2] = {"Male", "Female"};
    for (int i = 0; i < 2; i++) {

        int grades = 0;
        int gradesCnt = 0;

        for (int j = 0; j < uniqueStudentsCnt; j++) {
            if (studentsStats[j]->gender == genders[i][0]) {
                grades += studentsStats[j]->gradeSum;
                gradesCnt += studentsStats[j]->gradeCnt;
            }
        }

        printf("%s average grade is %.2f\n", genders[i], (float) grades / (float) gradesCnt);
    }

    for (int i = 0; i < uniqueStudentsCnt; i++) {
        free(studentsStats[i]);
    }
    free(studentsStats);
}


void freeJournal(classJournal_t *journal) {
    for (int i = 0; i < journal->count; i++) {
        free(journal->students[i]);
    }
    free(journal);
}
