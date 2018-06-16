#include "course_manager.h"
/**
 * CourseManager.c
 *
 * All functions have explanations in CourseManager.h file
 * except for the static functions that have them here .
 */
struct CourseManager_t {
    Set students ;
    Student logged_student ;
    int logged_id ;
};

/**
 * A return parameter for the static check request function .
 * The request has four different types :
 * CANCEL_COURSE - if the request was "cancel_course"
 * REGISTER_COURSE - if the request was "register_course"
 * REMOVE_COURSE -if the request was "remove_course"
 * REQUEST_ILLEGAL_PARAMETER - otherwize .
 */
typedef enum RequestResult_t {
    CANCEL_COURSE,
    REGISTER_COURSE,
    REMOVE_COURSE,
    REQUEST_ILLEGAL_PARAMETER
} RequestResult;

/**
 * Checks if a given id (of student) is in the legal range.
 * @param
 * id - the id that we wish to check.
 * @return
 * true - if id is in the legal range ,
 * false - otherwize .
 */
static bool checkId(int id) {
    if ((id<=MIN_ID)||(id>=MAX_ID)){
        return false ;
    }
    return true ;
}

/**
 * Checks if the given action is legal and updates the answer into the pointer
 * for the answer that is given.
 * @param
 * action - the action that we wish to check.
 * answer - a pointer to the answer parameter , will be true if action is
 * "accept" and false if answer is reject
 * @return
 * true - if the action was either "accept" or "reject".
 * false - otherwize or if NULL was sent .
 */
static bool checkAction (char* action,bool* answer) {
    if (action==NULL) {
        return false ;
    }
    if ((strcmp(action,"accept")==0)||(strcmp(action,"accept\n")==0)) {
        *answer=true ;
        return true ;
    }
    if ((strcmp(action,"reject")==0)||(strcmp(action,"reject\n")==0)) {
        *answer=false ;
        return true ;
    }
    return false ;
}

/**
 * Checks if a given course id is in the legal range.
 * @param
 * course_id - the course_id that we wish to check.
 * @return
 * true - if course_id is in the legal range ,
 * false - otherwize .
 */
static bool checkCourseId(int course_id) {
    if ((course_id>MIN_COURSE_ID)&&(course_id<MAX_COURSE_ID)) {
        return true ;
    }
    return false ;
}

/**
 * Checks if a given grade is in the legal range.
 * @param
 * grade - the course_id that we wish to check.
 * @return
 * true - if grade is in the legal range ,
 * false - otherwize .
 */
static bool checkGrade(int grade) {
    if ((grade>=MIN_GRADE)&&(grade<=MAX_GRADE)) {
        return true ;
    }
    return false ;
}

/**
 * Converts and returns the number of course points , the course points are
 * given to us as a string and they might be of the following form (points),
 * (points).0 ,(points).5 , the functions converts the points accordingly
 * and returns their value multiplied by 2 (so that we can save them as int).
 * @param
 * points - the string that contains the points.
 * @return
 *  -1 - if a NULL was sent or if the string wasn't just with numbers .
 *  The number of course points * 2 - otherwize .
 */
static int convertPoints (char* points) {
    if (points==NULL) {
        return -1 ;
    }
    int numeric_points = 0 ,index=0,numeric_digit ;
    char digit = points[index] ;
    if ((digit=='.') || (digit=='\0')) {
        return -1 ;
    }
    while ((digit!='.')&&(digit!='\0')) {
        numeric_points*=10 ;
        numeric_digit= digit - '0' ;
        if ((numeric_digit<0)||(numeric_digit>9)) {
            return -1 ;
        }
        numeric_points+=numeric_digit ;
        digit=points[++index];
    }
    if ((digit=='\0')&&(index!=0)) {
        return (numeric_points*2) ;
    }
    digit=points[++index] ;
    if ((digit=='5')&&(points[index+1]=='\0')) {
        return (numeric_points*2+1) ;
    }
    if ((digit=='0')&&(points[index+1]=='\0')) {
        return (numeric_points*2) ;
    }
    return -1 ;
}

/**
 * A function that checks if the request is legal and returns a result value
 * so that we can tell what was the request.
 * @param
 * request - the request we wish to check.
 * @return
 * CANCEL_COURSE - if the request was "cancel_course"
 * REGISTER_COURSE - if the request was "register_course"
 * REMOVE_COURSE -if the request was "remove_course"
 * REQUEST_ILLEGAL_PARAMETER - otherwize .
 */
