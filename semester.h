#ifndef SEMESTER_H
#define SEMESTER_H

#include "grade.h"
#include <stdlib.h>

/**
 * Semester.h
 * Semester is a data type that contains the semester number and all the grads
 * that are relevant to that semester .
 *
 * Semester functions :
 *
 * semesterCreate
 * semesterCopy
 * semesterGetSemester
 * semesterCompareForSort
 * semesterAddGrade
 * semesterRemoveGrade
 * semesterUpdateGrade
 * semesterGetTotalPoints
 * semesterGetFailedPoints
 * semesterGetEffective
 * semesterCreateEffectiveList
 * semesterGetMaxGrade
 * semesterCheckGradeExist
 * semesterPrint
 * semesterDestroy
 */
typedef struct semseter_t* Semester ;

/**
 * A return parameter for some of the functions .
 *
 * SEMESTER_SUCCES - if everything went perfect with no errors .
 * SEMESTER_NULL_ARGUMENT - if one of the parameters was NULL .
 * SEMESTER_MEMROEY_FAIL - if there was a memory allocation problem .
 * SEMESTER_NO_SUCH_COURSE - if no such course (as provided)
 * was not found in the semester.
 */
typedef enum SemesterResult_t {
    SEMESTER_SUCCES,
    SEMESTER_NULL_ARGUMENT,
    SEMESTER_MEMROEY_FAIL,
    SEMESTER_NO_SUCH_COURSE
}SemesterResult;

/**
 *  Allocates a new semester type , creates a new empty grades list .
 *  and defines the semester with the semester number given .
 * @param semester
 * @return
 */
Semester semesterCreate (int semester) ;
/**
 * Creates a new semester and copies all the fields from a given semester.
 * @param
 * semester - the semester that we wish to copy.
 * @return
 * NULL - if semester is NULL or there was a memory allocation problem.
 * A new copy of semester otherwize
 */
ListElement semesterCopy (ListElement semester) ;

/**
 * Returns the semester(number) of a given Semester type .
 * @param
 * semester - the semester that we wish to get the semester from.
 * @return
 * -1 - if a NULL was given
 * the semester of the given semester otherwize.
 */
int semesterGetSemester(Semester semester) ;
/**
 * Returns the number of grades that a given semester has .
 * if semester has no grades it'll return 0
 * @param
 * semester - the semester we wish to check.
 * @return
 * -1 if a NULL was sent .
 * The number of grades in that semester otherwize.
 */
int semesterGetNumOfGrades(Semester semester) ;
/**
 * Comparing between 2 given semesters (by the semester value).
 * @param
 * semester1 - first semester .
 * semester2 - second semester .
 * key - doesn't effect the sort in any way ,
 * it's just a requirement  for the sort function of the list .
 * @return
 * 0 - if both semester are equal ,
 * A positive number - if the first semester is bigger ,
 * A negative number otherwize.
 */
int semesterCompareForSort(ListElement semester1,ListElement semester2,
                           ListSortKey key);
/**
 * Adds a new grade to a given semester(adds it to the grades linked list).
 * the list is kept in the input order .
 * @param
 * semester - the semester type we wish to add the grade to .
 * grade - the grade that we wish to add to the semester.
 * @return
 * SEMESTER_NULL_ARGUMENT - if one of the argument was NULL.
 * SEMESTER_MEMROEY_FAIL - if there was a memory allocation problem
 * SEMESTER_SUCCES otherwize .
 */
SemesterResult semesterAddGrade (Semester semester,Grade grade) ;

/**
 * Removes a grade(by ID) from the grades linked list of a given semester,
 * it will remove the last grade that was added to the list of grades.
 * @param
 * semester -  the semester that we want to remove the grade from.
 * course_id - the course ID of the grade that we wish to remove.
 * @return
 * SEMESTER_NULL_ARGUMENT - if one of the parameters was NULL .
 * SEMESTER_SUCCES - if we successfully removed a grade from the grades list.
 * SEMESTER_NO_SUCH_COURSE - otherwize if no grade was removed
 * we couldn't find a course with the same ID in the grades list.
 */
SemesterResult semesterRemoveGrade (Semester semester ,int course_id);

/**
 * Updates a grade(by ID) from the grades linked list of a given semester,
 * it will update the last grade that was added to the list of grades.
 * @param
 * semester -  the semester that we want to update the grade from.
 * course_id - the course ID of the grade that we wish to update.
 * new_grade - the new grade that needs to put instead of the old one.
 * @return
 * SEMESTER_NULL_ARGUMENT - if one of the parameters was NULL .
 * SEMESTER_SUCCES - if we successfully updated a grade from the grades list.
 * SEMESTER_NO_SUCH_COURSE - otherwize if no grade was updated
 * we couldn't find a course with the same ID in the grades list.
 */
SemesterResult semesterUpdateGrade (Semester semester ,
                                        int course_id , int new_grade);

/**
 * Calculates the total points that were taken during the semester.
 * A course that was taken multiple times
 * it's course points will be calculated multiple times aswell.
 * @param
 * semester - the semester that we wish to calculate the number of course points
 * @return
 * -1 if NULL was given ,
 * the total course points otherwize .
 */
int semesterGetTotalPoints (Semester semester);

/**
 * Calculates the total failed points that were failed during the semester.
 * A course that was failed multiple times
 * it's course points will be calculated multiple times aswell.
 * @param
 * semester - the semester that we wish to calculate the number of
 * failed course points
 * @return
 * -1 if NULL was given ,
 * the total failed course points otherwize .
 */
int semesterGetFailedPoints (Semester semester) ;

/**
 * Allocates and creates a new list with the entire semester effective grades,
 * Effective grades are the grade who counts.
 * A grade doesn't count if another grade of the same course id appears later
 * in the semester.
 * @param
 * semester - the semester we wish to get the effective grades list from .
 * @return
 * NULL - if the semester was NULL or if there was a memory allocation problem
 * A new effective grades list otherwize .
 */
List semesterCreateEffectiveList (Semester semester) ;

/**
 * Returns a pointer to the maximum grade found
 * in the semester of a given course (by ID).
 * @param
 * semester - the semester we want to get the max grade from .
 * course_id - the course id of the grade we want to get .
 * @return
 * NULL - if the semester was NULL or if not such course was found,
 * the maximum grade of the course id in the semester otherwize .
 */
Grade semesterGetMaxGrade (Semester semester,int course_id) ;

/**
 * Checks if a course (by ID) is in the semester .
 * @param
 * semester - the semester we want to know if the course is in it .
 * course_id - the course ID that we want to check .
 * @return
 * false - if the course isn't found in the semester.
 * true - if the course is found in the semester.
 */
bool semesterCheckGradeExist(Semester semester,int course_id);

/**
 * Prints all the grades in the given semester (by gradePrint function) ,
 * and the semester info according to the mtmPrintSemesterInfo function.
 * @param
 * output - a given output channel for the print function.
 * semester - the semester that we wish to print .
 * @return
 * SEMESTER_NULL_ARGUMENT - if the semester is NULL .
 * SEMESTER_MEMROEY_FAIL - if there was a memory allocation problem
 * (the function reverses the grade list for a correct printing order).
 * SEMESTER_SUCCES - otherwize .
 */
SemesterResult semesterPrint(FILE* output,Semester semester)  ;

/**
 * Deallocates a given semester .
 * @param
 * semester - the target semester to deallocate,
 * if NULL was sent nothing will happen.
 */
void semesterDestroy(ListElement semester) ;
#endif //SEMESTER_H
