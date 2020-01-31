//
//  RRschedulingLibrary.c
//  SchedulingRR
//
//  Created by Nicolò Cogno on 24/01/20.
//  Copyright © 2020 Nicolò Cogno. All rights reserved.
//

#include "RRschedulingLibrary.h"

void init(int n, struct PROCESS *ptr) {
    
    for (int i = 0; i<n; i++) {
        printf("%d process name (1 character only) \n", i+1);
        scanf(" %c", &((*(ptr+i)).name));
        printf("%d process arrival time \n", i+1);
        scanf("%d", &((*(ptr+i)).t_arr));
        printf("%d process burst time \n", i+1);
        scanf("%d", &((*(ptr+i)).t_burst));
    }
}

void initNull(int n, struct PROCESS *ptr) {
    
    for (int i = 0; i<n; i++) {
        ((*(ptr+i)).name) = '\0';
        ((*(ptr+i)).t_arr) = 0;
        ((*(ptr+i)).t_burst) = 0;
    }
}

void removeFirstAndShiftRight(int n, struct PROCESS *ptr) {
    
    for (int i = 0; i<n-1; i++) {
        ((*(ptr+i)).name) = ((*(ptr+i+1)).name);
        ((*(ptr+i)).t_arr) = ((*(ptr+i+1)).t_arr);
        ((*(ptr+i)).t_burst) = ((*(ptr+i+1)).t_burst);
    }
    ((*(ptr+n-1)).name) = '\0';
    ((*(ptr+n-1)).t_arr) = 0;
    ((*(ptr+n-1)).t_burst) = 0;
    
}

int checkIfProcessWillArrive(int n, struct PROCESS *ptr, int now) {
    
    int processWillArrive = 0;
    
    for (int i = 0; i<n; i++) {
        if (((*(ptr+i)).t_arr) > now) {
            processWillArrive = 1;
        }
    }
    
    return processWillArrive;
}

void addAtTheEnd(int n, struct PROCESS *ptr, struct PROCESS last) {
    
    int foundLast = 0, i = 0;
    
    do {
        if (((*(ptr+i)).name) == '\0') {
            ptr[i] = last;
            foundLast = 1;
        }
        i++;
    } while(foundLast == 0);
}

void printArray(int n, struct PROCESS *ptr) {
    printf(" \n Array: \t");
    for (int i = 0; i<n; i++) {
        if (((*(ptr+i)).name) != '\0') {
            printf("%c \t",((*(ptr+i)).name));
        }
    }
    
}

void initNullStruct(struct PROCESS *proc) {
    (*proc).name = '\0';
    (*proc).t_arr = 0;
    (*proc).t_burst = 0;
}

void computeTimeToCompletion(int n, struct PROCESS *ptr, int *time_ptr) {
    
    *time_ptr = 0;
    
    for (int i = 0; i<n; i++) {
        *time_ptr = *time_ptr + (*(ptr+i)).t_burst;
    }
    
    //printf(" \n Time to completion \t %d \n", *time_ptr);
}

void setExitTime(int n, struct PROCESS *ptr, struct PROCESS last, int now) {
    for (int i = 0; i<n; i++) {
        if (((*(ptr+i)).name) == last.name) {
            ((*(ptr+i)).t_exit) = now;
        }
    }
    
}

void computeAverageTurnAroundTime(int n, struct PROCESS *ptr) {
    
    float averageTurnAroundTime = 0, totalTurnAroundTime = 0;
    
    for (int i = 0; i<n; i++) {
            totalTurnAroundTime += (((*(ptr+i)).t_exit)-((*(ptr+i)).t_arr));
    }
    
    averageTurnAroundTime = totalTurnAroundTime/n;
    
    printf("Average TurnAround time = %f \n", averageTurnAroundTime);
    
}

void computeAverageWaitTime(int n, struct PROCESS *ptr) {
    
    float averageWaitTime = 0, totalWaitTime = 0;
    
    for (int i = 0; i<n; i++) {
        totalWaitTime += (((*(ptr+i)).t_exit)-((*(ptr+i)).t_arr)-((*(ptr+i)).t_burst));
    }
    
    averageWaitTime = totalWaitTime/n;
    
    printf("Average Wait time = %f \n", averageWaitTime);
    
}
