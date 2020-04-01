#ifndef COURSE_MANAGER_H
#define COURSE_MANAGER_H

#include "student.h"
#include "mtm_ex3.h"

/**
 * CourseManager.h
 * CourseManager is a data type that contains a set of students ,
 * and information on a logged student (a pointer to him and his ID).
 *
 * CourseManager functions :
 * courseManagerCreate
 * courseManagerAddStudent
 * courseManagerRemoveStudent
 * courseManagerLogin
 * courseManagerLogout
 * courseManagerFriendRequest
 * courseManagerHandleRequest
 * courseManagerUnfriend
 * courseManagerAddGrade
 * courseManagerRemoveGrade
 * courseManagerUpdateGrade
 * courseManagerPrintFull
 * courseManagerPrintClean
 * courseManagerPrintMaxMin
 * courseManagerReference
 * courseManagerRequest
 * courseManagerDestroy
 */
typedef struct CourseManager_t* CourseManager ;

/**
 * A return parameter for some of the functions .
 *
 * COURSE_MANAGER_SUCCESS - if everything went perfect with no errors.
 * COURSE_MANAGER_MEM_PROBLEM - if there was a memory allocation problem .
 * COURSE_MANAGER_INVALID_PARAMETERS - if one of the parameters was NULL .
 * COURSE_MANAGER_STUDENT_EXISTS - if a student already exists in the set of
 * students.
 * COURSE_MANAGER_NO_SUCH_STUDENT - if no such student exists in the set of
 * students.
 * COURSE_MANAGER_ALREADY_LOGGED - if there's already a logged student in the
 * course manager .
 * COURSE_MANAGER_NO_LOGGED_STUDENT - if there's not a logged student in the
 * course manager .
 * COURSE_MANAGER_ALREADY_FRIEND - if a student is already a friend of the given
 * student id or if a friend request was sent from a student to himself .
 * COURSE_MANAGER_ALREADY_REQUESTED - if a friend request already exist
 * from a given student .
 * COURSE_MANAGER_NO_SUCH_REQUEST -if there was no request from a given student.
 * COURSE_MANAGER_NOT_FRIEND - if a given student id wasn't found in the student
 * friends set
 * COURSE_MANAGER_NO_SUCH_COURSE - if a given course wasn't found in the student
 * semester list .
 */
typedef enum CourseManagerResult_t {
    COURSE_MANAGER_SUCCESS,
    COURSE_MANAGER_MEM_PROBLEM,
    COURSE_MANAGER_INVALID_PARAMETERS,
    COURSE_MANAGER_STUDENT_EXISTS ,
    COURSE_MANAGER_NO_SUCH_STUDENT,
    COURSE_MANAGER_ALREADY_LOGGED,
    COURSE_MANAGER_NO_LOGGED_STUDENT,
    COURSE_MANAGER_ALREADY_FRIEND,
    COURSE_MANAGER_ALREADY_REQUESTED,
    COURSE_MANAGER_NO_SUCH_REQUEST,
    COURSE_MANAGER_NOT_FRIEND,
    COURSE_MANAGER_NO_SUCH_COURSE,
}CourseManagerResult;

/**
 * A few constant we use for range check.
 * Student ID is between 0 to 1000000000
 * Course ID is between 0 to 1000000
 * Grade is between 0 to 100
 */
#define MIN_ID 0
#define MAX_ID 1000000000
#define MIN_COURSE_ID 0
#define MAX_COURSE_ID 1000000
#define MIN_GRADE 0
#define MAX_GRADE 100

/**
 * Allocates and returns a new CourseManager type , creates an empty set of
 * students , and sets the logged student pointer to be NULL (which means no
 * logged student),logged id will be 0 .
 * @return
 * NULL -  if there was a memorey allocation problem
 * A new CourseManager otherwize .
 */
CourseManager courseManagerCreate() ;

