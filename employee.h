/*
    AUTHOR: MCA.2104, MCA.2103
    PROGRAM: PROJECT
    DATE CREATED: 18 NOV 2021
    DATE MODIFIED: 29 DEC 2021
*/
//DS Designer
#ifndef EMPLOYEE
    #define EMPLOYEE

    typedef struct salary salstr;
    typedef struct employee empstr;
    typedef struct list listNd; //list of employees
    typedef struct empNode empNd;

    struct salary{
        float basicPay;
        float HRA; //20%
        float DA; //20%
        float TA; //20%
        float PA; //20%
        float bonus;
        float total;
    };

    struct employee{
        int empID;
        char name[40];
        char address[100];
        char department[20];
        struct salary sal;
        char prjAssigned[100];
        float salAdvance;
        float salLeft;
        int leavesTotal;
        int leavesTaken;
        int leavesLeft;
    };
    
    struct list{
        int empCount;
        int eID;
        struct empNode *firstEmp;
    };

    struct empNode{
        struct employee emp;
        struct empNode *nextEmp;
    };

    /*
        function name: createList
        function: create a new list
        input: none
        pre-condition: none
        output: listNd*
        post-condition: new list created
    */
    listNd* createList();

    /*
        function name: calcSal
        function: calculates salary of an employee
        input: listNd*, int
        pre-condition: none
        output: total salary of the employee
        post-condition: none
    */
    float calcSal(listNd *list, int empID);
    
    /*
        function name: insertEmployee
        function: add an employee to the list
        input: listNd*, empstr
        pre-condition: list exist
        output: empNd*
        post-condition: new employee added to the list
    */
    empNd* insertEmployee(listNd *list, empstr emp);

    /*
        function name: refresh
        function: sets all employee parameters to default
        input: listNd*
        pre-condition: list not empty
        output: none
        post-condition: sets all employee parameters to default
    */
    void refresh(listNd *list);

    /*
        function name: grantBonus
        function: grants bonus to employee
        input: listNd*, int, float
        pre-condition: list not empty
        output: 1 if bonus granted, 0 otherwise
        post-condition: bonus granted to employee
    */
    int grantBonus(listNd *list, int empID, float bonus);

    /*
        function name: advanceSal
        function: grants advance salary to an employee
        input: listNd*, int, float
        pre-condition: list not empty
        output: return 1 if advance granted successfully, return -1 if employee not found, return -2 if asked salary greater than salary left
        post-condition: 
    */
    int advanceSal(listNd *list, int empID, float sal);

    /*
        function name: grantLeave
        function: grants leave to an employee
        input: listNd*, int, float
        pre-condition: list not empty
        output: return 1 if leave granted successfully, return -1: employee not found, return -2 if leaves asked for is greater than leaves left of the employee
        post-condition: leave granted to employee
    */
    int grantLeave(listNd *list, int empID, int leave);

    /*
        function name: displayEmployee
        function: displays employee details
        input: listNd*, int
        pre-condition: list not empty
        output: 1 if successfully, -1 otherwise
        post-condition: none
    */
    int displayEmployee(listNd *list, int empID);

    /*
        function name: displayAllEmployees
        function: displays all employee details
        input: listNd*
        pre-condition: list not empty
        output: none
        post-condition: none
    */
    void displayAllEmployees(listNd *list);

    /*
        function name: deleteEmployee
        function: deletes an employee from the list and frees the memory allocated
        input: listNd*, int
        pre-condition: list not empty
        output: return 1 if successfull, return -1 if employee not found, return -2 if employee working on a project
        post-condition: employee deleted from the list
    */
    int deleteEmployee(listNd* list, int ID);

    /*
        function name: destroyList
        function: deletes all employees from the list and frees the memory allocated
        input: listNd*
        pre-condition: none
        output: none
        post-condition: all employees deleted from the list
    */
    void destroyList(listNd *list);
#endif