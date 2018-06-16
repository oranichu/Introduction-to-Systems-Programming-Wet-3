#ifndef GRADE_H
#define GRADE_H

#include <stdlib.h>
#include <stdio.h>
#include "course.h"
#include "list.h"
#include "mtm_ex3.h"

/**
 * Grade.h
 * Grade is a data type that contains a certain grade ,
 * plus a little more info like the Course that is belongs to ,
 * the semester it belongs to and the student ID
 *
 * Grade functions :
 *
 * gradeCreate
 * gradeCopy
 * gradeGetGrade
 * gradeGetSemester
 * gradeGetStudentId
 * gradeGetCoursePoints
 * gradeGetCourseId
 * gradeUpdate
 * gradeIsGradeInList
 * gradeIsSportCourse
 * gradeCompareById
 * gradeCompareForSort
 * gradeSortByGrade
 * gradePrint
 * gradeDestroy
 *
 */

typedef struct grade_t* Grade ;

/**
 * A return parameter for some of the functions.
 *
 * GRADE_SUCCES - if everything went perfect with no errors.
 * GRADE_NULL_ARGUMENT - if one of the parameters is NULL .
 */
typedef enum GradeResult_t {
    GRADE_SUCCES,
    GRADE_NULL_ARGUMENT,
}GradeResult;

/**
 * A few constant we use for range check.
 * Sport Courses are between 390000 to 399999.
 */
#define SPORT_COURSE_MIN 390000
#define SPORT_COURSE_MAX 399999

/**
 * Allocates a new Grade with the parameters given .
 *
 * @param
 * course - Course type of the course that the grade belongs to.
 * grade - the grade (score) that we wish to save .
 * semester - the semester number in which we've got that score.
 * student_id - the student that got this grade .
 * @return
 * NULL - if course is NULL or if there was a memorey allocation problem.
 * A new copied grade otherwize.
 */
Grade  gradeCreate(Course course, int grade,int semester,int student_id) ;

/**
 * Creates a new grade and copies all the fields from a given grade.
 * Grade is going to be a data type inside a list,
 * a copy function is required for a generic list ADT.
 * @param
 * grade - the grade that we wish to copy.
 * @return
 * NULL - if grade is NULL or there was a Memory allocation problem.
 * A copy of grade otherwize .
 */
ListElement gradeCopy(ListElement grade) ;

/**
 * Returns the grade (score) of a given grade.
 * @param
 * grade - the grade that we wish to get the grade from .
 * @return
 * -1 - if a NULL was given ,
 * the grade otherwize .
 */
int gradeGetGrade (Grade grade) ;

/**
 * Returns the semester of a given grade.
 * @param
 * grade - the grade that we wish to get the semester from.
 * @return
 * -1 - if a NULL was given
 * the semester of the grade otherwize .
 */
int gradeGetSemester (Grade grade) ;

/**
 * Returns the student ID of a given grade.
 * @param
 * grade - the grade that we wish to get the student ID from.
 * @return
 * -1 if a NULL was given
 * the semester of the grade otherwize.
 */
int gradeGetStudentId (Grade grade) ;

/**
 * Returns the course ID of a given grade.
 * @param
 * grade - the grade that we wish to get the Course ID from
 * @return
 * -1 if a NULL was given
 * the course ID of the grade otherwize.
 */
int gradeGetCourseId (Grade grade) ;

/**
 * Returns the number of course points of a given grade.
 * @param
 * grade - the grade that we wish to get the points from .
 * @return
 * -1 if a NULL was given
 * the course points of the grade otherwize.
 */
int gradeGetCoursePoints(Grade grade) ;

/**
 * Updates a grade with a new grade(score) instead of the old one.
 * @param
 * grade - the grade that we wish to change.
 * new_grade - the new grade that we wish to change with the old one.
 * @return
 * GRADE_NULL_ARGUMENT - if grade is NULL .
 * GRADE_SUCCES otherwize .
 */
GradeResult gradeUpdate(Grade grade , int new_grade) ;

/**
 * Checks if a given grade is found in a List of grades.
 * @param
 * list - a list of grades that we wish to know if the grade is in it .
 * grade - the grade that we want to check.
 * @return
 * true - if the given grade was found in the list,
 * false otherwize.
 */
bool gradeIsGradeInList (List list , Grade grade) ;

/**
 * Checks if a given grade belogs to a sport course.
 * A sport course is a course with an id in the range of 390000-399999.
 * @param
 * grade - the grade that we wish to check
 * @return
 * true - if the grade belongs to a sport course,
 * false otherwize.
 */
bool gradeIsSportCourse(Grade grade) ;

/**
 * Compares between two grades by their course ID ,
 * if course ID is equal sorts them by their semesters
 * @param
 * grade1 - first grade .
 * grade2 - second grade .
 * key - doesn't effect the sort in any way ,
 * it's just a requirement  for the sort function of the list .
 * @return
 * 1 - if the first grade course ID is bigger .
 * -1 - if the second grade course ID is bigger .
 * if course IDs are equal then it will return a positive number if the
 * semester of the first grade is bigger and a negative number otherwize .
 */
int gradeCompareById(ListElement grade1,ListElement grade2,ListSortKey key);

/**
 * Compares between two grades by their grade score ,
 * if the grades are the same we sort by their semester
 * and if the semesters are equal we will sort by their courseId.
 * the functions can sort in a descending order or ascending order ,
 * depending on the key.
 * @param
 * grade1 - first grade.
 * grade2 - second grade.
 * key - if the given key is 1 it will sort in a descending order ,
 * if the key is -1 it will sort in a ascending order.
 * @return
 * Positive number - if the first grade needs to be before
 * the second one depending on the key.
 * Negative number - if the second grade needs to be before
 * the first one depending on the key.
 */
int gradeCompareForSort(ListElement grade1,ListElement grade2
        ,ListSortKey key);

/**
 * Compares between two grades by their grade score ,
 * if grades are equal sorts them by their student ID .
 * @param
 * grade1 - first grade .
 * grade2 - second grade .
 * key - doesn't effect the sort in any way ,
 * it's just a requirement  for the sort function of the list . *
 * @return
 * 1 - if the first grade is bigger .
 * -1 - if the second grade is bigger .
 * if grades are equal then it will return a positive number if the
 * student ID of the first grade is bigger and a negative number otherwize .
 */
int gradeSortByGrade (ListElement grade1,ListElement grade2,ListSortKey key);

/**
 * Prints the grade info according to the mtmPrintGradeInfo function.
 * @param
 * output - a given output channel for the print function.
 * grade - the grade that we wish to print .
 */
void gradePrint (FILE* output,Grade grade) ;

/**
 * Deallocates a given grade .
 * @param
 * grade - the target grade to deallocate,if NULL was sent nothing will happen.
 */
void gradeDestroy(ListElement grade) ;

#endif //GRADE_H
