//Programma che stampa in output lo scheduling di processi seguendo l'algoritmo RR, dati i nomi dei processi, i tempi di arrivo, i tempi di burst e la durata dei quanti di tempo

#include <stdio.h>
#include "RRschedulingLibrary.h"

int main(int argc, const char * argv[]) {
    
    //quanta = time quanta, no_process = number of processes, timeToCompletion = total remaining time to elaborate all processe, current_time = current time in units, realQuanta is used when burst time is lower than quanta
    int quanta, no_process, timeToCompletion = 0, current_time = 0, i = 0, realQuanta = 0;
    
    //User input
    printf("Insert time quanta \n");
    scanf("%d", &quanta);
    printf("Insert number of processes \n");
    scanf("%d", &no_process);
    
    //processes contains all processes, readyQueue contains ready processes, lastRunProcess = last Run process
    struct PROCESS processes[no_process], readyQueue[no_process], lastRunProcess;
    
    //Initialization
    init(no_process, processes);
    initNull(no_process, readyQueue);
    initNullStruct(&lastRunProcess);
    
    readyQueue[0] = processes[0];
    
    computeTimeToCompletion(no_process, readyQueue, &timeToCompletion);
    
    //loop goes on until all processes in Ready queue have been processed and there are not processes coming in the future (i.e. it admits idle processes)
    while (timeToCompletion>0 || checkIfProcessWillArrive(no_process, processes, current_time)) {
        
        i=0;
        
        printf("Current time \t %d \n", current_time);
        
            if (readyQueue[i].t_burst > 0) {
                
                if (readyQueue[i].t_burst >= quanta) {
                    readyQueue[i].t_burst = readyQueue[i].t_burst - quanta;
                    realQuanta = quanta;
                } else {
                    realQuanta = readyQueue[i].t_burst; //Only part of the quanta is used
                    readyQueue[i].t_burst = 0; //Process finishes its burst time
                }
                
                lastRunProcess = readyQueue[i];
                printf("\n Run process \t %c \n", readyQueue[i].name);
            }
        
        current_time = current_time + realQuanta; //Time passes
        
        //Processes in Ready queue are shifted
        removeFirstAndShiftRight(no_process, readyQueue);
        
        //Processes arrived during last quanta are added at the end of the RQ
        for (int j = 0; j<no_process; j++) {
            if ((processes[j].t_arr > current_time-realQuanta) && (processes[j].t_arr <= current_time)) {
                addAtTheEnd(no_process, readyQueue, processes[j]);
            }
        }
        
        //Last run process is added at the end of the RQ if it needs more time to finish execution
        if (lastRunProcess.t_burst > 0) {
            addAtTheEnd(no_process, readyQueue, lastRunProcess);
            //Otherwise, exit time is set
        } else {
            setExitTime(no_process, processes, lastRunProcess, current_time);
        }
        
        //printArray(no_process, readyQueue);
        
        computeTimeToCompletion(no_process, readyQueue, &timeToCompletion);
        
        if (timeToCompletion == 0 && checkIfProcessWillArrive(no_process, processes, current_time)) {
            printf("Running idle \n");
        }
    }
    
    printf("Empty Ready Queue!\n");

    computeAverageTurnAroundTime(no_process, processes);
    computeAverageWaitTime(no_process, processes);

    return 0;
}