/**
 * Creates and adds a new student to the set of the given CourseManger .
 * @param
 * course_manager - the course manager that we wish to add the student to .
 * id - the id of the student.
 * first_name - the student's first name .
 * last_name - the student's last name .
 * @return
 * COURSE_MANAGER_MEM_PROBLEM - if there was a memory allocation problem.
 * COURSE_MANAGER_STUDENT_EXISTS - if theres already a student with the same id
 * in the system.
 * COURSE_MANAGER_INVALID_PARAMETERS - if a NULL was given or ID is illegal .
 * COURSE_MANAGER_SUCCESS - otherwize .
 */
CourseManagerResult courseManagerAddStudent(CourseManager course_manager
        ,int id , char* first_name,char* last_name) ;

/**
 * Removes a student from the student set, also deletes all the friendships
 * he has with other students and all their requests .
 * @param
 * course_manager - the course manager that were gonna remove the student from .
 * id - the id of the student that we wish to remove
 * @return
 * COURSE_MANAGER_INVALID_PARAMETERS - if a NULL was sent .
 * COURSE_MANAGER_NO_SUCH_STUDENT - if no such student exist .
 * COURSE_MANAGER_SUCCESS - otherwize .
 */
CourseManagerResult courseManagerRemoveStudent (CourseManager course_manager
        ,int id) ;
/**
 * Loges in a student by a given ID . (saves a pointer to him,and saves his ID).
 * @param
 * course_manager - the course manger we want to login to .
 * id - the id of the student that wants to log in
 * @return
 * COURSE_MANAGER_INVALID_PARAMETERS - if a NULL was sent .
 * COURSE_MANAGER_ALREADY_LOGGED - if a student is already logged in .
 * COURSE_MANAGER_NO_SUCH_STUDENT - if no such student exist .
 * COURSE_MANAGER_SUCCESS - otherwize .
 */
CourseManagerResult courseManagerLogin (CourseManager course_manager ,int id) ;

/**
 * Loges out a student.
 * @param
 * course_manager - the course manger we want to logout from .
 * @return
 * COURSE_MANAGER_INVALID_PARAMETERS - if a NULL was sent .
 * COURSE_MANAGER_NO_LOGGED_STUDENT - if theres no student who's logged in .
 * COURSE_MANAGER_SUCCESS - otherwize .
 */
CourseManagerResult courseManagerLogout (CourseManager course_manager) ;

/**
 * Sends a friend Request from the logged student to another student by a given
 * ID.
 * @param
 * course_manager - the relevant course manager.
 * id - the id of the student that we want to send the request to.
 * @return
 * COURSE_MANAGER_INVALID_PARAMETERS - if a NULL was sent .
 * COURSE_MANAGER_NO_LOGGED_STUDENT - if theres no student who's logged in .
 * COURSE_MANAGER_NO_SUCH_STUDENT - if no such student exist .
 * COURSE_MANAGER_ALREADY_FRIEND - if the student send's a friend request to
 * himself or to another student that's already his friend .
 * COURSE_MANAGER_ALREADY_REQUESTED - there's already a pending request from him
 * COURSE_MANAGER_SUCCESS - otherwize .
 */
CourseManagerResult courseManagerFriendRequest (CourseManager course_manager
        ,int id) ;

/**
 * Handles a friend request , if the action is either accept or reject we can
 * either add a friend , or remove the request sent .
 * @param
 * course_manager - the relevant course manager.
 * id - the id of the student that we want to handel the request .
 * action - a string that is either accept or reject .
 * @return
 * COURSE_MANAGER_MEM_PROBLEM - if there was a memory allocation problem.
 * COURSE_MANAGER_NO_LOGGED_STUDENT - if there's no student who's logged in .
 * COURSE_MANAGER_NO_SUCH_STUDENT - if no such student exist .
 * COURSE_MANAGER_ALREADY_FRIEND - if the student pending request is to
 * himself or to another student that's already his friend .
 * COURSE_MANAGER_NO_SUCH_REQUEST - there's no request from the ID .
 * COURSE_MANAGER_INVALID_PARAMETERS - if the action was not accept or reject.
 * COURSE_MANAGER_SUCCESS - otherwize .
 */
