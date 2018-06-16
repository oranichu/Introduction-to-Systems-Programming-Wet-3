#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <assert.h>
#include "mtm_ex3.h"
#include "course_manager.h"


typedef enum {
    INPUT_ERROR, //input is illegal
    INPUT_IS_JUST_INPUT, // we received just -i
    INPUT_IS_JUST_OUTPUT,// we received just -o
    INPUT_IS_INPUT_THEN_OUTPUT,// we received -i then -o
    INPUT_IS_OUTPUT_THEN_INPUT,// we received -o then -i
    INPUT_IS_NONE // argc == 1
} WhatIsTheInput ;

typedef enum {
    INPUT,
    OUTPUT,
    NOT_BOTH
}InputOrOutput ;

static InputOrOutput checkInputOrOutput (char* string) {
    if (!strcmp(string,"-i")) {
        return INPUT ;
    }
    if (!strcmp(string,"-o")) {
        return OUTPUT ;
    }
    return NOT_BOTH ;
}

static WhatIsTheInput checkInput(int argc , char** argv){
    if (argc > 5 || argc==2 || argc== 4) { // invalid number of parameters.
        return INPUT_ERROR;
    }
    if (argc == 3 ) {
        if (((!strcmp(argv[1],"-o"))&&(!strcmp(argv[2],"-i"))) ||
            ((!strcmp(argv[1],"-i"))&&(!strcmp(argv[2],"-o")))) {
            return INPUT_ERROR ; // special case when input is -i and -o
        }
        InputOrOutput check1 = checkInputOrOutput(argv[1]) ;
        if (check1 == INPUT ) {
            return INPUT_IS_JUST_INPUT ;
        }
        if (check1 == OUTPUT) {
            return INPUT_IS_JUST_OUTPUT ;
        }
        return INPUT_ERROR ;
    }
    if (argc == 5) {
        InputOrOutput check2 = checkInputOrOutput(argv[1]) ;
        InputOrOutput check3 = checkInputOrOutput(argv[3]) ;
        if (check2==INPUT && check3==OUTPUT) {
            return INPUT_IS_INPUT_THEN_OUTPUT ;
        }
        if (check2==OUTPUT && check3==INPUT) {
            return INPUT_IS_OUTPUT_THEN_INPUT ;
        }
        return INPUT_ERROR ;
    }
    return INPUT_IS_NONE ; //argc == 1
}

FILE* openInputFile(WhatIsTheInput check ,char ** argv) {
    switch (check) {
        case INPUT_IS_JUST_INPUT : return fopen(argv[2],"r") ;
        case INPUT_IS_INPUT_THEN_OUTPUT : return fopen(argv[2],"r") ;
        case INPUT_IS_OUTPUT_THEN_INPUT : return fopen(argv[4],"r") ;
        default: return stdin ; //either it's just output or none
    }
}

FILE* openOutputFile (WhatIsTheInput check ,char ** argv) {
    switch (check) {
        case INPUT_IS_JUST_OUTPUT : return fopen(argv[2],"w") ;
        case INPUT_IS_OUTPUT_THEN_INPUT : return fopen(argv[2],"w") ;
        case INPUT_IS_INPUT_THEN_OUTPUT : return fopen(argv[4],"w") ;
        default: return stdout ; //either it's just intput or none
    }
}

void closeInputFile (WhatIsTheInput check , FILE* input) {
    if (check == INPUT_IS_NONE || check == INPUT_IS_JUST_OUTPUT ) {
        return ; //it means input is stdin ;
    }
    fclose(input) ;
}

void closeOutputFile (WhatIsTheInput check , FILE* output) {
    if (check == INPUT_IS_NONE || check == INPUT_IS_JUST_INPUT) {
        return ; //it means output is stdout ;
    }
    fclose(output) ;
}

void closeAllFiles(WhatIsTheInput check , FILE* input , FILE* output) {
    closeInputFile(check,input);
    closeOutputFile(check,output) ;
}

