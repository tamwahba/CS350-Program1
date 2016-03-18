#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <string.h>

#define FRAME_COUNT 100


typedef struct m {
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

  return 0;

}

// checks if there is any free memory available
bool has_free_memory(memory m) {
    return m.freeFramesCount > 0;

}

void remove_frames_for_process(memory* m, int pid) {

}

void add_page_to_memory(memory* m, int pid, int page) {

  for (size_t frame = 0; frame < FRAME_COUNT; ++frame)
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

        ///set the pid
        m->frame[frame*2] = pid;
        ///set the page
        m->frame[(frame*2)+1] = page;

        ///mark the frame as full
        m->frameIsEmpty[frame] = false;

        m->freeFramesCount--;
        return;
    }
  }
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
          ///TODO: remove scaffolding
          fprintf(stdout, "START, pid: %d, addressSpaceSize: %d\n", pid, addressSpaceSize);

        } else if (strcmp(opstr, "TERMINATE") == 0) {
          op = TERMINATE;
          pid = arg1;


          ///TODO: do whatever the TERMINATE command does
          ///TODO: remove scaffolding
          fprintf(stdout, "TERMINATE, pid: %d\n", pid);
        } else if (strcmp(opstr, "REFERENCE") == 0) {
          op = REFERENCE;
          pid = arg1;
          pageNumber = arg2;

          ///TODO: do whatever the REFERENCE command does
          ///TODO: remove scaffolding
          fprintf(stdout, "REFERENCE, pid: %d, page: %d\n", pid, pageNumber);


        } else {
          fprintf(stderr, "Invalid command\n%9s", opstr);
        }
    }

    // if start create page tabel
    // if reference
    //  check if page is not in memory
      // if (!is_in_memory()) {
      // }
    //      check if has free memory
    //          add page to memory
    //      else
    //          increment page fault counter
                // totalPageFaultCount++;
    //  if terminate
    //      remove frames from memory


    return 0;
}