static RequestResult checkRequest (char* request) {
    if (strcmp("cancel_course",request)==0){
        return CANCEL_COURSE;
    }
    if (strcmp("register_course",request)==0){
        return REGISTER_COURSE;
    }
    if (strcmp("remove_course",request)==0){
        return REMOVE_COURSE;
    }
    return REQUEST_ILLEGAL_PARAMETER;
}

/**
 * Returns a pointer to a student by a given ID .
 * @param
 * course_manager - the course manager we wish to get the student from.
 * id - the ID of the requested student.
 * @return
 * NULL - if no such student was found ,
 * A pointer to the requested student otherwize .
 */
static Student getStudentFromSet (CourseManager course_manager , int id ) {
    SET_FOREACH(Student,student,course_manager->students) {
        if (studentGetId(student)==id) {
            return student ;
        }
    }
    return NULL ;
}

CourseManager courseManagerCreate() {
    CourseManager new_course_manager = malloc (sizeof(*new_course_manager));
    if (new_course_manager==NULL) {
        return NULL ;
    }
    new_course_manager->students=setCreate(studentCopy,
                                           studentDestroy,studentCompare) ;
    if (new_course_manager->students==NULL) {
        free (new_course_manager) ;
        return NULL ;
    }
    new_course_manager->logged_student=NULL ;
    new_course_manager->logged_id= 0 ;
    return new_course_manager ;
}

CourseManagerResult courseManagerAddStudent(CourseManager course_manager
        ,int id , char* first_name,char* last_name){
    if ((!course_manager)||(!first_name)||(!last_name)||
            (!checkId(id))) {
        return COURSE_MANAGER_INVALID_PARAMETERS ;
    }
    Student new_student ;
    if (studentCreate(id,first_name,last_name,&new_student)!=STUDENT_SUCCESS){
        return COURSE_MANAGER_MEM_PROBLEM ;
    }
    SetResult set_result=setAdd(course_manager->students,new_student) ;
    studentDestroy(new_student) ;
    switch (set_result) {
        case SET_OUT_OF_MEMORY : {
            return COURSE_MANAGER_MEM_PROBLEM ;
        }
        case SET_NULL_ARGUMENT: {
            return COURSE_MANAGER_MEM_PROBLEM ;
        }
        case SET_ITEM_ALREADY_EXISTS: {
            return COURSE_MANAGER_STUDENT_EXISTS ;
        }
        default:
            return COURSE_MANAGER_SUCCESS ;
    }
}

CourseManagerResult courseManagerRemoveStudent (CourseManager course_manager
        ,int id) {
    if (course_manager==NULL) {
        return COURSE_MANAGER_INVALID_PARAMETERS ;
    }
    if (!checkId(id)) {
        return COURSE_MANAGER_NO_SUCH_STUDENT ;
    }
    Student student_to_remove = getStudentFromSet(course_manager,id) ;
    if (student_to_remove==NULL) {
        return COURSE_MANAGER_NO_SUCH_STUDENT ;
    }
    SET_FOREACH(Student,student,course_manager->students) {
        studentRemoveFriend(student,id);
        studentRemoveRequest(student,id) ;
    }
    setRemove(course_manager->students,student_to_remove) ;
    return COURSE_MANAGER_SUCCESS ;
}

CourseManagerResult courseManagerLogin (CourseManager course_manager ,int id) {
    if(course_manager==NULL) {
        return COURSE_MANAGER_INVALID_PARAMETERS ;
    }
    if(course_manager->logged_student!=NULL) {
        return COURSE_MANAGER_ALREADY_LOGGED ;
    }
    course_manager->logged_student=getStudentFromSet(course_manager,id) ;
    if (course_manager->logged_student==NULL) {
        return COURSE_MANAGER_NO_SUCH_STUDENT ;
    }
    course_manager->logged_id=studentGetId(course_manager->logged_student) ;
    return COURSE_MANAGER_SUCCESS ;
}

CourseManagerResult courseManagerLogout (CourseManager course_manager) {
    if(course_manager==NULL) {
        return COURSE_MANAGER_INVALID_PARAMETERS ;
    }
    if (course_manager->logged_student==NULL) {
        return COURSE_MANAGER_NO_LOGGED_STUDENT;
    }
    course_manager->logged_student=NULL ;
    course_manager->logged_id=0 ;
    return COURSE_MANAGER_SUCCESS ;
}