CourseManagerResult courseManagerHandleRequest (CourseManager course_manager
        ,int id , char* action) ;

/**
 * Cancels a friendship between two students , removes them from each of their
 * friends set .
 * @param
 * course_manager - course_manager - the relevant course manager.
 * id - the id of the student we wish to remove from our friend set and remove
 * me from his friends set .
 * @return
 * COURSE_MANAGER_INVALID_PARAMETERS - if a NULL was sent.
 * COURSE_MANAGER_NO_LOGGED_STUDENT - if theres no student who's logged in .
 * COURSE_MANAGER_NO_SUCH_STUDENT - if no such student exist .
 * COURSE_MANAGER_NOT_FRIEND - if the ID that we try to remove isn't a friend
 * of the logged student.
 * COURSE_MANAGER_SUCCESS - otherwize .
 */
CourseManagerResult courseManagerUnfriend(CourseManager course_manager,int id);

/**
 * Creates and adds a grade to the logged student semester list .
 * If all parameters are legal we create a new Grade type and add it to the
 * student semester list .
 * @param
 * course_manager - the relevant course manager.
 * semester - the semester of the grade.
 * course_id - the course ID
 * points - the number of course points , comes as a string and by the help of
 * convertPoints function , it's converted to int and saves their
 * value multiplied by 2 .
 * grade - the grade (score) we wish to enter .
 * @return
 * COURSE_MANAGER_MEM_PROBLEM - if there was a memory allocation problem.
 * COURSE_MANAGER_NO_LOGGED_STUDENT - if there's no student who's logged in .
 * COURSE_MANAGER_INVALID_PARAMETERS - if a one of the parameters is illegal.
 * COURSE_MANAGER_SUCCESS - otherwize .
 */
CourseManagerResult courseManagerAddGrade (CourseManager course_manager
        ,int semester,int course_id ,char* points , int grade) ;
/**
 * Removes a grade(by his course ID)
 * from the student grade list in a given semester.
 * If student has multiple grade for the same course in that semester , it'll
 * remove his last inserted grade.
 * @param
 * course_manager - the relevant course manager.
 * semester - the semester of the grade we wish to remove .
 * course_id - the course Id of the grade we wish to remove .
 * @return
 * COURSE_MANAGER_INVALID_PARAMETERS - if a NULL was sent.
 * COURSE_MANAGER_NO_LOGGED_STUDENT - if there's no student who's logged in .
 * COURSE_MANAGER_NO_SUCH_COURSE - if no such course exists .
 * COURSE_MANAGER_SUCCESS - otherwize .
 */
CourseManagerResult courseManagerRemoveGrade(CourseManager course_manager
        ,int semester , int course_id) ;

/**
 * Updates a given grade (by course ID) with a new grade (score) , updates the
 * latest grade of the given course ID (the latest semester).
 * @param
 * course_manager - the relevant course manager.
 * course_id - the course Id of the grade we wish to update .
 * new_grade - the new grade that'll be put instead of the old one.
 * @return
 * COURSE_MANAGER_NO_LOGGED_STUDENT - if there's no student who's logged in .
 * COURSE_MANAGER_NO_SUCH_COURSE - if no such course exists .
 * COURSE_MANAGER_INVALID_PARAMETERS - if the new grade was illegal.
 * COURSE_MANAGER_SUCCESS - otherwize .
 */
CourseManagerResult courseManagerUpdateGrade(CourseManager course_manager
        , int course_id , int new_grade) ;

/**
 * Prints the entire grade sheet of a student , first prints the student info ,
 * then prints the grades (in the insert order) for each semester with semester
 * info at the end of each grade list (for that semester) , in the end
 * a full summary will be printed .
 * @param
 * output - a given output channel for the print function.
 * course_manager - the course manager of the logged student we wish to print.
 * @return
 * COURSE_MANAGER_NO_LOGGED_STUDENT - if there's no student who's logged in .
 * COURSE_MANAGER_MEM_PROBLEM - if there was a memory allocation problem.
 * COURSE_MANAGER_SUCCESS - otherwize.
 */
