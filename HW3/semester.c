#include "semester.h"

/**
 * Semester.c
 *
 * All functions have explanations in Semester.h file
 * except for the static functions that have them here .
 */

/**
 * Each semester type is consisted of a list of grades that are sorted
 * by the input order , and a semester number to let us know in which semester
 * we are.
 * Semester will be inserted into a sorted linked list for Student type.
 */
struct semseter_t {
    int semester ;
    List grades ;
};

Semester semesterCreate (int semester) {
    Semester new_semester = malloc(sizeof(*new_semester)) ;
    if (new_semester==NULL) {
        return NULL ;
    }
    List grades=listCreate(gradeCopy,gradeDestroy) ;
    if (grades==NULL)  {
        free (new_semester) ;
        return NULL ;
    }
    new_semester->grades=grades ;
    new_semester->semester=semester ;
    return new_semester ;
}

ListElement semesterCopy (ListElement semester) {
    if (semester == NULL) {
        return NULL;
    }
    Semester new_semester=malloc(sizeof(*new_semester)) ;
    if (new_semester==NULL) {
        return NULL;
    }
    new_semester->grades=listCopy(((Semester)semester)->grades);
    if (new_semester->grades==NULL){
        free (new_semester) ;
        return NULL ;
    }
    new_semester->semester=(((Semester)semester)->semester);
    return new_semester ;
}

int semesterGetSemester(Semester semester) {
    return semester == NULL ? -1 : semester->semester ;
}

int semesterGetNumOfGrades(Semester semester) {
    if (semester==NULL) {
        return -1 ;
    }
    int counter = 0 ;
    LIST_FOREACH(Grade,grade,semester->grades) {
        counter++;
    }
    return counter ;
}

int semesterCompareForSort(ListElement semester1,ListElement semester2,
                           ListSortKey key){
    return semesterGetSemester((Semester)semester1) -
           semesterGetSemester((Semester)semester2) ;
}

SemesterResult semesterAddGrade (Semester semester,Grade grade) {
    if((semester==NULL)||(grade==NULL)) {
        return SEMESTER_NULL_ARGUMENT;
    }
    if (listInsertFirst(semester->grades,grade)==LIST_OUT_OF_MEMORY){
        return  SEMESTER_MEMROEY_FAIL;
    }
    return SEMESTER_SUCCES ;
}

SemesterResult semesterRemoveGrade (Semester semester ,int course_id){
    if (semester==NULL) {
        return SEMESTER_NULL_ARGUMENT ;
    }
    LIST_FOREACH(Grade,current_grade,semester->grades) {
        if(gradeGetCourseId(current_grade)==course_id) {
            if (listRemoveCurrent(semester->grades)!=LIST_SUCCESS) {
                return SEMESTER_NULL_ARGUMENT ;
            }
            return SEMESTER_SUCCES ;
        }
    }
    return SEMESTER_NO_SUCH_COURSE ;
}

SemesterResult semesterUpdateGrade (Semester semester ,
                                    int course_id , int new_grade){
    if (semester==NULL) {
        return SEMESTER_NULL_ARGUMENT ;
    }
    LIST_FOREACH(Grade,current_grade,semester->grades) {
        if(gradeGetCourseId(current_grade)==course_id) {
            Grade temp_grade=listGetCurrent(semester->grades) ;
            if (gradeUpdate(temp_grade,new_grade)==GRADE_NULL_ARGUMENT) {
                return SEMESTER_NULL_ARGUMENT;
            }
            return SEMESTER_SUCCES ;
        }
    }
    return SEMESTER_NO_SUCH_COURSE ;
}

int semesterGetTotalPoints (Semester semester) {
    if (semester==NULL) {
        return -1 ;
    }
    int sum=0 ;
    LIST_FOREACH(Grade,grade,semester->grades) {
        sum+=gradeGetCoursePoints(grade) ;
    }
    return sum ;
}

int semesterGetFailedPoints (Semester semester) {
    if (semester==NULL) {
        return -1 ;
    }
    int sum=0 ;
    LIST_FOREACH(Grade,grade,semester->grades) {
        if (gradeGetGrade(grade)<55)
            sum+=gradeGetCoursePoints(grade) ;
    }
    return sum ;
}

