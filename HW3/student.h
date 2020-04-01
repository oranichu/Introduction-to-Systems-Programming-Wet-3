#ifndef STUDENT_H
#define STUDENT_H

#include "semester.h"
#include <string.h>
#include "set.h"

/**
 * Student.h
 * Student is a data type that contains a given student first and last name ,
 * ID , a set of friends , a set of request and a sorted list of semesters.
 *
 * Student functions :
 *
 * studentCreate
 * studentCopy
 * studentGetId
 * studentGetFriends
 * studentGetSemesterList
 * studentCheckIfFriend
 * studentCheckIfRequested
 * studentCompare
 * studentAddRequest
 * studentRemoveRequest
 * studentAddFriend
 * studentRemoveFriend
 * studentAddGrade
 * studentRemoveGrade
 * studentUpdateGrade
 * studentGetTotalPoints
 * studentGetFailPoints
 * studentCreateEffectiveList
 * studentGetEffective
 * studentGetMaxGrade
 * studentCheckGradeExist
 * studentPrintName
 * studentPrint
 * studentDestroy
 */
typedef struct Student_t* Student ;

/**
 * A return parameter for some of the functions .
 *
 * STUDENT_SUCCESS - if everything went perfect with no errors.
 * STUDENT_NULL_ARGUMENT -  if one of the parameters was NULL .
 * STUDENT_MEM_PROBLEM - if there was a memory allocation problem .
 * STUDENT_REQUEST_ALREADY_EXIST - if a friend request already exist
 * from a given student .
 * STUDENT_ALREADY_FRIEND - if a student is already a friend of the given
 * student id or if a friend request was sent from a student to himself .
 * STUDENT_NO_SUCH_REQUEST - if there was no request from a given student.
 * STUDENT_NO_SUCH_FRIEND - if a given student id wasn't found in the student
 * friends set .
 * STUDENT_NO_SUCH_COURSE - if a given course wasn't found in the student
 * semester list .
 */
typedef enum StudentResult_t {
    STUDENT_SUCCESS,
    STUDENT_NULL_ARGUMENT,
    STUDENT_MEM_PROBLEM,
    STUDENT_REQUEST_ALREADY_EXIST,
    STUDENT_ALREADY_FRIEND,
    STUDENT_NO_SUCH_REQUEST,
    STUDENT_NO_SUCH_FRIEND,
    STUDENT_NO_SUCH_COURSE
}StudentResult;

/**
 * Allocates and puts a new Student type into a given pointer to a student
 * through the parameters (there could be a problem with parameters or with
 * memory allocation problem and we need to distinguish between the two , so
 * we can't return a Student through the function).
 * creates a new semester list , set of friends and a set of requests.
 * @param
 * id - the id of a the student that we wish to create.
 * first_name - the first name of the student we wish to create.
 * last_name -  the last name of the student we wish to create.
 * student - a pointer to the student , the data will be allocated to here.
 * @return
 * STUDENT_NULL_ARGUMENT - if one of the parameters was NULL .
 * STUDENT_MEM_PROBLEM - if there was a memorey allocation problem.
 * STUDENT_SUCCESS - otherwize .
 */
StudentResult studentCreate (int id,char* first_name,char* last_name
        ,Student *student) ;

/**
 * Creates a new student type and copies all the fields from a given student.
 * @param
 * student - the student that we wish to copy .
 * @return
 * NULL if student was NULL or if there was a memorey allocation problem,
 * A new copy of student otherwize.
 */
SetElement studentCopy (ListElement student) ;

/**
 * Returns the student ID .
 * @param
 * student - the student we wish to get the ID from .
 * @return
 * -1 if a NULL was sent ,
 * The student ID otherwize.
 */
int studentGetId(Student student) ;
/**
 * Copies and returns the set of friends that the student has .
 * @param
 * student -  the student we wish to get the set of friends from.
 * @return
 * NULL if a NULL was sent , or if there was a memory allocation problem,
 * A new copy of the student friends set.
 */
Set studentGetFriends(Student student) ;

/**
 * Copies and returns the list of semester that the student has.
 * @param
 * student - the student that we wish to get the list of semesters from.
 * @return
 * NULL if a NULL was sent , or if there was a memory allocation problem,
 * A new copy of the semesters list otherwize .
 */
