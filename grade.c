#include "grade.h"
/**
 * Grade.c
 *
 * All functions have explanations in Grade.h file .
 */

/**
 * Each type of grade has a Course that he belogns to ,
 * a Semester , the student ID and the grade itself .
 * Grade will be inserted into a linked list for Semester type.
 */
struct grade_t {
    Course course ;
    int grade ;
    int semester ;
    int student_id ;
};

Grade  gradeCreate(Course course, int grade,int semester,int student_id) {
    if (course==NULL) {
        return NULL ;
    }
    Grade new_grade=malloc(sizeof(*new_grade)) ;
    if (new_grade==NULL) {
        return NULL;
    }
    new_grade->course=courseCopy(course) ;
    if (new_grade->course==NULL) {
        gradeDestroy(new_grade) ;
        return NULL ;
    }
    new_grade->grade=grade ;
    new_grade->semester=semester;
    new_grade->student_id=student_id;
    return new_grade ;
}

ListElement gradeCopy(ListElement grade) {
    if (grade == NULL) {
        return NULL ;
    }
    Grade new_grade=malloc(sizeof(*new_grade)) ;
    if (new_grade==NULL) {
        return NULL;
    }
    new_grade->course=courseCopy(((Grade)grade)->course);
    if (new_grade->course==NULL) {
        gradeDestroy(new_grade) ;
        return NULL ;
    }
    new_grade->grade=(((Grade)grade)->grade) ;
    new_grade->semester=(((Grade)grade)->semester) ;
    new_grade->student_id=(((Grade)grade)->student_id) ;
    return new_grade ;
}

int gradeGetGrade (Grade grade) {
    return grade == NULL ? -1 : grade->grade ;
}

int gradeGetSemester (Grade grade) {
    return grade == NULL ? -1 : grade->semester ;
}

int gradeGetStudentId (Grade grade) {
    return grade == NULL ? -1 : grade->student_id ;
}

int gradeGetCoursePoints(Grade grade) {
    return grade == NULL ? -1 : courseGetPoints(grade->course);
}

int gradeGetCourseId (Grade grade) {
    if (grade==NULL) {
        return -1;
    }
    return courseGetId(grade->course) ;
}

GradeResult gradeUpdate(Grade grade , int new_grade) {
    if (grade==NULL) {
        return GRADE_NULL_ARGUMENT ;
    }
    grade->grade=new_grade ;
    return GRADE_SUCCES ;
}

bool gradeIsGradeInList (List list , Grade grade) {
    LIST_FOREACH(Grade,current,list){
        if (gradeGetCourseId(grade)==gradeGetCourseId(current)) {
            return true;
        }
    }
    return false ;
}

bool gradeIsSportCourse(Grade grade) {
    int course_id=gradeGetCourseId(grade);
    if ((course_id>=SPORT_COURSE_MIN)&&(course_id<=SPORT_COURSE_MAX)) {
        return true;
    }
    return false ;
}

int gradeCompareById(ListElement grade1,ListElement grade2,ListSortKey key){
    int result = gradeGetCourseId(grade1) - gradeGetCourseId(grade2) ;
    if (result>0) {
        return 1 ;
    }
    if (result<0){
        return -1 ;
    }
    // if course_id is the same we sort by semesters ;
    return  gradeGetSemester(grade1) - gradeGetSemester(grade2) ;
}

// if we want to sort by max , Key = 1 , if we want to sort by Min , key=-1
int gradeCompareForSort(ListElement grade1,ListElement grade2
        ,ListSortKey key){
    int result = (*(int*)(key))*(gradeGetGrade(grade1) - gradeGetGrade(grade2)) ;
    if (result>0) {
        return -1 ;
    }
    if (result<0){
        return 1 ;
    }// if grades are the same we sort by semesters ;
    result = gradeGetSemester(grade1) - gradeGetSemester(grade2) ;
    if (result>0) {
        return 1 ;
    }
    if (result<0){
        return -1 ;
    }// if semester are the same we sort by course_id
    return gradeGetCourseId(grade1)- gradeGetCourseId(grade2) ;
}

int gradeSortByGrade (ListElement grade1,ListElement grade2,ListSortKey key){
    int result = gradeGetGrade(grade1) - gradeGetGrade(grade2) ;
    if (result>0) {
        return -1 ;
    }
    if (result<0) {
        return 1;
    }//if grades are the same we sort by student ID
    return gradeGetStudentId(grade1) - gradeGetStudentId(grade2) ;
}

void gradePrint (FILE* output,Grade grade) {
    if (grade==NULL) {
        return ;
    }
    mtmPrintGradeInfo(output,gradeGetCourseId(grade),
                      gradeGetCoursePoints(grade),gradeGetGrade(grade));
}

void gradeDestroy(ListElement grade){
    if (grade==NULL) {
        return;
    }
    courseDestroy(((Grade)grade)->course);
    free (grade) ;
}


