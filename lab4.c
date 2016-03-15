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
    int processId = 1;
    int numProcesses = 1;
    int mainAddress = 4, mainLocality = 2;
    int rangeAddress = 2, locality = 2;

    // read input and check bounds for parameters
    
    process processes[numProcesses];
    // generate processes, put into processes array.
   

    // loop over each process checking if it should start now. If yes, print starting otherwise
    // randomly select processes for memory access, decrementing remaining
    // counter in process. Delete process from processes array and print exit when
    // counter reaches 0.
    
}