int numOfWords(char* str) {
    int num_of_words = 0 ;
    bool still_space = true ;
    for (int i=0 ; i< strlen(str) ; i++) {
        if (((str[i]!=' ') &&(str[i]!='\n')&&(str[i]!='\t') && still_space)) {
            num_of_words++;
            still_space=false ;
        }
        if (((str[i]==' ')|| (str[i]=='\t')) && !still_space) {
            still_space=true ;
        }
    }
    return num_of_words;
}

void destroyStringArray(char** array , int size) {
    for (int i=0;i<size;i++) {
        free(array[i]) ;
    }
    //  free(array) ;
}

bool stringToArray(char** array,char* str) {
    assert (str) ;
    int i=0 ;
    char *temp_str = calloc(strlen(str) + 1, sizeof(char));
    if (temp_str == NULL) {
        return false;
    }
    strcpy(temp_str, str);
    char *word = strtok(temp_str," \t\n");
    while (word != NULL) {
        array[i]= malloc((strlen(word) + 1)*sizeof(char)) ;
        if (array[i]==NULL) {
            free(temp_str);
            destroyStringArray(array,i);
            return false ;
        }
        strcpy(array[i++],word);
        word = strtok(NULL," \t\n");
    }
    free(word) ;
    free(temp_str);
    return true ;
}

static int stringToInt (char* string){
    if (string==NULL) {
        return -1 ;
    }
    int num=0,index=0,numeric_digit ;
    char digit= string[index] ;
    while ((digit!='\0')&&(digit!='\n')) {
        num*=10;
        numeric_digit=digit- '0' ;
        if ((numeric_digit<0)||(numeric_digit>9)) {
            return -1 ;
        }
        num+=numeric_digit ;
        digit=string[++index];
    }
    return num ;
}

bool mainStudentAdd(CourseManager course_manager,int id,
                char* first_name,char* last_name) {
    CourseManagerResult result=courseManagerAddStudent(course_manager,id,
                                                       first_name,last_name);
    switch (result) {
        case COURSE_MANAGER_MEM_PROBLEM: return false ;
        case COURSE_MANAGER_STUDENT_EXISTS: mtmPrintErrorMessage(stderr
                    ,MTM_STUDENT_ALREADY_EXISTS);
            break;
        case COURSE_MANAGER_INVALID_PARAMETERS : mtmPrintErrorMessage(stderr
                    ,MTM_INVALID_PARAMETERS);
            break;
        default: ;
    }
    return true;
}

bool mainStudentRemove(CourseManager course_manager,int id) {
    CourseManagerResult result=courseManagerRemoveStudent(course_manager,id);
    switch (result) {
        case COURSE_MANAGER_NO_SUCH_STUDENT: mtmPrintErrorMessage(stderr
                    ,MTM_STUDENT_DOES_NOT_EXIST);
        default: ;
    }
    return true;
}

bool mainStudentLogin (CourseManager course_manager,int id){
    CourseManagerResult result=courseManagerLogin(course_manager,id) ;
    switch (result) {
        case COURSE_MANAGER_ALREADY_LOGGED: mtmPrintErrorMessage(stderr
                    ,MTM_ALREADY_LOGGED_IN);
            break;
        case COURSE_MANAGER_NO_SUCH_STUDENT : mtmPrintErrorMessage(stderr
                    ,MTM_STUDENT_DOES_NOT_EXIST);
            break;
        default: ;
    }
    return true;
}

bool mainStudentLogout(CourseManager course_manager){
    CourseManagerResult result=courseManagerLogout(course_manager) ;
    switch (result) {
        case COURSE_MANAGER_NO_LOGGED_STUDENT: mtmPrintErrorMessage(stderr
                    ,MTM_NOT_LOGGED_IN);
        default: ;
    }
    return true;
}

bool mainFriendRequest(CourseManager course_manager, int id) {
    CourseManagerResult result=courseManagerFriendRequest(course_manager,id);
    switch (result) {
        case COURSE_MANAGER_MEM_PROBLEM: return false ;
        case COURSE_MANAGER_NO_LOGGED_STUDENT: mtmPrintErrorMessage(stderr
                    ,MTM_NOT_LOGGED_IN);
            break;
        case COURSE_MANAGER_NO_SUCH_STUDENT : mtmPrintErrorMessage(stderr
                    ,MTM_STUDENT_DOES_NOT_EXIST);
            break;
        case COURSE_MANAGER_ALREADY_FRIEND : mtmPrintErrorMessage(stderr
                    ,MTM_ALREADY_FRIEND);
            break;
        case COURSE_MANAGER_ALREADY_REQUESTED : mtmPrintErrorMessage(stderr
                    ,MTM_ALREADY_REQUESTED);
            break;
        default: ;
    }
    return true;
}

