#include <time.h>
#include <stdlib.h>
#include <stdio.h>

typedef struct proc {
    int pid;
    int remaining;
    int start;
    int addressSize;
    int lastPage; 
    // use this to request same page witha certain probability 
    // depending on locality of reference. 1 - 40%, 2 - 70%, 3 - 90%
} process;

int main(int argc, char* argv[]) {
    // default settings
    srand(time(NULL));
    int processId = 1;
    int numProcesses = 10;
    int mainAddress = 4, mainLocality = 2;
    int rangeAddress = 2, locality = 2;

    // read input and check bounds for parameters
    
    process processes[numProcesses];
    int runningStart = 1;
    // generate processes, put into processes array.
    processes[0].pid = processId;
    processes[0].remaining = 1000;
    processes[0].start = runningStart++;
    processes[0].addressSize = mainAddress;
    processes[0].lastPage = 0;

    for(int i = 1; i < numProcesses; i++) {
        processes[i].pid = i + processId;
        processes[i].remaining = (rand() % 10000) + 1000;
        processes[i].start = runningStart++;
        if(rangeAddress == 1) processes[i].addressSize = (rand() % 5) + 1;
        else if(rangeAddress == 2) processes[i].addressSize = (rand() % 15) + 5;
        else processes[i].addressSize = (rand() % 30) + 20;
        processes[i].lastPage = 0;
    }

    // loop over each process checking if it should start now. If yes, print starting otherwise
    // randomly select processes for memory access, decrementing remaining
    // counter in process. Delete process from processes array and print exit when
    // counter reaches 0.
    
}
