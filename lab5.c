#include <getopt.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct m {
    int totalFramesCount;
    int freeFramesCount;
    unsigned long* frame; // contains the id of the process and the page using that frame.
    // I make it as an array and each entry has two things ( pid and page number)
    bool* frameIsEmpty; // contains whether the frame is empty
} memory;


enum operation {
    START,
    REFERENCE,
    TERMINATE
};

// checks if page is in memory
bool is_in_memory(memory m, int pid, int pageNumber) {
    for(int i = 0; i < m.totalFramesCount; i++) {
        if(pid == (m.frame[i] >> 16) && pageNumber == (m.frame[i] & 0xffff))
            return true;
    }
    return false;
}

// checks if there is any free memory available
bool has_free_memory(memory m) {
    return m.freeFramesCount > 0;
}

void remove_frames_for_process(memory* m, int pid) {
    for(int i = 0; i < m->totalFramesCount; i++) {
        if(pid == (m->frame[i] >> 16)) {
            m->frameIsEmpty[i] = true;
            m->freeFramesCount++;
        }
    }
}


void add_page_to_memory(memory* m, int pid, int page) {

    for (size_t frame = 0; frame < m->totalFramesCount; ++frame)
    {
        ///I put the pid AND the page number into the frames array
        ///So, each frame takes up two slots
        ///for example [pid, page, pid, page, pid, page]
        ///The reason that I cannot do it like key and value because the key is frame number
        // and the value will be (pid ,  page number ) -> this is not working at all
        /// this is the array of the frame | frame 1| |frame 2|  |frame 3 |

        //int frame_pid = m->frame[frame*2];
        //int frame_page = m->frame[(frame*2)+1];

        bool is_this_frame_free = m->frameIsEmpty[frame];

        if (is_this_frame_free)
        {
            ///fill this frame slot
            unsigned long val = 0;
            val = (val | pid) << 16;
            val = val | page;

            m->frame[frame] = val;

            ///mark the frame as full
            m->frameIsEmpty[frame] = false;

            m->freeFramesCount--;
            return;
        }
    }
}

int main(int argc, char* argv[]) {
    int process;
    int memSize;
    int totalReferences = 0;
    int totalPageFaultCount = 0;
    int processReferences = 0;
    int processPageFaultCount = 0;

    char opt;
    // read parameters
    while ((opt = getopt(argc, argv, "p:s:")) != -1) {
        switch(opt) {
            case 'p':
                if (!sscanf(optarg, "%i", &process)) {
                    fprintf(stderr, "Invalid process id option.\n");
                    exit(1);
                }
                break;
            case 's':
                if (!sscanf(optarg, "%i", &memSize)) {
                    fprintf(stderr, "Invalid memory size option.\n");
                    exit(1);
                }
                break;
            case '?':
                fprintf(stderr, "Unrecognized option -%c.\n", optopt);
                exit(1);
                break;
            case ':':
                fprintf(stderr, "The -%c option is missing an argument.\n",
                        optopt);
                exit(1);
                break;
            default:
                break;
        }
    }
    if (optind != 5) {
        fprintf(stderr, "Missing required arguments.\n");
        exit(1);
    }

    
    // initialize memory
    memory m;
    m.totalFramesCount = memSize;
    m.freeFramesCount = memSize;
    m.frame = malloc(sizeof(unsigned long) * memSize);
    m.frameIsEmpty = malloc(sizeof(bool) * memSize);
    for (int i = 0; i < memSize; i++) {
        m.frameIsEmpty[i] = true;
    }

    // read input from stdin
    enum operation op;
    int pid;
    int pageNumber;
    int addressSpaceSize;

    ///START <PID> <ADDRESSSPACESIZE>
    ///TERMINATE <PID>

    while (true)
    {
        char opstr[10]; // each word at most 10 characters 
        int arg1 = 0, arg2 = 0;
        int num_args = fscanf(stdin, "%9s %d %d\n", opstr, &arg1, &arg2);

        if (num_args == EOF)
            break;

        ///not parse because it's empty
        if (num_args == 0)
            ///skip
            continue;

        if (strcmp(opstr, "START") == 0)
        {
            op = START;
            pid = arg1;
            addressSpaceSize = arg2;

            ///Here START command 
            /// just debugs
            // fprintf(stdout, "START, pid: %d, addressSpaceSize: %d\n", pid, addressSpaceSize);

        } else if (strcmp(opstr, "TERMINATE") == 0) {
            op = TERMINATE;
            pid = arg1;


            ///Here Terminals command 
            /// just debugs
            // fprintf(stdout, "TERMINATE, pid: %d\n", pid);
        } else if (strcmp(opstr, "REFERENCE") == 0) {
            op = REFERENCE;
            pid = arg1;
            pageNumber = arg2;

            ///Here Reerence command 
            /// just debugs
            // fprintf(stdout, "REFERENCE, pid: %d, page: %d\n", pid, pageNumber);


        } else {
            fprintf(stderr, "Invalid command\n%9s", opstr);
        }

        switch(op) {
            case START:
                //create page table
                break;

            case REFERENCE:
                if(!is_in_memory(m, pid, pageNumber)) {
                    if(has_free_memory(m)) {
                        add_page_to_memory(&m, pid, pageNumber);
                    } else { 
                        if(pid == process) processPageFaultCount++;
                        totalPageFaultCount++;
                    }
                }
                if(pid == process) processReferences++;
                totalReferences++;
                break;

            case TERMINATE:
                remove_frames_for_process(&m, pid);
                break;
        }
    }

    free(m.frame);
    free(m.frameIsEmpty);

    fprintf(stdout, "Total page faults: %i.\nProcess page faults: %i.\n",
            totalPageFaultCount, processPageFaultCount);

    return 0;
}
