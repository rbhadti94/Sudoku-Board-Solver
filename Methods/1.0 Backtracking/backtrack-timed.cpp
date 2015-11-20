/*---PROGRAM DESCRIPTION---
This particular way of solving the sudoku
board is called the backtracking method. The 
process for this is as follows:
1-The program puts a '1' in an empty square.
2-Checks if it violates the condition.
3-And if it does it inputs the next number possible (in this case '2').
4-The program than cycles steps 2 and 3 until a suitable number is found.
5-If all numbers from 1-9 cannot be placed in that square
 then it moves back to the previous square. (This is backtracking).
6-Then steps 2 and 3 are repeated until it finds another number that is suitable.
7-This carries on until the program reaches the end of the board, by this time
  theoretically we should have found a solution to the board.
*/



#include "header.h"
#include <ctime>
//For timing purposes.

int main(){
	clock_t begin;
	double length;
	begin = clock();
	
	bool result, check = false;
	int i, j, a, b;
	int board[SIDE][SIDE];
	//The board is a 9x9
	//bidimensial array.	
	
	vector <constant> const_elem;
	//Vector contains elements that can 
	//not be changed in the sudoku board.
	
	read_file(board);

	read_const(const_elem, board);
	//Read into a vector the pre-filled
	//elements on the board so they don't
	//get accidently replaced during the
	//program.
	
	
	
	for (i = 0 ; i < SIDE;  i++){
		for (j = 0; j < SIDE ; j++){
			a = i;	
			b = j;
			result = false;
			if(board[a][b]==0){
				while(!result){
					result = back_track(board, a, b);			
					if (result==false && b==0){
						b = 8;
						a--;	
					}

					else if (result==false && b!=0){
						b--;					
					}
				
					check = check_elem(const_elem, a, b);
					while(check==false){
						if (result==false && b==0){
							b = 8;
							a--;	
						}

						else if(result==false && b!=0){
							b--;					
						}
						check = check_elem(const_elem, a, b);						
					}
								
				}		
				i = a;
				j = b;
			}
		}	
	}
	
	
	length = (clock() - begin)/(double) CLOCKS_PER_SEC;
	//Stop timer and check the time taken.
	print_board(board);
	write_file(board);
	//Writing the file to the board.
	
	cout<<"Time taken to solve the board: "<<length<<endl;
	
	
	return 0;
}

