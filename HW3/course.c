#include "course.h"

/**
 * Course.c
 *
 * All functions have explanations in Course.h file .
 */

/**c
 * Each type of course has an ID and number of points.
 * number of points is saved as number of points *2
 * so that we can save it as an int .
 */
struct  course_t {
    int id ;
    int points ;
} ;

Course courseCreate(int id , int points) {
    Course new_course=malloc(sizeof(*new_course)) ;
    if (new_course==NULL) {
        return NULL ;
    }
    new_course->id=id ;
    new_course->points=points;
    return new_course ;
}

int courseGetId(Course course) {
    return course == NULL ? -1 : course->id;
}

int courseGetPoints(Course course) {
    return course == NULL ? -1 : course->points;
}

Course courseCopy(Course course) {
    if (course ==NULL ) {
        return NULL ;
    }
    Course new_course=malloc(sizeof(*new_course)) ;
    if (new_course==NULL) {
        return NULL ;
    }
    new_course->id = course->id ;
    new_course->points= course->points ;
    return new_course ;
}

void courseDestroy(Course course) {
    if (course==NULL) {
        return;
    }
    free (course) ;
}
