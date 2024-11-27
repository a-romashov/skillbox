//
// Created by Андрей on 23.11.2024.
//

#ifndef SKILLBOX_STUDENT_H
#define SKILLBOX_STUDENT_H

#define JOURNAL_MAX_RECORDS 40
#define STUDENT_NAME_LENGTH 32
#define STUDENT_CLASS_LENGTH 4

typedef struct {
    char firstName[STUDENT_NAME_LENGTH];
    char lastName[STUDENT_NAME_LENGTH];
    char middleName[STUDENT_NAME_LENGTH];
    char gender;
    char className[STUDENT_CLASS_LENGTH];
    char subject[STUDENT_NAME_LENGTH];
    unsigned short int grade;
} student_t;

typedef struct {
    student_t *students[JOURNAL_MAX_RECORDS];
    unsigned int count;
} classJournal_t;


classJournal_t *scanClassJournal();

void printJournalStatistics(classJournal_t *journal);

void freeJournal(classJournal_t *journal);

#endif //SKILLBOX_STUDENT_H
