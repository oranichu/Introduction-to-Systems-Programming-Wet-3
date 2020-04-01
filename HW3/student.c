#include "student.h"
/**
 * Student.c
 *
 * All functions have explanations in Student.h file
 * except for the static functions that have them here .
 */

/**
 * Each student type is consisted of a list of semester ,
 * set of friends , set of friend requests , his id , first and last name .
 * semester list will be sorted in a descending order (latest first).
 */
struct Student_t {
    int id ;
    char* first_name ;
    char* last_name ;
    Set friends ;
    Set requests ;
    List semesters ;
};

/**
 * A copy function for integers for the friends and requests set.
 * @param
 * element - the element we wish to copy.
 * @return
 * NULL - if a NULL was sent or if there was a memory allocation problem.
 * A new element copy - otherwize.
*/
static SetElement copyInt (SetElement element) {
    if (element==NULL) {
        return NULL ;
    }
    int* new_int = malloc(sizeof(*new_int)) ;
    if (new_int==NULL) {
        return NULL ;
    }
    *new_int=*(int*)element ;
    return new_int ;
}

/**
 * A free function for integers for the friends and requests set.
 * @param
 * element - the element we wish to free.
*/
static void freeInt (SetElement element)  {
    if (element!=NULL) {
        free(element) ;
    }
}

/**
 * A compare function for integers for the friends and requests set.
 * @param
 * element1 - first element.
 * element2 - second element.
 * @return
 * A positive number - if the first element is bigger .
 * A negative number - if the second element is bigger .
 * 0 - if the element are equal.
*/
static int compareInt(SetElement element1,SetElement element2) {
    return *(int*)element1 - *(int*)element2 ;
}

/**
 * Allocates and duplicates a given string to a new string (and returns it).
 * in use at the copy student function (for copying his first and last name).
 * @param
 * string - the new string that we wish to copy.
 * @return
 * NULL - if a null was given or if there was a memory allocation problem.
 * A new copy of the string - otherwize.
 */
static char* duplicateString(char* string) {
    if (string == NULL) {
        return NULL ;
    }
    char* new_string=malloc(strlen(string) + 1) ;
    if (new_string==NULL) {
        return NULL;
    }
    return strcpy(new_string,string) ;
}

StudentResult studentCreate (int id,char* first_name,char* last_name
        ,Student *student) {
    if ((first_name==NULL)||(last_name==NULL)||(student==NULL)){
        return STUDENT_NULL_ARGUMENT ;
    }
    (*student)=malloc(sizeof(*(*student)));
    if ((*student)==NULL) {
        return STUDENT_MEM_PROBLEM;
    }
    (*student)->first_name=duplicateString(first_name) ;
    if ((*student)->first_name==NULL) {
        studentDestroy (*student) ;
        return STUDENT_MEM_PROBLEM ;
    }
    (*student)->last_name=duplicateString(last_name) ;
    if ((*student)->last_name==NULL) {
        studentDestroy (*student) ;
        return STUDENT_MEM_PROBLEM ;
    }
    (*student)->friends=setCreate(copyInt,freeInt,compareInt) ;
    if ((*student)->friends==NULL) {
        studentDestroy(*student) ;
        return STUDENT_MEM_PROBLEM ;
    }
    (*student)->requests=setCreate(copyInt,freeInt,compareInt) ;
    if ((*student)->requests==NULL) {
        studentDestroy(*student) ;
        return STUDENT_MEM_PROBLEM ;
    }
    (*student)->semesters=listCreate(semesterCopy,semesterDestroy) ;
    if ((*student)->friends==NULL) {
        studentDestroy(*student) ;
        return STUDENT_MEM_PROBLEM ;
    }
    (*student)->id=id ;
    return STUDENT_SUCCESS ;
}

