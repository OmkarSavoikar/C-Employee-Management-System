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

listNd* createList() {
    listNd *list;
    list = (listNd *)malloc(sizeof(listNd));
    if (list) {
        list->empCount = 0;
        list->eID = 1;
        list->firstEmp = NULL;
    }
    return list;
}

float calcSal(listNd *list, int empID) {
    //return total salary
    empNd *temp;
    float sum = 0.0;
    temp = list->firstEmp;
    while (temp != NULL) {
        if (temp->emp.empID == empID) {
            sum = temp->emp.sal.basicPay + temp->emp.sal.DA + temp->emp.sal.HRA + temp->emp.sal.PA + temp->emp.sal.TA + temp->emp.sal.bonus;
            break;
        }
        temp = temp->nextEmp;
    }
    return sum;
}

empNd* insertEmployee(listNd *list, empstr emp) {
    //return empNd*: success
    //return NULL: memory couldnt be created
    empNd *newEmp, *temp;
    newEmp = (empNd *)malloc(sizeof(empNd));
    if (newEmp) {
        newEmp->emp.empID = list->eID;
        strcpy(newEmp->emp.name, emp.name);
        strcpy(newEmp->emp.address, emp.address);
        strcpy(newEmp->emp.department, emp.department);
        strcpy(newEmp->emp.prjAssigned, "-");
        newEmp->emp.sal.basicPay = emp.sal.basicPay;
        newEmp->emp.sal.HRA = emp.sal.basicPay * 0.2;
        newEmp->emp.sal.DA = emp.sal.basicPay * 0.2;
        newEmp->emp.sal.TA = emp.sal.basicPay * 0.2;
        newEmp->emp.sal.PA = emp.sal.basicPay * 0.2;
        newEmp->emp.sal.bonus = 0;
        newEmp->emp.salAdvance = 0;
        newEmp->emp.leavesLeft = 10;
        newEmp->emp.leavesTaken = 0;
        newEmp->emp.leavesTotal = 10;
        newEmp->nextEmp = NULL;
        if (list->firstEmp == NULL) {
            list->firstEmp = newEmp;
            temp = list->firstEmp;
        }
        else {
            temp = list->firstEmp; 
            while (temp->nextEmp != NULL) 
                temp = temp->nextEmp;
            temp->nextEmp = newEmp;
            temp = temp->nextEmp;
        }
        temp->emp.sal.total = calcSal(list, temp->emp.empID);
        temp->emp.salLeft = calcSal(list, temp->emp.empID);
        (list->eID)++;
        (list->empCount)++;
    }
    return newEmp;
}

void refresh(listNd *list) {
    empNd *temp;
    temp = list->firstEmp;
    while (temp->nextEmp != NULL) {
        temp->emp.leavesTotal = 10;
        temp->emp.leavesTaken = 0;
        temp->emp.leavesLeft = 10;
        temp->emp.salAdvance = 0;
        temp->emp.sal.bonus = 0;
        temp->emp.salLeft = temp->emp.sal.total = calcSal(list, temp->emp.empID);
        temp = temp->nextEmp;
    }
}

int grantBonus(listNd *list, int empID, float bonus) {
    //return 1: success
    //return -1: failure
    empNd *temp;
    temp = list->firstEmp;
    while (temp != NULL) {
        if (temp->emp.empID == empID) {
            temp->emp.sal.bonus += bonus;
            temp->emp.salLeft += bonus;
            temp->emp.sal.total = calcSal(list, temp->emp.empID);
            return (1);
        }
        temp = temp->nextEmp;
        return (-1);
    }
}

int advanceSal(listNd *list, int empID, float sal) {
    //return 1: success
    //return -1: employee not found
    //return -2: asked salary greater than salary left
    empNd *temp;
    temp = list->firstEmp;
    while (temp != NULL) {
        if (temp->emp.empID == empID) {
            if (temp->emp.salLeft < sal) 
                return (-2);
            temp->emp.salAdvance += sal;
            temp->emp.salLeft = temp->emp.sal.total - temp->emp.salAdvance;
            return (1);
        }
        temp = temp->nextEmp;
    }
    return (-1);
}

int grantLeave(listNd *list, int empID, int leave) {
    //return 1: success
    //return -1: employee not found
    //return -2: leaves asked for is greater than total leaves
    empNd *temp;
    temp = list->firstEmp;
    while (temp != NULL) {
        if (temp->emp.empID == empID) {
            if (temp->emp.leavesLeft < leave)
                return (-2);
            temp->emp.leavesTaken += leave;
            temp->emp.leavesLeft -= leave;
            return (1);
        }
        temp = temp->nextEmp;
    }
    return (-1);
}

int displayEmployee(listNd *list, int empID) {
    //return 1: success
    //return -1: failure
    empNd *temp;
    temp = list->firstEmp;
    while (temp != NULL) {
        if (temp->emp.empID == empID) {
            printf("\nEmpID = %d", temp->emp.empID);
            printf("\nFull name = %s", temp->emp.name);
            printf("\nAddress = %s", temp->emp.address);
            printf("\nDepartment = %s", temp->emp.department);
            printf("\nProject assigned = %s", temp->emp.prjAssigned);
            printf("\nTotal salary = %g", temp->emp.sal.total);
            printf("\nSalary advance = %g", temp->emp.salAdvance);
            printf("\nSalary left = %g", temp->emp.salLeft);
            printf("\nTotal leaves = %d", temp->emp.leavesTotal);
            printf("\nLeaves taken = %d", temp->emp.leavesTaken);
            printf("\nLeaves left = %d", temp->emp.leavesLeft);
            printf("\n----------------------------------------------------------------");
            return (1);
        }
        temp = temp->nextEmp;
    }
    return (-1);
}

void displayAllEmployees(listNd *list) {
    empNd *temp;
    temp = list->firstEmp;
    while (temp != NULL) {
        displayEmployee(list, temp->emp.empID);
        temp = temp->nextEmp;
    }
}

int deleteEmployee(listNd* list, int ID) {
    //return 1: success
    //return -1: employee not found
    //return -2: employee working on a project
    empNd *prev, *del;
    del = list->firstEmp;
    prev = NULL;
    int success = -1;
    while (del != NULL) {
        if (del->emp.empID == ID){
            success = 1;
            break;
        }
        prev = del;
        del = del->nextEmp;
    }
    if (success == 1) {
        if(strcmp("-", del->emp.prjAssigned) != 0)
            return(-2);
        if (prev == NULL)
            list->firstEmp = del->nextEmp;
        else
            prev->nextEmp = del->nextEmp;
        free(del);
        (list->empCount)--;
    }
    return(success);
}

void destroyList(listNd *list) {
    empNd *temp;
    temp = list->firstEmp;
    while (temp != NULL) {
        deleteEmployee(list, temp->emp.empID);
        temp = temp->nextEmp;
    }
    free(list);
}