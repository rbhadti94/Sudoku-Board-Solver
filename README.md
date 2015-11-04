# The Sudoku Board Solver

Sudoku is a Japanese game that requires the user to fill out a 9 x 9 numerical grid by using only numbers 1 - 9. The conditions are that:
* There are 9 3 x 3 sub-grids, and within these all numbers must be unique.
* Every row must contain the numbers 1 - 9 and every column must also contain the numbers 1 - 9.

This repository contains different versions of a Sudoku puzzle solver designed to work for 9 x 9 grids. Each of these methods uses a (slightly) different algorithmic implementation to solve the board. By all means these are NOT the only ways to do this but this works! Within this repo, there is a board checker used to check the board for validity and also 3 different solver methods that can be also be used.

## Board Checker
Regardless of the algorithm that is used, the board will have to be checked. Either routinely throughout the algorithm or at the end of the program. This checker is located in ``` /Sudoku Checker ```.

Compile the file by carrying out the command below. This compiles the checker program and it is saved as ``` checker.out ``` in the same directory.
```
g++ bidimensional_check.cpp -o checker  
```
Run it as:
```
./checker board.txt
```
Where ``` board``` is the board file saved in a ```.txt``` format in the same folder. An example board is contained called ```board_incorrect.txt```. Try running this! You will get the message:
```
This board is not valid.
Time Taken : XXXXX
```

If you observe the text file you'll notice that the rules of Sudoku are not followed hence this message is displayed. Find a board that is correct and input it into a text file. What result do you get?

## Solver Methods

The checker designed above is now used in conjunction with a board solver! There are 3 main methods that are used here all of which have been tested to work!

###  V 1.0 : Back-Tracking
This version is essentially purely brute force. It goes as follows:

1. Loads in an unsolved board where blank spaces are represented by a ```'0'```.

2. Fills a blank space with a ```'1'```.  

3. The board is then checked.

4. If valid -> Go to next blank space and do the same.  

5. If invalid -> Go back to the last filled element and change the number in the box from ```'1'``` to ```'2'``` (i.e. ```n``` to ```n+1```). If ```n == 9``` then set ```n+1 = 1```.

6. This is continued till the end of the board.  

###  V 2.0 : Improved Back-Tracking

### V 2.1 : Humanised Back-Tracking

### V 3.0 : Stochastic Search & Optimisation
