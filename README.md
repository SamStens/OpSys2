Banker's Algorithm for Deadlock Avoidance
Overview
This C++ program implements the Banker's algorithm for deadlock avoidance. 
The Banker's algorithm is a resource allocation and deadlock avoidance algorithm 
that is used in operating systems. It ensures that the system remains in a safe state by 
determining whether granting a resource request will leave the system in a safe state or not.

Usage
To compile and run the program, follow these steps:

Open a terminal in the directory containing the source code (banker_algorithm.cpp).
Compile the program using the following command:
g++ banker_algorithm.cpp -o banker_algorithm
./banker_algorithm input.txt

Input file Format 
Processes   A   B   C
P0          7   5   3
P1          3   2   2
P2          9   0   2
P3          2   2   2
P4          4   3   3
The first row represents the resource types (A, B, C).
The next rows represent the maximum resource need (max), resource allocation (allocation), 
and resource need (need) for each process (P0, P1, ..., P4).
The last row represents the available resources.

Output
After running the program, it will output whether the system is in a safe state or not. 
If it is in a safe state, it will provide the safe sequence.