CourseManagerResult courseManagerFriendRequest (CourseManager course_manager
        ,int id) {
    if (course_manager==NULL) {
        return COURSE_MANAGER_INVALID_PARAMETERS ;
    }
    if (course_manager->logged_student==NULL) {
        return  COURSE_MANAGER_NO_LOGGED_STUDENT ;
    }
    Student student=getStudentFromSet(course_manager,id) ;
    if (student==NULL) {
        return COURSE_MANAGER_NO_SUCH_STUDENT ;
    }
    if ((course_manager->logged_id==id)||
            studentCheckIfFriend(course_manager->logged_student,id)) {
        return COURSE_MANAGER_ALREADY_FRIEND ;
    } // if they are already friends or if he sends a request to himself .
    StudentResult result=studentAddRequest(student,course_manager->logged_id);
    switch (result) {
        case STUDENT_MEM_PROBLEM : return COURSE_MANAGER_MEM_PROBLEM ;
        case STUDENT_REQUEST_ALREADY_EXIST :
            return COURSE_MANAGER_ALREADY_REQUESTED ;
        default: return COURSE_MANAGER_SUCCESS ;
        }
}

CourseManagerResult courseManagerHandleRequest (CourseManager course_manager
        ,int id , char* action) {
    bool answer ;
    if (course_manager->logged_student==NULL) {
        return COURSE_MANAGER_NO_LOGGED_STUDENT ;
    }
    Student student=getStudentFromSet(course_manager,id) ;
    if (student==NULL) {
        return COURSE_MANAGER_NO_SUCH_STUDENT ;
    }
    if ((course_manager->logged_id==id)||
        studentCheckIfFriend(course_manager->logged_student,id)) {
        return COURSE_MANAGER_ALREADY_FRIEND ;
    }
    if (!studentCheckIfRequested(course_manager->logged_student,id)) {
        return COURSE_MANAGER_NO_SUCH_REQUEST ;
    }
    if ((!checkAction(action,&answer))) {
        return COURSE_MANAGER_INVALID_PARAMETERS ;
    }
    studentRemoveRequest(course_manager->logged_student,id) ;
    if (!answer) {
        return COURSE_MANAGER_SUCCESS ;
    } // if the answer is reject , nothing else to do .
    studentRemoveRequest(student,course_manager->logged_id);
    StudentResult res1 = studentAddFriend(course_manager->logged_student,id);
    StudentResult res2 = studentAddFriend(student,course_manager->logged_id);
    if ((res1==STUDENT_MEM_PROBLEM)||(res2==STUDENT_MEM_PROBLEM)) {
        return COURSE_MANAGER_MEM_PROBLEM ;
    }
    return  COURSE_MANAGER_SUCCESS ;
}

CourseManagerResult courseManagerUnfriend(CourseManager course_manager,int id){
    if (course_manager==NULL) {
        return COURSE_MANAGER_INVALID_PARAMETERS ;
    }
    if (course_manager->logged_student==NULL) {
        return COURSE_MANAGER_NO_LOGGED_STUDENT;
    }
    Student student= getStudentFromSet(course_manager,id) ;
    if (student==NULL) {
        return COURSE_MANAGER_NO_SUCH_STUDENT ;
    }
    if ((course_manager->logged_id==id)||
            (!studentCheckIfFriend(course_manager->logged_student,id))) {
        return COURSE_MANAGER_NOT_FRIEND ;
    }
    studentRemoveFriend(student,course_manager->logged_id) ;
    studentRemoveFriend(course_manager->logged_student,id) ;
    return  COURSE_MANAGER_SUCCESS ;
}

CourseManagerResult courseManagerAddGrade (CourseManager course_manager
        ,int semester,int course_id ,char* points , int grade) {
    int numeric_points = convertPoints(points);
    if (course_manager->logged_student==NULL) {
        return COURSE_MANAGER_NO_LOGGED_STUDENT ;
    }
    if ((semester<=0)||(numeric_points==-1) ||
            (!checkCourseId(course_id))||(!checkGrade(grade))){
        return COURSE_MANAGER_INVALID_PARAMETERS ;
    }
    Course course=courseCreate(course_id,numeric_points);
    if (course==NULL) {
        return COURSE_MANAGER_MEM_PROBLEM ;
    }
    Grade new_grade=gradeCreate(course,grade,semester
            ,course_manager->logged_id);
    courseDestroy(course);
    if (new_grade==NULL) {
        return COURSE_MANAGER_MEM_PROBLEM ;
    }
    if(studentAddGrade(course_manager->logged_student,semester,new_grade)
        ==STUDENT_MEM_PROBLEM) {
        gradeDestroy(new_grade) ;
        return COURSE_MANAGER_MEM_PROBLEM ;
    }
    gradeDestroy(new_grade) ;
    return COURSE_MANAGER_SUCCESS;
}

