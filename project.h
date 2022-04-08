/*
    AUTHOR: MCA.2104, MCA.2103
    PROGRAM: PROJECT
    DATE CREATED: 18 NOV 2021
    DATE MODIFIED: 29 DEC 2021
*/
//DS Designer
#ifndef PROJECT
    #define PROJECT
    
    typedef struct project prjstr;
    typedef struct graphNode graphNd; //graph of projects
    typedef struct projectNode projectNd;
    typedef struct linkNode linkNd; //link to employees on the project

    struct project{
        int projectID;
        char projectName[50];
        char projectDescription[1000];
        int empCount;
    };
    
    struct graphNode{
        int prjCount;
        int pID;
        struct projectNode *firstProject;
    };

    struct projectNode{
        prjstr prj;
        struct projectNode *nextProject;
        struct linkNode *firstEmp;
    };

    struct linkNode{
        struct employee destination;
        struct linkNode *nextLink;
    };

    /*
        function name: createGraph
        function: create a new graph
        input: none
        pre-condition: none
        output: graphNd*
        post-condition: new graph is created
    */
    graphNd* createGraph();

    /*
        function name: insertProject
        function: inserts new project in the graph
        input: graphNd*, prjstr
        pre-condition: graph exists
        output: projectNd*
        post-condition: new project added in the graph
    */
    projectNd* insertProject(graphNd *graph, prjstr name);

    /*
        function name: addEmployee
        function: adds an employee to a project
        input: graphNd*, int, listNd*, int
        pre-condition: linkedlist not empty
        output: return 1 if employee successfully added, return -1 if memory couldnt be created, return -2 if project doesnt exist, return -3 if employee doesnt exist, return -4 if employee already working on another project
        post-condition: an employee added to a project
    */
    int addEmployee(graphNd *graph, int prjID, listNd *list, int empID);

    /*
        function name: displayAllProject
        function: displays all projects in the graph
        input: graphNd*
        pre-condition: graph not empty
        output: none
        post-condition: none
    */
    void displayAllProject(graphNd *graph);

    /*
        function name: displayProject
        function: displays one project from the graph
        input: graphNd*, int
        pre-condition: graph not empty
        output: 1 if project exists, -1 otherwise
        post-condition: none
    */
    int displayProject(graphNd *graph, int prjID);

    /*
        function name: generateReport
        function: generates report of all projects at the end of the month
        input: graphNd*, listNd*
        pre-condition: graph not empty
        output: 1 none
        post-condition: none
    */
    void generateReport(graphNd *graph, listNd *list);

    /*
        function name: removeEmployee
        function: removes an employee from a project and free the memory allocated
        input: graphNd*, int, listNd*, int
        pre-condition: linkedlist not empty
        output: return 1 if employee successfully removed from project, return -1 if project not found in the database, return -2 if employee not found in the project list
        post-condition: an employee removed from a project
    */
    int removeEmployee(graphNd *graph, int prjID, listNd *list, int empID);

    /*
        function name: deleteProject
        function: deletes a project from the graph and free the memory allocated
        input: graphNd*, int, listNd*
        pre-condition: graph not empty
        output: 1 if project successfully deleted, -1 otherwise
        post-condition: project deleted from the graph
    */
    int deleteProject(graphNd* graph, int prjID, listNd *list);

    /*
        function name: destroyGraph
        function: deletes all projects from the graph and free the memory allocated
        input: graphNd*, listNd*
        pre-condition: none
        output: none
        post-condition: all projects deleted from the graph
    */
    void destroyGraph(graphNd *graph, listNd *list);
#endif