SetElement studentCopy (ListElement student) {
    if (student == NULL) {
        return NULL;
    }
    Student new_student;
    if (studentCreate(((Student) student)->id, ((Student) student)->first_name,
                      ((Student) student)->last_name, &new_student) !=
        STUDENT_SUCCESS) {
        return NULL;
    }
    setDestroy(new_student->friends);
    new_student->friends = setCopy(((Student) student)->friends);
    if (new_student->friends == NULL) {
        studentDestroy(new_student);
        return NULL;
    }
    setDestroy(new_student->requests);
    new_student->requests = setCopy(((Student) student)->requests);
    if (new_student->requests == NULL) {
        studentDestroy(new_student);
        return NULL;
    }
    listDestroy(new_student->semesters);
    new_student->semesters=listCopy(((Student)student)->semesters) ;
    if (new_student->semesters==NULL) {
        studentDestroy(new_student) ;
        return NULL ;
    }
    return new_student ;
}

int studentGetId(Student student) {
    if (student==NULL) {
        return -1 ;
    }
    return student->id ;
}

Set studentGetFriends(Student student) {
    if (student==NULL) {
        return NULL ;
    }
    return setCopy(student->friends) ;
}

List studentGetSemesterList(Student student) {
    if(student==NULL) {
        return NULL ;
    }
    return listCopy(student->semesters) ;
}

bool studentCheckIfFriend (Student student,int id) {
    if (student==NULL) {
        return false ;
    }
    return setIsIn(student->friends,&id) ;
}

bool studentCheckIfRequested (Student student,int id) {
    if (student==NULL) {
        return false ;
    }
    return setIsIn(student->requests,&id) ;
}

int studentCompare (SetElement student1,SetElement student2) {
    return (((Student)student1)->id - ((Student)student2)->id) ;
}

StudentResult studentAddRequest  (Student student,int id) {
    if (student==NULL) {
        return STUDENT_NULL_ARGUMENT ;
    }
    SetResult result=setAdd(student->requests,&id) ;
    switch (result) {
        case SET_NULL_ARGUMENT : return STUDENT_NULL_ARGUMENT ;
        case SET_OUT_OF_MEMORY : return STUDENT_MEM_PROBLEM ;
        case SET_ITEM_ALREADY_EXISTS : return STUDENT_REQUEST_ALREADY_EXIST ;
        default: return STUDENT_SUCCESS ;
    }
}

StudentResult studentRemoveRequest(Student student,int id) {
    if (student==NULL) {
        return STUDENT_NULL_ARGUMENT ;
    }
    SetResult result=setRemove(student->requests,&id) ;
    switch (result) {
        case SET_NULL_ARGUMENT : return STUDENT_NULL_ARGUMENT ;
        case SET_ITEM_DOES_NOT_EXIST : return STUDENT_NO_SUCH_REQUEST ;
        default: return STUDENT_SUCCESS ;
    }
}

StudentResult studentAddFriend (Student student,int id) {
    if (student==NULL) {
        return STUDENT_NULL_ARGUMENT ;
    }
    SetResult result=setAdd(student->friends,&id) ;
    switch (result) {
        case SET_NULL_ARGUMENT : return STUDENT_NULL_ARGUMENT ;
        case SET_OUT_OF_MEMORY : return STUDENT_MEM_PROBLEM ;
        case SET_ITEM_ALREADY_EXISTS : return STUDENT_ALREADY_FRIEND;
        default: return STUDENT_SUCCESS ;
    }
}

StudentResult studentRemoveFriend (Student student,int id) {
    if (student==NULL) {
        return STUDENT_NULL_ARGUMENT ;
    }
    SetResult result=setRemove(student->friends,&id) ;
    switch (result) {
        case SET_NULL_ARGUMENT : return STUDENT_NULL_ARGUMENT ;
        case SET_ITEM_DOES_NOT_EXIST : return STUDENT_NO_SUCH_FRIEND ;
        default: return STUDENT_SUCCESS ;
    }
}
/**
 * Adds a new semester type to the student semester list.
 * Adds the new semester by order , the first semester is the latest one.
 * So that the semester list will be kept sorted in a descending order.
 * @param
 * student - the student we wish to add the new semester to .
 * semester - the new semester to be added.
 * @return
 * STUDENT_NULL_ARGUMENT - if a NULL was sent .
 * STUDENT_MEM_PROBLEM - if there was a memory allocation problem.
 * STUDENT_SUCCESS - if a new semester was successfully added .
 */
