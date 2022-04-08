/*
    AUTHOR: MCA.2104, MCA.2103
    PROGRAM: PROJECT
    DATE CREATED: 18 NOV 2021
    DATE MODIFIED: 29 DEC 2021
*/
//APPLICATION DEVELOPER
#include<stdio.h>
#include<conio.h>
#include<stdbool.h>
#include<string.h>
#include<malloc.h>
#include"employee.h"
#include"project.h"

void main() {
    int option, check, prjID, empID, days;
    float sal;
    prjstr prj;
    empstr emp;
    graphNd *graph;
    listNd *list;
    projectNd *prjnd;
    empNd *empnd;
    option = 1;
    graph = createGraph();
    list = createList();
    do {
        printf("\n----------------------------------------------------------------");
        printf("\nEnter 1 to create new database.");
        printf("\nEnter 2 to add new project.");
        printf("\nEnter 3 to add new employee.");
        printf("\nEnter 4 to add an employee to a project.");
        printf("\nEnter 5 to remove an employee from a project.");
        printf("\nEnter 6 to grant bonus to an employee.");
        printf("\nEnter 7 to grant advance salary to an employee.");
        printf("\nEnter 8 to grant leave to an employee.");
        printf("\nEnter 9 to display single project details.");
        printf("\nEnter 10 to display all projects details.");
        printf("\nEnter 11 to display single employee details.");
        printf("\nEnter 12 to display all employee details.");
        printf("\nEnter 13 to generate month end report of all projects.");
        printf("\nEnter 14 to refresh employee data at month end.");
        printf("\nEnter 15 to delete an employee.");
        printf("\nEnter 16 to delete a project.");
        printf("\nEnter 0 to exit.");
        printf("\nEnter your choice: ");
        scanf("%d",&option);
        switch(option) {
            case 1: {
                //create new database
                destroyGraph(graph, list);
                graph = createGraph();
                if(graph)
                    printf("\nNew project database created.");
                else
                    printf("\nProject database could not be created. Memory overflow. Try again.");
                destroyList(list);
                list = createList();
                if(list)
                    printf("\nNew employee database created.");
                else
                    printf("\nEmployee database could not be created. Memory overflow. Try again.");
                break;
            }
            case 2: {
                //add new project in graph
                fflush(stdin);
                printf("\nEnter name of project: ");
                gets(prj.projectName);
                printf("\nEnter description of project: ");
                gets(prj.projectDescription);
                prjnd = insertProject(graph, prj);
                if(prjnd)
                    printf("\nNew project added to the database.\nProject ID = %d", prjnd->prj.projectID);
                else
                    printf("\nProject could not be created. Memory overflow. Try again.");
                break;
            }
            case 3: {
                //add new employee in list
                fflush(stdin);
                printf("\nEnter Employee full name: ");
                gets(emp.name);
                printf("\nEnter address: ");
                gets(emp.address);
                printf("\nEnter department: ");
                gets(emp.department);
                printf("\nEnter basic pay of employee: ");
                scanf("%f", &emp.sal.basicPay);
                empnd = insertEmployee(list, emp);
                if (empnd)
                    printf("\nNew employee added to the database.\n Employee ID = %d", empnd->emp.empID);
                else
                    printf("\nEmployee could not be created. Memory overflow. Try again.");
                break;
            }
            case 4:{
                //add employee to a project
                if (list->empCount == 0) {
                    printf("\nNo employees in the database.");
                    break;
                }
                printf("\nEnter ID of project: ");
                scanf("%d", &prjID);
                printf("\nEnter ID of employee: ");
                scanf("%d", &empID);
                check = addEmployee(graph, prjID, list, empID);
                if(check == 1)
                    printf("\nEmployee added to the project.");
                else if(check == -1)
                    printf("\nEmployee could not be added. Memory overflow. Try again.");
                else if(check == -2)
                    printf("\nProject could not found. Enter valid input. Try again.");
                else if(check == -3)
                    printf("\nEmployee could not be found. Enter valid input. Try again.");
                else if(check == -4)
                    printf("\nEmployee could not be added. Employee already part of a project.");
                break;
            }
            case 5: {
                //remove employee from project
                if (list->empCount == 0) {
                    printf("\nNo employees in the database.");
                    break;
                }
                printf("\nEnter ID of project: ");
                scanf("%d", &prjID);
                printf("\nEnter ID of employee: ");
                scanf("%d", &empID);
                check = removeEmployee(graph, prjID, list, empID);
                if (check == 1)
                    printf("\nEmployee removed from project.");
                else if (check == -1)
                    printf("\nProject could not found.");
                else
                    printf("\nEmployee not part of the project.");
                break;
            }
            case 6: {
                //grant bonus to employee
                if (list->empCount == 0) {
                    printf("\nNo employees in the database.");
                    break;
                }
                printf("\nEnter ID of employee: ");
                scanf("%d", &empID);
                printf("\nEnter salary amount: ");
                scanf("%f", &sal);
                check = grantBonus(list, empID, sal);
                if (check == 1)
                    printf("\nSalary updated.");
                else
                    printf("\nEmployee could not be found.");
                break;
            }
            case 7: {
                //grant salary to employee
                if (list->empCount == 0) {
                    printf("\nNo employees in the database.");
                    break;
                }
                printf("\nEnter ID of employee: ");
                scanf("%d", &empID);
                printf("\nEnter salary amount: ");
                scanf("%f", &sal);
                check = advanceSal(list, empID, sal);
                if (check == 1)
                    printf("\nSalary updated.");
                else if (check == -1)
                    printf("\nEmployee could not be found.");
                else
                    printf("\nEntered salary greater than employee's salary left.");
                break;
            }
            case 8: {
                //grant leave to employee
                if (list->empCount == 0) {
                    printf("\nNo employees in the database.");
                    break;
                }
                printf("\nEnter ID of employee: ");
                scanf("%d", &empID);
                printf("\nEnter days of leaves: ");
                scanf("%d", &days);
                check = grantLeave(list, empID, days);
                if (check == 1)
                    printf("\nLeaves updated.");
                else if(check == -1)
                    printf("\nEmployee could not be found.");
                else
                    printf("\nEntered number of leaves greater than employee's leaves left.");
                break;
            }
            case 9: {
                //displpay details of single project
                if(graph->prjCount == 0) {
                    printf("\nNo project in the database.");
                    break;
                }
                printf("\nEnter project ID to search: ");
                scanf("%d", &prjID);
                check = displayProject(graph, prjID);
                if (check == -1)
                    printf("\nProject could not be found.");
                break;
            }
            case 10: {
                //display all projects list
                if(graph->prjCount == 0) {
                    printf("\nNo project in the database.");
                    break;
                }
                displayAllProject(graph);
                break;
            }
            case 11: {
                //display single employee details
                if (list->empCount == 0) {
                    printf("\nNo employees in the database.");
                    break;
                }
                printf("\nEnter employee ID to search: ");
                scanf("%d", &empID);
                check = displayEmployee(list, empID);
                if (check == -1)
                    printf("\nEmployee could not be found.");
                break;
            }
            case 12: {
                //display all employees details
                if (list->empCount == 0) {
                    printf("\nNo employees in the database.");
                    break;
                }
                displayAllEmployees(list);
                break;
            }
            case 13: {
                //generate month end report
                if (graph->prjCount == 0) {
                    printf("\nNo project in the database.");
                    break;
                }
                generateReport(graph, list);
                break;
            }
            case 14: {
                //refresh employee data
                if (list->empCount == 0) {
                    printf("\nNo employees in the database.");
                    break;
                }
                refresh(list);
                printf("\nEmployee data refreshed.");
                break;
            }
            case 15: {
                //delete an employee
                if (list->empCount == 0) {
                    printf("\nNo employees in the database.");
                    break;
                }
                printf("\nEnter employee ID to delete: ");
                scanf("%d", &empID);
                check = deleteEmployee(list, empID);
                if (check == 1)
                    printf("\nEmployee removed.");
                else if(check == -1)
                    printf("\nEmployee could not be found.");
                else
                    printf("\nEmployee is assigned to a project. Remove employee from assigned project and try again.");
                break;
            }
            case 16: {
                //delete a project
                if(graph->prjCount == 0) {
                    printf("\nNo project in the database.");
                    break;
                }
                printf("\nEnter project ID to delete: ");
                scanf("%d", &prjID);
                check = deleteProject(graph, prjID, list);
                if (check == 1)
                    printf("\nProject removed.");
                else
                    printf("\nProject could not be found.");
                break;
            }
            case 0: break;
            default: printf("\nInvalid input. Enter a number between 0 to 11.");
        }
    }while(option != 0);
    destroyGraph(graph, list);
    destroyList(list);
}