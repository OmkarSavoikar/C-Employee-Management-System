/*
    AUTHOR: MCA.2104, MCA.2103
    PROGRAM: PROJECT
    DATE CREATED: 18 NOV 2021
    DATE MODIFIED: 29 DEC 2021
*/
//DS DEVELOPER
#include<stdio.h>
#include<conio.h>
#include<stdbool.h>
#include<string.h>
#include<malloc.h>
#include"employee.h"
#include"project.h"

graphNd* createGraph() {
    graphNd* graph;
    graph = (graphNd *)malloc(sizeof(graphNd));
    if (graph) {
        graph->prjCount = 0;
        graph->pID = 1;
        graph->firstProject = NULL;
    }
    return graph;
}

projectNd* insertProject(graphNd *graph, prjstr newPrj) {
    //return newProject: success
    //return NULL: memory couldnt be created
    projectNd *newProject, *temp;
    newProject = (projectNd *) malloc (sizeof(projectNd));
    if (newProject) {
        newProject->prj.projectID = graph->pID;
        strcpy(newProject->prj.projectName, newPrj.projectName);
        strcpy(newProject->prj.projectDescription, newPrj.projectDescription);
        newProject->prj.empCount = 0;
        newProject->firstEmp = NULL;
        newProject->nextProject = NULL;
        if (graph->firstProject == NULL)
            graph->firstProject = newProject;
        else {
            temp = graph->firstProject;
            while (temp->nextProject != NULL)
                temp = temp->nextProject;
            temp->nextProject = newProject;
        }
        (graph->pID)++;
        (graph->prjCount)++;
    }
    return newProject;
}

int addEmployee(graphNd *graph, int prjID, listNd *list, int empID) {
    //return 1: success
    //return -1: memory couldnt be created
    //return -2: project doesnt exist
    //return -3: employee doesnt exist
    //return -4: employee already working on another project
    linkNd *newLink, *temp;
    projectNd *src;
    empNd *emp;
    int success = -2;
    src = graph->firstProject;
    while (src != NULL) {
        if (src->prj.projectID == prjID) {
            success = -1;
            break;
        }
        src = src->nextProject;
    }
    if (success == -1) {
        emp = list->firstEmp;
        while (emp != NULL) {
            if (emp->emp.empID == empID) {
                if (strcmp("-", emp->emp.prjAssigned) == 0) {
                    strcpy(emp->emp.prjAssigned, src->prj.projectName);
                    success = 1;
                    break;
                }
                return(-4);
            }
            emp = emp->nextEmp;
        }
        if (success == 1) {
            newLink = (linkNd *)malloc(sizeof(linkNd));
            if (newLink) {
                newLink->destination = emp->emp;
                newLink->nextLink = NULL;
                if (src->firstEmp == NULL)
                    src->firstEmp = newLink;
                else {
                    temp = src->firstEmp;
                    while (temp->nextLink != NULL)
                        temp = temp->nextLink;
                    temp->nextLink = newLink;
                }
                (src->prj.empCount)++;
                return (1); //Added employee to project
            }
            return (-1); //Memory overflow
        }
        return (-3); //Employee not found
    }
    return (-2); //Project not found
}

int displayProject(graphNd *graph, int prjID) {
    //return 1: success
    //return -1: project not found
    projectNd *project;
    linkNd *link;
    project = graph->firstProject;
    while (project != NULL) {
        if (project->prj.projectID == prjID) {
            printf("\nProject ID: %d", project->prj.projectID);
            printf("\nProject name: %s", project->prj.projectName);
            printf("\nProject description: %s", project->prj.projectDescription);
            printf("\nEmployees working: %d", project->prj.empCount);
            link = project->firstEmp;
            while (link != NULL) {
                printf("\nEmployee ID: %d", link->destination.empID);
                printf("\nEmployee name: %s", link->destination.name);
                link = link->nextLink;
            }
            printf("\n----------------------------------------------------------------");
            return (1);
        }
        project = project->nextProject;
    }
    return (-1);
}

void displayAllProject(graphNd *graph) {
    projectNd *project;
    project = graph->firstProject;
    while (project != NULL) {
        displayProject(graph, project->prj.projectID);
        project = project->nextProject;
    }
}

void generateReport(graphNd *graph, listNd *list) {
    projectNd *project;
    linkNd *link;
    empNd *emp;
    int leave = 0;
    float sal = 0.0;
    float adv = 0.0;
    project = graph->firstProject;
    while (project != NULL) {
        displayProject(graph, project->prj.projectID);
        link = project->firstEmp;
        while (link != NULL) {
            emp = list->firstEmp;
            while(link->destination.empID != emp->emp.empID)
                emp = emp->nextEmp;
            leave += emp->emp.leavesTaken;
            sal += calcSal(list, link->destination.empID);
            adv += emp->emp.salAdvance;
            link = link->nextLink;
        }
        printf("\nReport:");
        printf("\nTotal salary to be paid to employees working on the project = %g", sal);
        printf("\nSalary advance given to employees working on the project = %g", adv);
        printf("\nSalary to be paid to employees working on the project = %g", sal-adv);
        printf("\nTotal leaves taken by employees working on the project = %d", leave);
        printf("\n----------------------------------------------------------------");
        project = project->nextProject;
    }
}

int removeEmployee(graphNd *graph, int prjID, listNd *list, int empID) {
    //return 1: success
    //return -1: project not found in the database
    //return -2: employee not found in the project list
    projectNd *project;
    linkNd *prev, *del;
    empNd *emp;
    int success = -3;
    project = graph->firstProject;
    while (project != NULL) {
        if (project->prj.projectID == prjID) {
            //Project found
            success = -1;
            break;
        }
        project = project->nextProject;
    }
    if (success == -1) {
        emp = list->firstEmp;
        del = project->firstEmp;
        prev = NULL;
        while (del != NULL) {
            if (del->destination.empID == empID) {
                //Employee found
                strcpy(emp->emp.prjAssigned, "-");
                success = 1;
                break;
            }
            prev = del;
            del = del->nextLink;
            emp = emp->nextEmp;
        }
        if (success == 1) {
            if (prev == NULL)
                project->firstEmp = del->nextLink;
            else
                prev->nextLink = del->nextLink;
            free(del);
            (project->prj.empCount)--;
            return (1); //Deleted
        }
        return (-2); //Employee not found
    }
    return (-1); //Project not found
}

int deleteProject(graphNd* graph, int prjID, listNd *list) {
    //return 1: success
    //return -1: project not found
    projectNd *prev, *del;
    linkNd *emp, *temp;
    int success = 0;
    del = graph->firstProject;
    prev = NULL;
    while (del != NULL) {
        if (del->prj.projectID == prjID) {
            //Project found
            success = 1;
            break;
        }
        prev = del;
        del = del->nextProject;
    }
    if (success == 1) {
        temp = del->firstEmp;
        while (temp != NULL) {
            removeEmployee(graph, del->prj.projectID, list, temp->destination.empID);
            temp = temp->nextLink;
        }
        if (prev == NULL)
            graph->firstProject = del->nextProject;
        else
            prev->nextProject = del->nextProject;
        free(del);
        (graph->prjCount)--;
        return (1);
    }
    return (-1); //Project not found
}

void destroyGraph(graphNd *graph, listNd *list) {
    projectNd *src;
    linkNd *dest;
    int delProject, delEmp;
    delProject = delEmp = 1;
    while ((graph->firstProject != NULL) && (delProject == 1)) {
        src = graph->firstProject;
        delProject = deleteProject(graph, src->prj.projectID, list);
    }
    free(graph);
}