static StudentResult addNewSemester(Student student,Semester semester){
    if ((student==NULL)||(semester==NULL)) {
        return STUDENT_NULL_ARGUMENT ;
    }
    if (listGetSize(student->semesters)==0) {
        if (listInsertFirst(student->semesters,semester)!=LIST_SUCCESS){
            return STUDENT_MEM_PROBLEM;
        }
        return STUDENT_SUCCESS ;
    }
    LIST_FOREACH(Semester,current,student->semesters) {
        if (semesterGetSemester(current) < semesterGetSemester(semester)) {
            if (listInsertBeforeCurrent(student->semesters,semester)
                !=LIST_SUCCESS){
                return STUDENT_MEM_PROBLEM;
            }
            return STUDENT_SUCCESS ;
        }
    }
    if (listInsertLast(student->semesters,semester)!=LIST_SUCCESS){
        return STUDENT_MEM_PROBLEM;
    }
    return STUDENT_SUCCESS ;
}

StudentResult studentAddGrade (Student student,int semester,Grade grade) {
    if ((student == NULL) || (grade == NULL)) {
        return STUDENT_NULL_ARGUMENT;
    }
    LIST_FOREACH(Semester,current,student->semesters){
        if (semesterGetSemester(current)==semester) {
            if(semesterAddGrade(current,grade)!=SEMESTER_SUCCES) {
                return STUDENT_MEM_PROBLEM ;
            }
            return STUDENT_SUCCESS ;
        }
    } // if we have'nt added a grade yet it means no such semester exist
    Semester new_semester=semesterCreate (semester) ;
    if(semesterAddGrade(new_semester,grade)!=SEMESTER_SUCCES) {
        semesterDestroy(new_semester) ;
        return STUDENT_MEM_PROBLEM ;
    }
    if (addNewSemester(student,new_semester)!=STUDENT_SUCCESS) {
        semesterDestroy(new_semester) ;
        return STUDENT_MEM_PROBLEM ;
    }
    semesterDestroy(new_semester) ;
    return STUDENT_SUCCESS ;
}

StudentResult studentRemoveGrade(Student student,int semester,int course_id) {
    if ((student==NULL)) {
        return STUDENT_NULL_ARGUMENT ;
    }
    LIST_FOREACH(Semester,current,student->semesters){
        if (semesterGetSemester(current)==semester) {
            if(semesterRemoveGrade(current,course_id)==SEMESTER_SUCCES){
                if (semesterGetNumOfGrades(current)==0){
                    listRemoveCurrent(student->semesters);
                }
                return STUDENT_SUCCESS ;
            }
            return STUDENT_NO_SUCH_COURSE ;
        }
    }
    return STUDENT_NO_SUCH_COURSE;
}

StudentResult studentUpdateGrade(Student student,int course_id,int new_grade) {
    if ((student==NULL)) {
        return STUDENT_NULL_ARGUMENT ;
    }
    LIST_FOREACH(Semester,current,student->semesters){
        if(semesterUpdateGrade(current,course_id,new_grade)==SEMESTER_SUCCES) {
            return STUDENT_SUCCESS ;
        }
    }
    return STUDENT_NO_SUCH_COURSE ;
}

int studentGetTotalPoints (Student student) {
    if (student==NULL) {
        return -1 ;
    }
    int sum=0 ;
    LIST_FOREACH(Semester,semester,student->semesters) {
        sum+=semesterGetTotalPoints(semester) ;
    }
    return sum ;
}

int studentGetFailPoints (Student student) {
    if (student==NULL) {
        return -1 ;
    }
    int sum=0 ;
    LIST_FOREACH(Semester,semester,student->semesters) {
        sum+=semesterGetFailedPoints(semester) ;
    }
    return sum ;
}

/**
 * A function that merges two effective grades lists but only adds a grade
 * if he wasn't in the list before (or if he's a sport course),
 * because the semesters are sorted in a descending order we are guaranteed
 * that all the courses will be effective courses, for a purpose of creating
 * an effective grade list from all the semesters.
 * @param
 * full_list - the fully effective grade list we wish to add more grades
 * list_to_add - the list we wish to add to the full list .
 * @return
 * STUDENT_MEM_PROBLEM - if there was a memory allocation problem.
 * STUDENT_SUCCESS - if all the grades from full list were added successfully.
 */