List studentGetSemesterList(Student student) ;

/**
 * Checks if a given student (by ID) is friend of another
 * student(Given by Student)
 * @param
 * student - the "main" student were gonna check if the otherone is his friend.
 * id - the id of the friend that we wish to check.
 * @return
 * false - if the're not friends ,
 * true - if the're friends.
 */
bool studentCheckIfFriend (Student student,int id) ;

/**
 * Checks if a given student (by ID) has a friend  request from another
 * student(Given by Student)
 * @param
 * student - the "main" student were gonna check if he received any requests.
 * id - the id of the friend request that we wish to check.
 * @return
 * false - if such request doesn't exists   ,
 * true - if such request exists.
 */
bool studentCheckIfRequested (Student student,int id) ;

/**
 * A compare function for a creation of a set of student (for Course Manager)
 * compares between two students IDs .
 * @param
 * student1 - first student.
 * student2 - second student.
 * @return
 * a positive number - if the first student ID is bigger .
 * a negative number - if the second student ID is bigger .
 * 0 - if student ID are equal.
 */
int studentCompare (SetElement student1,SetElement student2) ;

/**
 * Adds a request from a given ID to a student.
 * @param
 * student - the student we wish to add the request to .
 * id - the id of the student that sended a request.
 * @return
 * STUDENT_NULL_ARGUMENT - if a NULL was sent .
 * STUDENT_MEM_PROBLEM - if there was a memory allocation problem.
 * STUDENT_REQUEST_ALREADY_EXIST - if the student already has a request
 * form the given ID .
 * STUDENT_SUCCESS -  if we successfully added a request from the given ID .
 */
StudentResult studentAddRequest  (Student student,int id) ;

/**
 * Removes a request (from a given ID) to a student.
 * @param
 * student - the student that we wish to remove one of his pending requests .
 * id - the id of the request we wish to remove.
 * @return
 * STUDENT_NULL_ARGUMENT - if a NULL was sent.
 * STUDENT_NO_SUCH_REQUEST - if there was no request from the given ID.
 * STUDENT_SUCCESS - if we successfully removed a request from the given ID.
 */
StudentResult studentRemoveRequest(Student student,int id) ;

/**
 * Adds a friend (by a given ID) to the student friends list.
 * @param
 * student - the student we wish to add the given ID as friend .
 * id - the ID of the friend we wish to add .
 * @return
 * STUDENT_NULL_ARGUMENT - if NULL was sent.
 * STUDENT_MEM_PROBLEM - if there was a memory allocation problem.
 * STUDENT_ALREADY_FRIEND - if the student is already friends with ID
 * STUDENT_SUCCESS - if we've added a friend successfully.
 */
StudentResult studentAddFriend (Student student,int id) ;

/**
 * Removes a friend (by a given ID) from the student friends list.
 * @param
 * student - the student(By ID) we wish to remove ID as friend .
 * id - the ID of the friend we wish to remove .
 * @return
 * STUDENT_NULL_ARGUMENT - if NULL was sent.
 * STUDENT_NO_SUCH_FRIEND - if there's no such ID in the student friend set.
 * STUDENT_SUCCESS - if we've added a friend successfully.
 */
StudentResult studentRemoveFriend (Student student,int id) ;

/**
 * Adds a new grade to the student semester list , if no such semester exist ,
 * it'll create a new semester and insert it in order to the list
 * (latest semester first) , keeps the grades by insertion order .
 * @param
 * student - the student we wish to add the grade to .
 * semester - the semester which the grade belongs to .
 * grade - the grade that we wish to add .
 * @return
 * STUDENT_NULL_ARGUMENT - if a NULL was sent .
 * STUDENT_MEM_PROBLEM - if there was a memory allocation problem.
 * STUDENT_SUCCESS - if a grade was added successfully .
 */
StudentResult studentAddGrade (Student student,int semester,Grade grade) ;

