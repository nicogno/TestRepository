//
//  RRschedulingLibrary.h
//  SchedulingRR
//
//  Created by Nicolò Cogno on 24/01/20.
//  Copyright © 2020 Nicolò Cogno. All rights reserved.
//

#ifndef RRschedulingLibrary_h
#define RRschedulingLibrary_h

#include <stdio.h>

struct PROCESS {
    char name;
    int t_arr;
    int t_burst;
    int t_exit;
};

void init(int n, struct PROCESS *ptr);

void initNull(int n, struct PROCESS *ptr);

void initNullStruct(struct PROCESS *proc);

void removeFirstAndShiftRight(int n, struct PROCESS *ptr);

void addAtTheEnd(int n, struct PROCESS *ptr, struct PROCESS last);

void printArray(int n, struct PROCESS *ptr);

void computeTimeToCompletion(int n, struct PROCESS *ptr, int *time_ptr);

int checkIfProcessWillArrive(int n, struct PROCESS *ptr, int now);

void setExitTime(int n, struct PROCESS *ptr, struct PROCESS last, int now);

void computeAverageTurnAroundTime(int n, struct PROCESS *ptr);

void computeAverageWaitTime(int n, struct PROCESS *ptr);

#endif /* RRschedulingLibrary_h */
