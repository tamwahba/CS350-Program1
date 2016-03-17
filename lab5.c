#include <stdbool.h>

typedef struct m {
    int freeFramesCount;
    unsigned long* frame; // contains the id of the process and the page using that frame.
    bool* frameIsEmpty; // contains whether the frame is empty
} memory;

enum operation {
    START,
    REFERENCE,
    TERMINATE
};

// checks if page is in memory
bool is_in_memory(memory m, int pid, int pageNumber) {

}

// checks if there is any free memory available
bool has_free_memory(memory m) {
    return m.freeFramesCount > 0;

}

void remove_frames_for_process(memory m, int pid) {

}

void add_page_to_memory(memory m, int pid, int page) {

}

int main(int argc, char* argv[]) {
    int totalReferences = 0;
    int totalPageFaultCount = 0;
    int processReferences = 0;
    int processPageFaultCount = 0;
    
    // read parameters
    
    // initialize memory

    // read input from stdin 
    enum operation op;
    int pid;
    int pageNumber;
    int addressSpaceSize;

    // if start create page tabel
    // if reference
    //  check if page is not in memory
        if (!is_in_memory()) {
        }
    //      check if has free memory 
    //          add page to memory
    //      else 
    //          increment page fault counter
                totalPageFaultCount++;
    //  if terminate
    //      remove frames from memory


    return 0;
}
