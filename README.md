# CS350-Program1

# Lab 4
Generate list of memeory references simulating a number of running processes

input parameters
- `pid <int a m l>` main process id (process we are testing)
    - `int` process id
    - `a` int specifying address space size in pages
    - `m <1|2|3>` average number of memory references (see below)
    - `l` <1|2|3> for locality of reference (see below)
- `n` 1 to 200 number of different processes
- `a <1|2|3>` average address space size of processes
    - `1` small (1-5 pages)
    - `2` medium (5-20 pages)
    - `3` large (20-50 pafes)
- `m <1|2|3>` average number of memory references
    - `1` small (500 - 2000)
    - `2` medium (2000 - 5000)
    - `3` large (5000 - 10000)
- `l <1|2|3>` locality of reference
    - `1` sparse 40% same page twice in a row
    - `2` medium 70% same page twice in a row
    - `3` highly localized 90% same page twice in a row

# Lab 5
Read input from lab4 program and detect page faults when memory is full
and clear frames used by process when it terminates.

input parameters
- `pid <int>` processes id to focus on for testing for testing (we are testing this process relative to all other processes in input)
- `s <int>` memory size in pages

Output overall page fault rate for provided process and overall page fault rate

# Program 1
Implementing the page replacement mechanisms