static StudentResult mergeEffectiveLists (List full_list,List list_to_add) {
    LIST_FOREACH(Grade,grade,list_to_add) {
        if (gradeIsGradeInList(full_list,grade)&&(!gradeIsSportCourse(grade))){
            continue ; // if it's a sport course , we will add it .
        }
        if (listInsertFirst(full_list,grade) == LIST_OUT_OF_MEMORY) {
            return STUDENT_MEM_PROBLEM;
        }
    }
    return STUDENT_SUCCESS ;
}

List studentCreateEffectiveList(Student student) {
    if (student==NULL) {
        return NULL ;
    }
    List full_list=listCreate(gradeCopy,gradeDestroy);
    if (full_list==NULL) {
        return NULL ;
    }
    LIST_FOREACH(Semester,semester,student->semesters) {
        List temp_list = semesterCreateEffectiveList(semester) ;
        if (temp_list==NULL) {
            listDestroy(full_list);
            return NULL ;
        }
        if (mergeEffectiveLists(full_list,temp_list)==STUDENT_MEM_PROBLEM){
            listDestroy(temp_list);
            listDestroy(full_list);
            return NULL;
        }
        listDestroy(temp_list);
    }
    return full_list ;
}

StudentResult studentGetEffective (Student student,int* sum_points
        ,int* sum_grades) {
    *sum_grades=0;
    *sum_points=0;
    List full_effective_list=studentCreateEffectiveList(student) ;
    if (full_effective_list==NULL){
        return STUDENT_MEM_PROBLEM;
    }
    LIST_FOREACH(Grade,grade,full_effective_list) {
        (*sum_grades)+= (gradeGetGrade(grade)*gradeGetCoursePoints(grade)) ;
        (*sum_points)+=gradeGetCoursePoints(grade);
    }
    listDestroy(full_effective_list);
    return STUDENT_SUCCESS ;
}

Grade studentGetMaxGrade (Student student,int course_id) {
    if (student==NULL) {
        return NULL ;
    }
    int max_grade_score =-1 ;
    Grade max_grade=NULL  ;
    LIST_FOREACH(Semester,semester,student->semesters) {
        Grade temp_grade = semesterGetMaxGrade(semester,course_id) ;
        int temp_grade_score=gradeGetGrade(temp_grade);
        // if temp_grade = NULL , gradeGetGrade will return -1
        if(temp_grade_score>max_grade_score) {
            max_grade=temp_grade ;
            max_grade_score=temp_grade_score ;
        }
    }// function returns a pointer to grade and not a copy
    return max_grade ; // if not such grade is found it will return NULL
}

bool studentCheckGradeExist (Student student,int course_id){
    LIST_FOREACH(Semester,semester,student->semesters){
        if (semesterCheckGradeExist(semester,course_id)){
            return true;
        }
    }
    return false ;
}

void studentPrintName(FILE* output,Student student) {
    if (student==NULL) {
        return ;
    }
    mtmPrintStudentName(output,student->first_name,student->last_name) ;
}

void studentPrint(FILE* output,Student student) {
    if (student==NULL){
        return;
    }
    mtmPrintStudentInfo(output,student->id,student->first_name
            ,student->last_name);
}

void studentDestroy(SetElement student) {
    if ((Student)student==NULL) {
        return;
    }
    if (((Student)student)->first_name!=NULL) {
        free (((Student)student)->first_name) ;
    }
    if (((Student)student)->last_name!=NULL) {
        free (((Student)student)->last_name) ;
    }
    if (((Student)student)->friends!=NULL) {
        setDestroy(((Student)student)->friends) ;
    }
    if (((Student)student)->requests!=NULL) {
        setDestroy(((Student)student)->requests) ;
    }
    if (((Student)student)->semesters!=NULL) {
        listDestroy(((Student)student)->semesters) ;
    }
    free (student) ;
}

