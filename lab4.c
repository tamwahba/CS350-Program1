#include <time.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//from https://stackoverflow.com/questions/1644868/c-define-macro-for-debug-printing
#define DEBUG 0
#define debug_print(fmt, ...) \
    do { if (DEBUG) fprintf(stderr, fmt, __VA_ARGS__); } while (0)

typedef struct proc {
    int pid;
    int remaining;
    int start;
    int addressSize;
    int lastPage;
} process;


void print_usage(FILE* out)
{


    fprintf(out, "Usage:\n\n");
    fprintf(out, "program1 -h -pid <PID A L> -n <N> -a <1|2|3> -m <1|2|3> -l <1|2|3>\n");
    fprintf(out, "\n");
    fprintf(out, "-h      Print this help\n");
    fprintf(out, "\n");
    fprintf(out, "-pid    Main process specs\n");
    fprintf(out, " PID   Process ID for the main process\n");
    fprintf(out, " A     Address space size for the main process, measured in the number of pages\n");
    fprintf(out, " L     Locality of reference for the main process, measured in 1,2,3 for sparse, medium, highly localized (see below)\n");
    fprintf(out, "\n");
    fprintf(out, "-n      This option specifies number of additional processes\n");
    fprintf(out, " N     Number of additional processes (in range 1 to 200)\n");
    fprintf(out, "\n");
    fprintf(out, "-a      Average address space size for the additional processes\n");
    fprintf(out, " 1     Small (1-5 pages)\n");
    fprintf(out, " 2     Medium (5-20 pages)\n");
    fprintf(out, " 3     Large (20-50 pages)\n");
    fprintf(out, "\n");
    fprintf(out, "-m      Memory pressure for the additional processes\n");
    fprintf(out, " 1     Little\n");
    fprintf(out, " 2     Medium\n");
    fprintf(out, " 3     High\n");
    fprintf(out, "\n");
    fprintf(out, "-l      Locality of reference for the additional processes\n");
    fprintf(out, " 1     Sparse\n");
    fprintf(out, " 2     Medium\n");
    fprintf(out, " 3     Highly Localized\n");
}