CourseManagerResult courseManagerPrintFull(FILE* output
        ,CourseManager course_manager) ;
/**
 * Prints all the effective grades that a student has from all of his semesters.
 * Sorted by their course ID for courses with the same ID it'll be sorted
 * by their semester number .
 * @param
 * output - a given output channel for the print function.
 * course_manager - the course manager of the logged student we wish to print.
 * @return
 * COURSE_MANAGER_NO_LOGGED_STUDENT - if there's no student who's logged in .
 * COURSE_MANAGER_MEM_PROBLEM - if there was a memory allocation problem.
 * COURSE_MANAGER_SUCCESS - otherwize.
 */
CourseManagerResult courseManagerPrintClean(FILE* output
        ,CourseManager course_manager) ;

/**
 * Prints the students best/worst grades in a descending order ,
 * by the amount given.
 * if grades are equal , sort by semester number, if semesters are equal ,
 * sort by course ID .
 * if you wish to get the best grades key will be set to 1 .
 * if you wish to get the worst grades key will be set to -1 .
 * @param
 * output - a given output channel for the print function.
 * course_manager - the course manager of the logged student we wish to print.
 * amount - the amount of best grades we want to print.
 * key - a key to determant weather we want to print the best or worst grades ,
 * set to 1 if you wish to print best , set to -1 if you wish to print worst.
 * @return
 * COURSE_MANAGER_NO_LOGGED_STUDENT - if there's no student who's logged in .
 * COURSE_MANAGER_MEM_PROBLEM - if there was a memory allocation problem.
 * COURSE_MANAGER_INVALID_PARAMETERS - if the amount is illegal(amount<=0).
 * COURSE_MANAGER_SUCCESS - otherwize.
 */
CourseManagerResult courseManagerPrintMaxMin(FILE* output
        ,CourseManager course_manager,int amount,int key) ;

/**
 * Prints the student friends who scored the best grade on a given course
 * (by a given course ID),the function goes through the students friend set,
 * and gets their all time best grade in that subject (not just effective),
 * then prints the friends who scored the best (by the amount given).
 * if multiple students have the same grade it'll sort them by their ID.
 * @param
 * output - a given output channel for the print function.
 * course_manager - the course manager of the logged student we wish to print.
 * course_id - the course id of the course we want to get the best grade from.
 * amount - the amount of friends we wish to print.
 * @return
 * COURSE_MANAGER_NO_LOGGED_STUDENT - if there's no student who's logged in .
 * COURSE_MANAGER_MEM_PROBLEM - if there was a memory allocation problem.
 * COURSE_MANAGER_INVALID_PARAMETERS - if the amount is illegal(amount<=0).
 * COURSE_MANAGER_SUCCESS - otherwize.
 */
CourseManagerResult courseManagerReference (FILE* output
        ,CourseManager course_manager , int course_id ,int amount );

/**
 * Checks if a given student request is legit , if the request is legit
 * prints a massage of "your request was rejected", prints through the
 * mtmFacultyResponse function .
 * @param
 * output - a given output channel for the print function.
 * course_manager - the relevent course manager.
 * course_id - the course id we wish to have a reqest to.
 * request - a string which contains the request could be one of three options
 * "cancel_course","register_course" or "remove_course" anything else is illegal
 * @return
 * COURSE_MANAGER_NO_LOGGED_STUDENT - if there's no student who's logged in .
 * COURSE_MANAGER_INVALID_PARAMETERS - if the request is illegal.
 * COURSE_MANAGER_NO_SUCH_COURSE - if the request is "remove_course" , and no
 * such course was found in the logged student grades.
 * COURSE_MANAGER_SUCCESS - otherwize.
 */
CourseManagerResult courseManagerRequest (FILE* output
        ,CourseManager course_manager,int course_id,char* request);

/**
 * Deallocates a given course manager .
 * @param
 * course_manager - the target student to deallocate,
 * if NULL was sent nothing will happen.
 */
void courseManagerDestroy(CourseManager course_manager) ;

#endif //COURSE_MANAGER_H