CourseManagerResult courseManagerRemoveGrade(CourseManager course_manager
        ,int semester , int course_id) {
    if (course_manager->logged_student==NULL) {
        return COURSE_MANAGER_NO_LOGGED_STUDENT ;
    }
    if ((semester<=0)||(!checkCourseId(course_id))){
        return COURSE_MANAGER_NO_SUCH_COURSE ;
    }
    if(studentRemoveGrade(course_manager->logged_student
            ,semester,course_id)==STUDENT_NO_SUCH_COURSE){
        return COURSE_MANAGER_NO_SUCH_COURSE;
    }
    return COURSE_MANAGER_SUCCESS;
}

CourseManagerResult courseManagerUpdateGrade(CourseManager course_manager
        , int course_id , int new_grade) {
    if (course_manager->logged_student == NULL) {
        return COURSE_MANAGER_NO_LOGGED_STUDENT;
    }
    if (!checkCourseId(course_id)) { //saves as time of checking.
        return COURSE_MANAGER_NO_SUCH_COURSE;
    }
    if (!studentCheckGradeExist(course_manager->logged_student,course_id)){
        return COURSE_MANAGER_NO_SUCH_COURSE;
    }
    if ((!checkGrade(new_grade))) {
        return COURSE_MANAGER_INVALID_PARAMETERS;
    }
    studentUpdateGrade(course_manager->logged_student, course_id, new_grade);
    return COURSE_MANAGER_SUCCESS;
}

CourseManagerResult courseManagerPrintFull(FILE* output
        ,CourseManager course_manager) {
    if (course_manager->logged_student == NULL) {
        return COURSE_MANAGER_NO_LOGGED_STUDENT;
    }
    List semesters=studentGetSemesterList(course_manager->logged_student);
    if (semesters==NULL) {
        return COURSE_MANAGER_MEM_PROBLEM ;
    }
    if (listSort(semesters,semesterCompareForSort,NULL)!=LIST_SUCCESS){
        listDestroy(semesters);
        return COURSE_MANAGER_MEM_PROBLEM;
    }
    studentPrint(output,course_manager->logged_student);
    LIST_FOREACH(Semester,semester,semesters) {
        if(semesterPrint(output,semester)==SEMESTER_MEMROEY_FAIL){
            listDestroy(semesters);
            return COURSE_MANAGER_MEM_PROBLEM;
        }
    }
    listDestroy(semesters) ;
    int effective_grades ,effective_points ;
    if (studentGetEffective(course_manager->logged_student
            ,&effective_points,&effective_grades)==STUDENT_MEM_PROBLEM){
        return COURSE_MANAGER_MEM_PROBLEM;
    }
    mtmPrintSummary(output,studentGetTotalPoints(course_manager->logged_student)
    ,studentGetFailPoints(course_manager->logged_student),
                    effective_points,effective_grades);
    return COURSE_MANAGER_SUCCESS;
}

CourseManagerResult courseManagerPrintClean(FILE* output
        ,CourseManager course_manager) {
    if (course_manager->logged_student == NULL) {
        return COURSE_MANAGER_NO_LOGGED_STUDENT;
    }
    List grades = studentCreateEffectiveList(course_manager->logged_student);
    if (grades==NULL) {
        return COURSE_MANAGER_MEM_PROBLEM ;
    }
    if (listSort(grades,gradeCompareById,NULL)!=LIST_SUCCESS) {
        listDestroy(grades);
        return COURSE_MANAGER_MEM_PROBLEM;
    }
    int sum_points=0,sum_grades=0;
    studentPrint(output,course_manager->logged_student);
    LIST_FOREACH(Grade,grade,grades){
        sum_grades+= (gradeGetGrade(grade)*gradeGetCoursePoints(grade)) ;
        sum_points+=gradeGetCoursePoints(grade);
        gradePrint(output,grade);
    }
    mtmPrintCleanSummary(output,sum_points,sum_grades);
    listDestroy(grades);
    return COURSE_MANAGER_SUCCESS;
}

CourseManagerResult courseManagerPrintMaxMin(FILE* output
        ,CourseManager course_manager,int amount,int key) {
    if (course_manager->logged_student == NULL) {
        return COURSE_MANAGER_NO_LOGGED_STUDENT;
    }
    if (amount<=0) {
        return COURSE_MANAGER_INVALID_PARAMETERS ;
    }
    List grades = studentCreateEffectiveList(course_manager->logged_student);
    if (grades == NULL) {
        return COURSE_MANAGER_MEM_PROBLEM;
    }
    if (listSort(grades, gradeCompareForSort,&key) != LIST_SUCCESS) {
        listDestroy(grades);
        return COURSE_MANAGER_MEM_PROBLEM;
    }
    Grade grade = listGetFirst(grades);
    for (int i=0 ; i<amount && grade!=NULL ; i++) {
        gradePrint(output,grade) ;
        grade=listGetNext(grades);
    }
    listDestroy(grades);
    return COURSE_MANAGER_SUCCESS ;
}

