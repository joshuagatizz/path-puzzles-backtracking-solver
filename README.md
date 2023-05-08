# Path Puzzles Backtracking Repository

**Path puzzle** is a pencil-and-paper puzzle that was proven to be NP-complete. This repository contains code and data related to solving Path puzzles. The implemented Path puzzles solver uses a backtracking algorithm and has a asymptotic time complexity of $O(3^{mn})$, where $m \times n$ is the size of the puzzle.
For more information about the puzzle, see [https://www.enigami.fun](https://www.enigami.fun/_files/ugd/e33b96_3c76845fa9dd413a9f1606ce1c040b99.pdf) or the [original book](https://books.google.co.id/books/about/Path_Puzzles.html?id=tDhaswEACAAJ&redir_esc=y) by Roderick Kimball.

## Test Cases

The `testCases` directory contains a set of test cases in plain text that are taken from [font-pathpuzzles](https://github.com/edemaine/font-pathpuzzles) repository by Erik Demaine.  The directory contains two subdirectories `solved` and `unsolved` which contains the input files for the Path puzzles verifier and solver, respectively. 
There are 26 cases in each subdirectory where each case is of size $6 \times 6$ and corresponds to a letter in the standard English alphabets. Each unsolved case only has a single solution and each solved case is a correct solution.  Therefore, the expected solution for  `testCases/unsolved/{letter}.txt` can be found by examining  `testCases/solved/{letter}.txt`.

## Verifier

The verifier code is written in C++ and can be found in the `codes/verifier.cpp` file. It verifies the correctness of a given solution to the Path puzzle of size $m \times n$ in $O(mn)$ time by checking whether the solution satisfies the rules of the puzzle.

### Input
The input format for the verifier is as follows:
```
m n
i_a j_a
i_b j_b

cr_1 cr_2 ... cr_m
cc_1 cc_2 ... cc_n

p_{1,1} p_{1,2} ... p{1,n}
p_{2,1} p_{2,2} ... p{2,n}
...
p_{m,1} p_{m,2} ... p{m,n}
```
where:

 - `m` and `n` are integers representing the size of the puzzle.
 - `i_a` and `j_a` are integers representing the first door cell.
 - `i_b` and `j_b` are integers representing the second door cell.
 - `cr_{i}` is an integer representing the constraint number of row `i`. If row `i` does not have a constraint number, then `cr_{i} = -1`.
 - `cc_{j}` is an integer representing the constraint number of column `j`. If column `j` does not have a constraint number, then `cc_{j} = -1`.
 - `p_{i,j}` is a character representing cell $(i,j)$ of the puzzle, where the value is either `0`, `d`,`l`,`r`, or `u`. `0` represents an empty cell while `d`,`l`,`r`, and `u` correspond to $down, left, right,$ and $up$---direction of the path passing the cell. For example if the path pass through cell $(i,j)$ and then cell  $(i+1,j)$, then `p_{i,j} = d`.  Note that the second door cell $(i_b,j_b)$ is always filled with `u`.

### Output
The output format of the verifier is as follows:

 - The given input is a solution:
 ```
 valid solution!
 time taken: {running time}ms.
 ```
 - The given input is not a solution:
  ```
 invalid!
 time taken: {running time}ms.
 ```
### Example
```
3 3
1 1
3 3

1 3 1
2 1 2

d 0 0
r r d
0 0 u
```
```
valid solution!
time taken: 1ms.
 ```

## Solver

The solver code is also written in C++ and can be found in the `codes/solver.cpp` file. It uses a backtracking algorithm to find a solution to the given puzzle instance of size $m \times n$ in $O(3^{mn})$ time.

### Input
The input format for the solver is as follows:
```
m n
i_a j_a
i_b j_b

cr_1 cr_2 ... cr_m
cc_1 cc_2 ... cc_n
```
where:

 - `m` and `n` are integers representing the size of the puzzle.
 - `i_a` and `j_a` are integers representing the first door cell.
 - `i_b` and `j_b` are integers representing the second door cell.
 - `cr_{i}` is an integer representing the constraint number of row `i`. If row `i` does not have a constraint number, then `cr_{i} = -1`.
 - `cc_{j}` is an integer representing the constraint number of column `j`. If column `j` does not have a constraint number, then `cc_{j} = -1`.

### Output
The output format of the solver is as follows:

 - The given input has a solution:
 ```
solution found!

p_{1,1} p_{1,2} ... p{1,n}
p_{2,1} p_{2,2} ... p{2,n}
...
p_{m,1} p_{m,2} ... p{m,n}

time taken: {running time}ms.
 ```
 - The given input has no solution:
  ```
solution not found.
 ```

### Example
```
3 3
1 1
3 3

1 3 1
2 1 2
```
```
solution found!

d 0 0
r r d
0 0 u

time taken: 1ms.
 ```
## Usage

To use the code and data in this repository, simply clone the repository and compile `verifier.cpp` and `solver.cpp` files, run the executable and give and type the input manually or use a file input such as the test cases.

## Experiment Results

The `exptData/runtime.xlsx` file contains the results of experiments conducted on the solver against the test cases. The runtime and average of three tests are taken for each case and the results are presented in the form of  a table.