/**
 * A static function (only used here), that calculates
 * the total effective points and total grades of the effective courses
 * that were taken during the semester.
 * Effective courses are the  courses whose grade counts.
 * A grade doesn't count if another grade of the same course id appears later
 * in the semester.
 * Calculates them by creating a new list that only has the effective grades.
 * @param
 * semester - the semester that we wish to calculate the number of effective
 * course points and grades .
 * sum_points - a pointer to a variable that will have the
 * total effective course points if everything went good
 * sum_grades - a pointer to a variable that will have the
 * total effective grades if everything went good .
 * @return
 * SEMESTER_MEMROEY_FAIL - if there was a memorey allocation problem.
 * SEMESTER_SUCCES otherwize (everything went good and values are returned by
 * the pointers)
 */
static SemesterResult semesterGetEffective(Semester semester,
                                    int* sum_points,int* sum_grades) {
    List grades = semesterCreateEffectiveList(semester) ;
    if (grades==NULL) {
        return SEMESTER_MEMROEY_FAIL;
    }
    *sum_points=0;
    *sum_grades=0;
    LIST_FOREACH(Grade,grade,grades) {
        (*sum_grades) += (gradeGetGrade(grade)*gradeGetCoursePoints(grade));
        (*sum_points) += gradeGetCoursePoints(grade);
    }
    listDestroy(grades) ;
    return SEMESTER_SUCCES ;
}

List semesterCreateEffectiveList (Semester semester) {
    if (semester == NULL) {
        return NULL;
    }
    List list = listCreate(gradeCopy, gradeDestroy);
    if (list == NULL) {
        return NULL;
    }
    LIST_FOREACH(Grade, grade, semester->grades) {
        if (gradeIsGradeInList(list, grade)) continue;
        if (listInsertFirst(list, grade) == LIST_OUT_OF_MEMORY) {
            listDestroy(list);
            return NULL;
        }
    }
    return list ;
}
/**
 * A static function (only used here),that allocates and reverses a given list.
 * @param
 * list - the list that we want to copy and reverse .
 * @return
 * NULL - if there was a memory allocation problem ,
 * A new reversed list otherwize .
 */
static List reverseList(List list) {
    List reversed_list=listCreate(gradeCopy,gradeDestroy) ;
    if (reversed_list==NULL) {
        return NULL ;
    }
    LIST_FOREACH(Grade,grade,list) {
        if (listInsertFirst(reversed_list,grade) != LIST_SUCCESS){
            listDestroy(reversed_list);
            return NULL;
        }
    }
    return reversed_list;
}

Grade semesterGetMaxGrade (Semester semester,int course_id) {
    if (semester==NULL) {
        return NULL ;
    }
    int max_grade_score = -1 ;
    Grade max_grade = NULL ;
    LIST_FOREACH(Grade,grade,semester->grades){
        if (gradeGetCourseId(grade)==course_id){
            int temp_grade_score=gradeGetGrade(grade);
            if(temp_grade_score>max_grade_score) {
                max_grade_score=temp_grade_score;
                max_grade=grade ;
            }
        }
    }
    return max_grade ; //returns null if no such course is found
}

bool semesterCheckGradeExist(Semester semester,int course_id){
    LIST_FOREACH(Grade,grade,semester->grades){
        if (gradeGetCourseId(grade)==course_id){
            return true ;
        }
    }
    return false ;
}

SemesterResult semesterPrint(FILE* output,Semester semester)  {
    if (semester==NULL) {
        return SEMESTER_NULL_ARGUMENT ;
    }
    List reversed_list = reverseList(semester->grades) ;
    if (reversed_list==NULL) {
        return SEMESTER_MEMROEY_FAIL ;
    }
    LIST_FOREACH(Grade,grade,reversed_list) {
        gradePrint(output,grade) ;
    }
    int effective_points , effective_grades ;
    if (semesterGetEffective(semester,&effective_points,&effective_grades)
        ==SEMESTER_MEMROEY_FAIL){
        listDestroy(reversed_list);
        return SEMESTER_MEMROEY_FAIL;
    }
    mtmPrintSemesterInfo(output,semesterGetSemester(semester),
                         semesterGetTotalPoints(semester),semesterGetFailedPoints(semester)
            ,effective_points,effective_grades);
    listDestroy(reversed_list);
    return SEMESTER_SUCCES ;
}

void semesterDestroy(ListElement semester) {
    if ((Semester)semester==NULL) {
        return;
    }
    if (((Semester)semester)->grades!=NULL){
        listDestroy(((Semester)semester)->grades);
    }
    free(semester) ;
}