/**
 * Returns a pointer to the student by the given ID , searches the course manger
 * student set and finds the student with the given ID .
 * @param
 * course_manager - the course manager of the logged student we wish to print.
 * id - the id of the student we want to find .
 * @return
 * NULL - if a null was sent or if the student wasn't found.
 * A pointer to the student - otherwize .
 */
static Student courseManagerGetStudent (CourseManager course_manager,int id) {
    if (course_manager==NULL) {
        return NULL ;
    }
    SET_FOREACH(Student,student,course_manager->students) {
        if(studentGetId(student)==id) {
            return student ; // returns a pointer to student and not a copy
        }
    }
    return NULL ;
}

/**
 * Creates a new list of grades that each grade belongs to the logged student
 * friends set according to the course id.
 * the list is consisted of the max grade that each friend has in that course.
 * @param
 * course_manager - the course manager of the logged student we wish to print.
 * course_id - the course ID we want to get the max grades from .
 * @return
 * NULL - if a NULL was sent.
 * A new maximum grades of the logged student friends - otherwize .
 */
static List getReferenceList (CourseManager course_manager,int course_id) {
    if (course_manager==NULL) {
        return NULL ;
    }
    List list=listCreate(gradeCopy,gradeDestroy);
    if (list==NULL) {
        return NULL ;
    }
    Set friends = studentGetFriends(course_manager->logged_student);
    if (friends==NULL) {
        listDestroy(list) ;
        return NULL ;
    }
    SET_FOREACH(int*,friend,friends) {
        Student student=courseManagerGetStudent(course_manager,*friend);
        Grade max_grade=studentGetMaxGrade(student,course_id) ;
        //if max_grade==NULL the student doesn't have a grade of that course.
        if (max_grade!=NULL) {
            if(listInsertFirst(list,max_grade)!=LIST_SUCCESS) {
                setDestroy(friends);
                listDestroy(list) ;
                return NULL ;
            }
        }
    }
    setDestroy(friends) ;
    return list ;
}

CourseManagerResult courseManagerReference (FILE* output
        ,CourseManager course_manager , int course_id ,int amount ){
    if (course_manager->logged_student == NULL) {
        return COURSE_MANAGER_NO_LOGGED_STUDENT;
    }
    if (amount<=0) {
        return COURSE_MANAGER_INVALID_PARAMETERS ;
    }
    List references = getReferenceList(course_manager,course_id) ;
    if (references==NULL) {
        return COURSE_MANAGER_MEM_PROBLEM ;
    }
    if (listSort(references,gradeSortByGrade,NULL)!=LIST_SUCCESS){
        listDestroy(references) ;
        return COURSE_MANAGER_MEM_PROBLEM ;
    }
    Grade grade = listGetFirst(references);
    for (int i=0 ; i<amount && grade!=NULL ; i++) {
        Student student = courseManagerGetStudent(course_manager
                ,gradeGetStudentId(grade));
        studentPrintName(output,student) ;
        grade=listGetNext(references);
    }
    listDestroy(references) ;
    return COURSE_MANAGER_SUCCESS ;
}

CourseManagerResult courseManagerRequest (FILE* output
        ,CourseManager course_manager,int course_id,char* request){
    if (course_manager->logged_student == NULL) {
        return COURSE_MANAGER_NO_LOGGED_STUDENT;
    }
    RequestResult result=checkRequest(request) ;
    if(result==REQUEST_ILLEGAL_PARAMETER) {
        return COURSE_MANAGER_INVALID_PARAMETERS;
    }
    if (result==REMOVE_COURSE) {
        if(!checkCourseId(course_id)){
            return COURSE_MANAGER_NO_SUCH_COURSE;
        }
        if (!studentCheckGradeExist(course_manager->logged_student,course_id)){
            return COURSE_MANAGER_NO_SUCH_COURSE;
        }
    }
    mtmFacultyResponse(output,"your request was rejected");
    return COURSE_MANAGER_SUCCESS;
}

void courseManagerDestroy(CourseManager course_manager) {
    if (course_manager==NULL) {
        return ;
    }
    if (course_manager->students!=NULL) {
        setDestroy(course_manager->students);
    }
    course_manager->logged_student=NULL ;
    free (course_manager) ;
}