bool mainHandleRequest(CourseManager course_manager,int id,char* action) {
    CourseManagerResult result=courseManagerHandleRequest(course_manager
            ,id,action);
    switch (result) {
        case COURSE_MANAGER_MEM_PROBLEM: return false ;
        case COURSE_MANAGER_NO_LOGGED_STUDENT: mtmPrintErrorMessage(stderr
                    ,MTM_NOT_LOGGED_IN);
            break;
        case COURSE_MANAGER_NO_SUCH_STUDENT : mtmPrintErrorMessage(stderr
                    ,MTM_STUDENT_DOES_NOT_EXIST);
            break;
        case COURSE_MANAGER_ALREADY_FRIEND : mtmPrintErrorMessage(stderr
                    ,MTM_ALREADY_FRIEND);
            break;
        case COURSE_MANAGER_NO_SUCH_REQUEST : mtmPrintErrorMessage(stderr
                    ,MTM_NOT_REQUESTED);
            break;
        case COURSE_MANAGER_INVALID_PARAMETERS : mtmPrintErrorMessage(stderr
                    ,MTM_INVALID_PARAMETERS);
            break;
        default: ;
    }
    return true;
}

bool mainUnfriend (CourseManager course_manager,int id) {
    CourseManagerResult result=courseManagerUnfriend(course_manager,id);
    switch (result) {
        case COURSE_MANAGER_NO_LOGGED_STUDENT: mtmPrintErrorMessage(stderr
                    ,MTM_NOT_LOGGED_IN);
            break;
        case COURSE_MANAGER_NO_SUCH_STUDENT : mtmPrintErrorMessage(stderr
                    ,MTM_STUDENT_DOES_NOT_EXIST);
            break;
        case COURSE_MANAGER_NOT_FRIEND : mtmPrintErrorMessage(stderr
                    ,MTM_NOT_FRIEND);
            break;
        default: ;
    }
    return true;
}

bool mainAddGrade (CourseManager course_manager,int semester ,int course_id
        ,char* points , int grade) {
    CourseManagerResult result=courseManagerAddGrade(course_manager,semester
            ,course_id,points,grade) ;
    switch (result) {
        case COURSE_MANAGER_MEM_PROBLEM: return false ;
        case COURSE_MANAGER_NO_LOGGED_STUDENT: mtmPrintErrorMessage(stderr
                    ,MTM_NOT_LOGGED_IN);
            break;
        case COURSE_MANAGER_INVALID_PARAMETERS : mtmPrintErrorMessage(stderr
                    ,MTM_INVALID_PARAMETERS);
            break;
        default: ;
    }
    return true;
}

bool mainRemoveGrade (CourseManager course_manager,int semester,int course_id){
    CourseManagerResult result=courseManagerRemoveGrade(course_manager,semester
            ,course_id);
    switch (result) {
        case COURSE_MANAGER_NO_LOGGED_STUDENT: mtmPrintErrorMessage(stderr
                    ,MTM_NOT_LOGGED_IN);
            break;
        case COURSE_MANAGER_NO_SUCH_COURSE : mtmPrintErrorMessage(stderr
                    ,MTM_COURSE_DOES_NOT_EXIST);
            break;
        default: ;
    }
    return true;
}

bool mainUpdateGrade (CourseManager course_manager,int course_id,int grade){
    CourseManagerResult result=courseManagerUpdateGrade(course_manager,course_id
            ,grade);
    switch (result) {
        case COURSE_MANAGER_NO_LOGGED_STUDENT: mtmPrintErrorMessage(stderr
                    ,MTM_NOT_LOGGED_IN);
            break;
        case COURSE_MANAGER_NO_SUCH_COURSE : mtmPrintErrorMessage(stderr
                    ,MTM_COURSE_DOES_NOT_EXIST);
            break;
        case COURSE_MANAGER_INVALID_PARAMETERS : mtmPrintErrorMessage(stderr
                    ,MTM_INVALID_PARAMETERS);
            break;
        default: ;
    }
    return true;
}

