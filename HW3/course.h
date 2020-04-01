#ifndef COURSE_H
#define COURSE_H

#include <stdlib.h>
#include <stdio.h>

/**
 * Course.h
 * Course is a data type that contains a course ID
 * and the number of points(multiplied by 2) that the course has.
 *
 * Course functions :
 *
 * courseCreate
 * courseCopy
 * courseGetId
 * courseGetPoints
 * courseDestroy
 */

typedef  struct  course_t* Course ;

/**
 * Allocates a new Course with the parameters given.
 *
 * @param
 * id - the id number of the course.
 * points - number of course points.
 *
 * @return
 * NULL - if memorey allocation failed,
 * A new course otherwize.
 */
Course courseCreate(int id , int points) ;

/**
 * creates a new Course and copies all the fields from a given course.
 *
 * @param
 * course - the course that we wish to copy.
 * @return
 * NULL - if memorey allocation failed or a NULL argument,
 * A new copied course otherwize.
 */
Course courseCopy(Course course) ;

/**
 * Returns the course id.
 * @param
 * course - the course from which we want to get the id .
 * @return
 * -1 - retuns -1 if NULL argument,
 * the course id otherwize .
 */
int courseGetId(Course course) ;

/**
 * Returns the course points.
 * @param
 * course - the course from which we want to get the points.
 * @return
 * -1 - returns -1 if NULL argument ,
 * the course points*2 otherwize.
 */
int courseGetPoints(Course course) ;

/**
 * Deallocates an existing course.
 *
 * @param
 * course-the target course to deallocate,if null was sent nothing will happen.
 */
void courseDestroy(Course course) ;


#endif //COURSE_H