int main(int argc, char* argv[]) 
{


    // default settings
    ///PID
    srand(time(NULL));
    int processId = 1;
    ///N
    int numProcesses = 1;
    ///pid.A, pid.L
    int mainAddress = 4, mainLocality = 2;
    ///A, L
    int rangeAddress = 2, locality = 2;



    ///NOTE: I had to add this variable.
    int memoryPressure = 2;

    // read input and check bounds for parameters

    bool seen_pid = false;
    bool seen_n = false;
    bool seen_a = false;
    bool seen_m = false;
    bool seen_l = false;


    for (int arg_index = 1; arg_index < argc; ++arg_index)
    {
         char* arg = argv[arg_index];


        if (strcmp(arg, "-h") == 0)
        {
            print_usage(stdout);
            exit(0);
        } else if (strcmp(arg, "-pid") == 0) {
            ///reading the `pid` argument

            if (seen_pid)
            {
                ///have something like:
                ///./program1 -pid 1 2 3 -pid 1 2 3
                print_usage(stderr);
                exit(-1);
            }

            ///need to make sure there are 3 additional arguments, elsewise it is a usage error.
            if (!(arg_index + 3 < argc))
            {
                print_usage(stderr);
                exit(-1);
            }

            ///read the next argument, and convert it to a integer
            processId = atoi(argv[arg_index + 1]);

            mainAddress = atoi(argv[arg_index + 2]);

            mainLocality = atoi(argv[arg_index + 3]);

            if (mainLocality < 1 || mainLocality > 3)
            {
                fprintf(stderr, "Error: invalid value for -pid, l=%i, should be in range [1,3]\n\n", mainLocality);

                ///have something like:
                ///./program1 -pid 51022 45 4
                print_usage(stderr);
                exit(-1);
            }
            arg_index += 3;
            seen_pid = true;
        } else if (strcmp(arg, "-n") == 0) {
            ///reading the `n` argument

            if (seen_n)
            {
                ///./program1 -n 1 -n 1
                print_usage(stderr);
                exit(-1);
            }

            ///need to make sure there are 1 additional arguments, elsewise it is a usage error.
            if (!(arg_index + 1 < argc))
            {
                ///have something like:
                ///./program1 -n
                print_usage(stderr);
                exit(-1);
            }

            ///read the next argument, and convert it to a integer
            numProcesses = atoi(argv[arg_index + 1]);

            if (numProcesses < 1 || numProcesses > 200)
            {
                fprintf(stderr, "Error: invalid value for -n (%i), should be in range [1,200]\n\n", numProcesses);

                ///have something like:
                ///./program1 -n 201
                print_usage(stderr);
                exit(-1);
            }

            arg_index += 1;
            seen_n = true;
        } else if (strcmp(arg, "-a") == 0) {
            ///reading the `a` argument

            if (seen_a)
            {
                ///have something like:
                ///./program1 -a 1 -a 1
                print_usage(stderr);
                exit(-1);
            }
            if (!(arg_index + 1 < argc))
            {
                print_usage(stderr);
                exit(-1);
            }

            ///read the next argument, and convert it to a integer
            rangeAddress = atoi(argv[arg_index + 1]);

            if (rangeAddress < 1 || rangeAddress > 3)
            {
                fprintf(stderr, "Error: invalid value for -a (%i), should be in range [1,3]\n\n", rangeAddress);

                ///have something like:
                ///./program1 -a 4
                print_usage(stderr);
                exit(-1);
            }

            arg_index += 1;
            seen_a = true;
        } else if (strcmp(arg, "-m") == 0) {
            ///reading the `m` argument

            if (seen_m)
            {
                ///have something like:
                ///./program1 -m 1 -m 1
                print_usage(stderr);
                exit(-1);
            }
            if (!(arg_index + 1 < argc))
            {
                ///have something like:
                ///./program1 -m
                print_usage(stderr);
                exit(-1);
            }

            memoryPressure = atoi(argv[arg_index + 1]);

            if (memoryPressure < 1 || memoryPressure > 3)
            {
                fprintf(stderr, "Error: invalid value for -m (%i), should be in range [1,3]\n\n", memoryPressure);

                ///have something like:
                ///./program1 -m 4
                print_usage(stderr);
                exit(-1);
            }

            arg_index += 1;
            seen_m = true;
        } else if (strcmp(arg, "-l") == 0) {
            ///reading the `l` argument

            if (seen_l)
            {
                ///have something like:
                ///./program1 -l 1 -l 1
                print_usage(stderr);
                exit(-1);
            }
            if (!(arg_index + 1 < argc))
            {
                ///have something like:
                ///./program1 -l
                print_usage(stderr);
                exit(-1);
            }

            ///read the next argument, and convert it to a integer
            locality = atoi(argv[arg_index + 1]);

            if (locality < 1 || locality > 3)
            {
                fprintf(stderr, "Error: invalid value for -l (%i), should be in range [1,3]\n\n", locality);

                ///have something like:
                ///./program1 -l 4
                print_usage(stderr);
                exit(-1);
            }
            arg_index += 1;
            seen_l = true;
        } else {
            fprintf(stderr, "Error: unknown argument %s\n\n", argv[arg_index]);

            ///this means something like:
            ///./program1 not on our print usage 
            print_usage(stderr);
            exit(-1);
        }

    }


    // I made this print statments to check the outputs

    debug_print("processId: %i\n", processId);
    debug_print("numProcesses: %i\n", numProcesses);
    debug_print("mainAddress: %i\n", mainAddress);
    debug_print("mainLocality: %i\n", mainLocality);
    debug_print("rangeAddress: %i\n", rangeAddress);
    debug_print("locality: %i\n", locality);
    debug_print("memoryPressure: %i\n", memoryPressure);

    debug_print("seen_pid: %s\n", (seen_pid ? "true" : "false"));
    debug_print("seen_n: %s\n", (seen_n ? "true" : "false"));
    debug_print("seen_a: %s\n", (seen_a ? "true" : "false"));
    debug_print("seen_m: %s\n", (seen_m ? "true" : "false"));
    debug_print("seen_l: %s\n", (seen_l ? "true" : "false"));



        
    process processes[numProcesses];
    int runningStart = 0;
    unsigned long totalRequests = 0;

    //Generating focused process
    processes[0].pid = processId;
    processes[0].remaining = 1000;
    processes[0].start = runningStart++;
    processes[0].addressSize = mainAddress;
    processes[0].lastPage = 0;

    //Generating other processes
    for(int i = 1; i < numProcesses; i++) {
        processes[i].pid = i + processId;
        processes[i].remaining = (rand() % 10000) + 1000;
        processes[i].start = runningStart++;
        if(rangeAddress == 1) processes[i].addressSize = (rand() % 5) + 1;
        else if(rangeAddress == 2) processes[i].addressSize = (rand() % 15) + 5;
        else processes[i].addressSize = (rand() % 30) + 20;
        processes[i].lastPage = 0;
        totalRequests += processes[i].remaining;
    }


    // loop over each process checking if it should start now. If yes, print starting otherwise
    // randomly select processes for memory access, decrementing remaining
    // counter in process. Delete process from processes array and print exit when
    // counter reaches 0.
    int requests = 0;
    int remainingProcesses = numProcesses;
    while (remainingProcesses > 0) {
        for (int i = 0; i < remainingProcesses; i++) {
            if (processes[i].start == requests) {
                printf("START %i %i\n", 
                        processes[i].pid, processes[i].addressSize);
            break;
            }
        }
        
        int currentIdx = rand() % remainingProcesses;
        process* current = &(processes[currentIdx]);
        if (current->start > requests) {
            continue;
        } 
            
        if (current->remaining == 0) {
            printf("TERMINATE %i\n", current->pid);
            for (int i = currentIdx; i < remainingProcesses; i++) {
                processes[i] = processes[i + 1];
            }
            remainingProcesses--;
            continue;
        }
        
        double samePageProb;
        if (locality == 1) { samePageProb = 0.4; }
        else if (locality == 2) {samePageProb = 0.7; }
        else { samePageProb = 0.9; }
        // from http://stackoverflow.com/questions/3771551/how-to-generate-a-boolean-with-p-probability-using-c-rand-function
        bool samePage = rand() < (samePageProb * ((double)RAND_MAX + 1.0));
        
        int page = rand() % current->addressSize;
        while (page == current->lastPage && current->addressSize > 1) { 
            page = rand() % current->addressSize; 
        }
        
        printf("REFERENCE %i %i\n", 
                current->pid, samePage ? current->lastPage : page);
        current->lastPage = page;
        current->remaining--;
        requests++; 
    }

    return 0;
}