bool mainPrintFull (FILE* output,CourseManager course_manager) {
    CourseManagerResult result=courseManagerPrintFull(output,course_manager);
    switch (result) {
        case COURSE_MANAGER_MEM_PROBLEM : return false ;
        case COURSE_MANAGER_NO_LOGGED_STUDENT: mtmPrintErrorMessage(stderr
                    ,MTM_NOT_LOGGED_IN);
            break;
        default: ;
    }
    return true;
}

bool mainPrintClean (FILE* output,CourseManager course_manager) {
    CourseManagerResult result=courseManagerPrintClean(output,course_manager);
    switch (result) {
        case COURSE_MANAGER_MEM_PROBLEM : return false ;
        case COURSE_MANAGER_NO_LOGGED_STUDENT: mtmPrintErrorMessage(stderr
                    ,MTM_NOT_LOGGED_IN);
            break;
        default: ;
    }
    return true;
}

bool mainPrintMaxMin (FILE* output,CourseManager course_manager,int amount
        ,int key) {
    CourseManagerResult result=courseManagerPrintMaxMin(output,course_manager
            ,amount,key);
    switch (result) {
        case COURSE_MANAGER_MEM_PROBLEM : return false ;
        case COURSE_MANAGER_INVALID_PARAMETERS : mtmPrintErrorMessage(stderr
                    ,MTM_INVALID_PARAMETERS);
            break;
        case COURSE_MANAGER_NO_LOGGED_STUDENT : mtmPrintErrorMessage(stderr
                    ,MTM_NOT_LOGGED_IN);
            break;
        default: ;
    }
    return true;
}

bool mainPrintReference (FILE* output,CourseManager course_manager
        ,int course_id,int amount){
    CourseManagerResult result=courseManagerReference(output,course_manager
            ,course_id,amount);
    switch (result) {
        case COURSE_MANAGER_MEM_PROBLEM : return false ;
        case COURSE_MANAGER_INVALID_PARAMETERS : mtmPrintErrorMessage(stderr
                    ,MTM_INVALID_PARAMETERS);
            break;
        case COURSE_MANAGER_NO_LOGGED_STUDENT : mtmPrintErrorMessage(stderr
                    ,MTM_NOT_LOGGED_IN);
            break;
        default: ;
    }
    return true;
}

bool mainPrintFacultyRequest (FILE* output,CourseManager course_manager
        ,int course_id,char* request){
    CourseManagerResult result=courseManagerRequest(output,course_manager
            ,course_id,request);
    switch (result) {
        case COURSE_MANAGER_INVALID_PARAMETERS : mtmPrintErrorMessage(stderr
                    ,MTM_INVALID_PARAMETERS);
            break;
        case COURSE_MANAGER_NO_LOGGED_STUDENT : mtmPrintErrorMessage(stderr
                    ,MTM_NOT_LOGGED_IN);
            break;
        case COURSE_MANAGER_NO_SUCH_COURSE : mtmPrintErrorMessage(stderr
                    ,MTM_COURSE_DOES_NOT_EXIST);
            break;
        default: ;
    }
    return true;
}