/**
 * Removes a grade from the student semester list , by a given course ID ,
 * if multiple grades with the same course ID exist it'll remove the last one.
 * (which is the first one it bumps into in the grade list).
 * If the semester is left empty with no grades , Student remove grade will
 * destroy and free all the memory of that semester.
 * @param
 * student - the student we wish to remove the grade from .
 * semester - the semester of which the grade belgons to .
 * course_id - the course ID of the grade we wish to remove .
 * @return
 * STUDENT_NULL_ARGUMENT - if a NULL was sent.
 * STUDENT_NO_SUCH_COURSE - if no such course exist in the given semester.
 * STUDENT_SUCCESS - if the grade was removed successfully.
 */
StudentResult studentRemoveGrade (Student student,int semester,int course_id) ;

/**
 * Updates a grade from the student semester list , by a given course ID ,
 * if multiple grades with the same course ID exist it'll remove the last one
 * from the latest semester in the student semester list.
 * (which is the first one it bumps into in the semester list).
 * @param
 * student - the student we wish to update the grade from .
 * course_id - the course ID of the grade we wish to update .
 * new_grade - the new grade we wish to update.
 * @return
 * STUDENT_NULL_ARGUMENT - if a NULL was sent.
 * STUDENT_NO_SUCH_COURSE - if no such course exist
 * in the given student semester and grades lists.
 * STUDENT_SUCCESS - if the grade was updated successfully.
 */
StudentResult studentUpdateGrade(Student student,int course_id,int new_grade) ;

/**
 * Calculates the total points that were taken during all of the student
 * semesters , A course that was taken multiple times
 * it's course points will be calculated multiple times aswell.
 * @param
 * student - the student that we wish to calculate the number of
 * total course points
 * @return
 * -1 if NULL was given ,
 * the total course points otherwize .
 */
int studentGetTotalPoints (Student student) ;

/**
 * Calculates the total failed points that were failed during all of the student
 * semesters, A course that was failed multiple times
 * it's course points will be calculated multiple times aswell.
 * @param
 * student - the student that we wish to calculate the number of
 * failed course points
 * @return
 * -1 if NULL was given ,
 * the total failed course points otherwize .
 */
int studentGetFailPoints (Student student) ;

/**
 * Returns a fully effective grade list from all the semesters the a given
 * student has , by using the merge effective list function above .
 * @param
 * student - the student we wish to create an effective grade list from .
 * @return
 * NULL - if a NULL was sent or there was a memory allocation problem.
 * A fully effective grade list otherwize.
 */
List studentCreateEffectiveList(Student student) ;

/**
 * Calculates the total grades and course points of all the effective courses
 * that the given student has had in all of his semesters.
 * @param
 * student - the student we wish to get the effective grades and
 * course points from .
 * sum_points - a pointer to a variable that will have the
 * total effective course points if everything went good
 * sum_grades - a pointer to a variable that will have the
 * total effective grades if everything went good .
 * @return
 * STUDENT_MEM_PROBLEM - if there was a memory allocation problem.
 * STUDENT_SUCCESS - otherwize .
 */
StudentResult studentGetEffective (Student student,int* sum_points
        ,int* sum_grades) ;

/**
 * Returns a pointer to the maximum grade that the given student has , of a
 * given course ID
 * @param
 * student - the student that we want to get the max grade from.
 * course_id - the course ID of the grade we want to get.
 * @return
 * NULL - if a NULL was sent ,
 * The maximum grade - otherwize.
 */
Grade studentGetMaxGrade (Student student,int course_id) ;

/**
 * Checks if a given grade(by course ID) exist in the student semester list.
 * @param
 * student - the student we wish to check if the course exist in .
 * course_id - the course ID of the grade we want to check .
 * @return
 * false - if no such course ID was found .
 * true - if found .
 */
bool studentCheckGradeExist (Student student,int course_id);

/**
 * Prints the students name according to the mtmPrintStudentName function.
 * @param
 * output - a given output channel for the print function.
 * student - the student that we wish to print the name of .
 */
void studentPrintName(FILE* output,Student student) ;

/**
 * Prints student info according to the mtmPrintStudentInfo function.
 * @param
 * output - a given output channel for the print function.
 * student - the student that we wish to print the name of .
 */
void studentPrint(FILE* output,Student student) ;

/**
 * Deallocates a given student .
 * @param
 * student - the target student to deallocate,
 * if NULL was sent nothing will happen.
 */
void studentDestroy(SetElement student) ;

#endif //STUDENT_H
