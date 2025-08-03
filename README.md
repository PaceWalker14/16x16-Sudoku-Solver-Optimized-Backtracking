##16x16 Sudoku-Solver Optimized-Backtracking
This is a fast and simple 16x16 Sudoku solver I wrote in C++. It uses optimized backtracking with a simple but powerful heuristic(Always fill the cell with the fewest valid options first)

How it works
```
The Sudoku grid is 16x16 (supports numbers 1-9 and letters A-G [base 16 logic] ).

The grid is read as a single block of input, row by row.

Hex conversion

Empty cells are represented by "0" or "."
It uses a simple recursive solve() function with backtracking:

Always picks the empty cell with the least number of possibilities.

This greatly improves performance.

If stuck, it backtracks cleanly.
```
Example of input:
```
. . . . . . . . . . . . . . . .
. . . . . . . . . . . . . . . .
. . . . . . . . . . . . . . . .
. . . . . . . . . . . . . . . .
1 . . . . . . . . . . . . . . .
. 2 . . . . . . . . . . . . . .
. . 3 . . . . . . . . . . . . .
. . . 4 . . . . . . . . . . . .
. . . . 5 . . . . . . . . . . .
. . . . . 6 . . . . . . . . . .
. . . . . . 7 . . . . . . . . .
. . . . . . . 8 . . . . . . . .
. . . . . . . . 9 . . . . . . .
. . . . . . . . . A . . . . . .
. . . . . . . . . . B . . . . .
. . . . . . . . . . . C . . . .
```
Excample of output:
```
C D 7 6 3 5 2 1 A G 9 F 4 8 E B 
F A 5 2 4 8 6 7 C E 3 B 9 1 G D 
G 3 8 1 B E 9 D 6 7 2 4 F C A 5 
4 9 B E C G A F 5 8 1 D 6 7 3 2 
1 5 6 7 A B C 2 3 4 8 9 D E F G 
8 2 9 A 7 D 4 E B F C G 1 3 5 6 
B C 3 D 8 F G 9 1 5 6 E 2 4 7 A 
E F G 4 1 3 5 6 D 2 7 A 8 9 B C 
6 G 2 3 5 A B C 4 9 F 1 7 D 8 E 
5 1 4 9 D 6 E 3 7 B G 8 A 2 C F 
A 8 F C 2 4 7 G E D 5 3 B 6 9 1 
7 E D B 9 1 F 8 2 C A 6 5 G 4 3 
3 B A 8 E C 1 4 9 6 D 5 G F 2 7 
9 4 C F 6 2 D 5 G A E 7 3 B 1 8 
D 7 E G F 9 3 A 8 1 B 2 C 5 6 4 
2 6 1 5 G 7 8 B F 3 4 C E A D 9
```
How to compile & run with bash:
```
g++ -O2 -o sudoku_solver sudoku_solver.cpp
./sudoku_solver
```