bool jumpToSubroutine (FILE* output,char ** array,CourseManager course_manager){

    if (!strcmp(array[0],"student")) {
        if (!strcmp(array[1], "add")) {
            return mainStudentAdd(course_manager,stringToInt(array[2])
                    ,array[3],array[4]) ;
        }
        if (!strcmp(array[1], "remove")) {
            return mainStudentRemove (course_manager,stringToInt(array[2]));
        }
        if (!strcmp(array[1], "login")) {
            return mainStudentLogin(course_manager,stringToInt(array[2]));
        }
        if ((!strcmp(array[1], "logout")) || (!strcmp(array[1], "logout\n"))) {
            return mainStudentLogout(course_manager);
        }
        if (!strcmp(array[1], "friend_request")) {
            return mainFriendRequest(course_manager,stringToInt(array[2]));
        }
        if (!strcmp(array[1], "handle_request")) {
            return mainHandleRequest(course_manager,stringToInt(array[2])
                    ,array[3]);
        }
        if (!strcmp(array[1], "unfriend")) {
            return mainUnfriend(course_manager,stringToInt(array[2]));
        }
    }
    if (!strcmp(array[0],"grade_sheet")) {
        if (!strcmp(array[1], "add")) {
            return mainAddGrade(course_manager,stringToInt(array[2])
                    ,stringToInt(array[3]),array[4],stringToInt(array[5]));
        }
        if (!strcmp(array[1], "remove")) {
            return mainRemoveGrade(course_manager,stringToInt(array[2])
                    ,stringToInt(array[3]));
        }
        if (!strcmp(array[1], "update")) {
            return mainUpdateGrade(course_manager,stringToInt(array[2])
                    ,stringToInt(array[3]));
        }
    }
    if (!strcmp(array[0],"report")) {
        if ((!strcmp(array[1], "full")) || (!strcmp(array[1], "full\n"))) {
            return mainPrintFull(output,course_manager);
        }
        if ((!strcmp(array[1], "clean")) || (!strcmp(array[1], "clean\n"))) {
            return mainPrintClean(output,course_manager);
            ;
        }
        if (!strcmp(array[1],"best")) {
            return mainPrintMaxMin(output,course_manager,stringToInt(array[2])
                    ,1);
        }
        if (!strcmp(array[1],"worst")) {
            return mainPrintMaxMin(output,course_manager,stringToInt(array[2])
                    ,-1);
        }
        if (!strcmp(array[1],"reference")) {
            return mainPrintReference(output,course_manager
                    ,stringToInt(array[2]),stringToInt(array[3]));
        }
        if (!strcmp(array[1],"faculty_request")) {
            return mainPrintFacultyRequest(output,course_manager
                    ,stringToInt(array[2]),array[3]);
        }
    }
    return true;
}

bool readFile(WhatIsTheInput check ,FILE* input , FILE* output) {
    CourseManager course_manager = courseManagerCreate();
    if (course_manager==NULL) {
        closeAllFiles(check,input,output);
        return false;
    }
    char buffer[MAX_LEN] ="" ;
    while (fgets(buffer,MAX_LEN,input)!=NULL) {
        int number_of_words = numOfWords(buffer);
        if (number_of_words == 0) continue; //empty line
        char *buffer_array[number_of_words];
        if (stringToArray(buffer_array,buffer)==false) {
            courseManagerDestroy(course_manager);
            closeAllFiles(check,input,output);
            return false ;
        }
        if(buffer_array[0][0]!='#') { //comment line
            if(jumpToSubroutine(output,buffer_array,course_manager)==false){
                courseManagerDestroy(course_manager);
                destroyStringArray(buffer_array,number_of_words);
                closeAllFiles(check,input,output);
                return false;
            }
        }
        destroyStringArray(buffer_array,number_of_words);
    }
    courseManagerDestroy(course_manager);
    closeAllFiles(check,input,output) ;
    return true ;
}

int main(int argc , char** argv) {
    WhatIsTheInput check=checkInput(argc,argv) ;
    if (check == INPUT_ERROR) {
        mtmPrintErrorMessage(stderr,MTM_INVALID_COMMAND_LINE_PARAMETERS);
        return 0;
    }
    FILE* input = openInputFile(check,argv) ;
    if (!input) {
        mtmPrintErrorMessage(stderr,MTM_CANNOT_OPEN_FILE);
        return 0;
    }
    FILE* output = openOutputFile(check,argv) ;
    if (!output) {
        closeInputFile(check,input) ;
        mtmPrintErrorMessage(stderr,MTM_CANNOT_OPEN_FILE);
        return 0;
    }
    if (!readFile(check,input,output)) { // closes files aswell
        mtmPrintErrorMessage(stderr,MTM_OUT_OF_MEMORY);
    }
    return 0;
}