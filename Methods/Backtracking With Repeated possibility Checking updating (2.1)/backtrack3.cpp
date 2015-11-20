/*---PROGRAM DESCRIPTION---
*/

#include <iostream>
#include <fstream>
#include <vector>
#include <ctime>
#include <cstdlib>
#include <list>
using namespace std;

const int SIDE = 9;

typedef struct {
	int num;
	list <int> possible;
	list <int>::iterator iter;
}single;
//This is for one element on the board,
//it stores the board value 
//and its possibilities in the vector.

typedef struct {
	int x;
	int y;
}constant;

//Just like in backtrack 1.0, this holds
//the index values of the elements which
//cannot be changed (i.e elements that are
//already prefilled at the start of the game).

void read_file(single board[][SIDE], char *filename);
void set_max_poss(single board[][SIDE], int i, int j);
void find_possibilities(single board[][SIDE], int i, int j);
void read_const(vector <constant> &vec1, single board[][SIDE]);
bool check_board (single board[][SIDE]);
bool square_check(vector <int> &square);
bool check_elem(vector <constant> &vec1, int a, int b);
void print_board(single board[][SIDE]);
bool back_track(single board[][SIDE], int i, int j);
void print_vector(single board[][SIDE], int x, int y);
void init_board(single board[][SIDE]);
void update(single board[][SIDE], int i, int j);
void remove_square_elem(single board[][SIDE], int x, int y, int i,  int j);

int main(int argc, char **argv){
	
	char *file_name = NULL;
	if(argc == 1){
		cout<<"Please enter a text file name with the extension"<<endl;
		exit(1);
	}
	else{
		file_name = argv[1];
	}

	bool result, check = false;
	int i, j, a, b, times, timed;
	clock_t begin;
	double length;
	begin = clock();
	single board[SIDE][SIDE];
	vector <constant> const_elem;
	
	read_file(board, file_name);
	//Read file into 2 dimensional board.

	init_board(board);
	//Pre-initialise the board, this means we 
	//initialise the possibilities and make sure
	//that if the board element has only one possibility 
	//then we can put it in the square.

	read_const(const_elem, board);
	//Read into a vector the index of the
	//elements that cannot be altered.
	//These are the elements given at the beginning
	//of the game as well as the elements which we found
	//to have only one solution.	

	//Start the backtracking loop.	
	
	for (i = 0; i < SIDE ; i++){
		for (j = 0; j < SIDE ; j++){
			a = i;
			b = j;
			if(board[a][b].num==0){
				//This re-updates the possibilities.
				update(board, i ,j);
				result = false;
				while(!result){						
					result = back_track(board, a, b);
					if (!result && b==0){
							b = 8;
							a--;	
					}

					else if (!result && b!=0){
						b--;					
					}

					check = check_elem(const_elem, a, b);
					while(!check){
						if (!result && b==0){
							b = 8;
							a--;	
						}

						else if(!result && b!=0){
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

	print_board(board);
	length = (clock() - begin)/(double) CLOCKS_PER_SEC;
	cout<<"Time taken to solve the board: "<<length<<" seconds"<<endl;
	return 0;
}


bool back_track(single board[][SIDE], int i, int j){
	bool result = false;
	if (*board[i][j].iter==0){
		//It has reached the end of the possibilities.
		//And so we must reset the pointer to the 
		//beginning of the vector and returning false
		//will allow us to backtrack.
		board[i][j].num = 0;
		return false;	
	}

	while(!result){	
		board[i][j].num = *board[i][j].iter;
		//Set number in this element to the current
		//possibility that board[i][j] is pointing at.		
		result = check_board(board);	
		board[i][j].iter ++;		
		if (result==true){
			return true;		
		}
		else if(!result && *board[i][j].iter == 0){
			//If the pointer now points to zero then
			//all possibilities have been tried and they
			//have failed so return false so we can go back one
			//element later. We also reset the pointer.
			board[i][j].num = 0;
			return false;
		}
			
	}
}


void read_file(single board[][SIDE], char *filename){
	int i = 0;
	int j = 0;
	ifstream infile (filename);
	if (!infile.is_open()){
		cout<<"Could not open file"<<endl;
		exit(1);
	}
	
	bool loop_file = true;
	
	while (loop_file){
		infile >> board[i][j].num;	
			
		if (infile.fail()){
			loop_file = false;		
		}			
		j++;

		if (j==9){
			j = 0;
			i ++;		
		}
			
	}

	infile.close();

}


//Sets the maximum number of possibilities 
//to 1-9 initially for a single element.
void set_max_poss(single board[][SIDE], int i, int j){
	int count = 1;
	while(count<=9){
		board[i][j].possible.push_back(count);
		count++;			
	}		
	board[i][j].possible.push_back(0);
	//We also have to put a zero at the end
	//this list so that the pointer knows when
	//to stop.
}


//This function then eliminates
//the possibilities which are not viable.
void find_possibilities(single board[][SIDE], int i, int j){
	int count = 0;
	//Removing numbers from the vector which already
	//exist within the same row and column.		
		
	for (count = 0; count < SIDE ; count++){
		if (board[i][count].num!=0){
			board[i][j].possible.remove(board[i][count].num);
		}
		if(board[count][j].num!=0){
			board[i][j].possible.remove(board[count][j].num);
		}
	}
		
	//Removing the numbers from the vector which
	//already exist within the square itself.
	//First we must identify where in the subgrid the
	//element is then after that we can check its square
	//and remove the elements in this square.
	
	if (i%3==0){
		if (j%3==0){
			remove_square_elem(board, i, j, i, j);
		}
		else if ((j-1)%3==0){
			remove_square_elem(board, i, j-1, i, j);
		}
		else if ((j-2)%3==0){
			remove_square_elem(board, i, j-2, i, j);
		}
	}
	
	else if ((i-1)%3==0){
		if (j%3==0){
			remove_square_elem(board, i-1, j, i, j);
		}
		else if ((j-1)%3==0){
			remove_square_elem(board, i-1, j-1, i, j);
		}
		else if ((j-2)%3==0){
			remove_square_elem(board, i-1, j-2, i, j);
		}
	}

	else if ((i-2)%3==0){
		if (j%3==0){
			remove_square_elem(board, i-2, j, i, j);
		}
		else if ((j-1)%3==0){
			remove_square_elem(board, i-2, j-1, i, j);
		}
		else if ((j-2)%3==0){
			remove_square_elem(board, i-2, j-2, i, j);
		}
	
	}
}

void remove_square_elem(single board[][SIDE], int x, int y, int i,  int j){
	int lim1 = x + 3;
	int lim2 = y + 3;
	while(x < lim1){
		while (y < lim2){
			if(board[x][y].num!=0){
				board[i][j].possible.remove(board[x][y].num);
			}
			y++;
		}
		y = lim2 -3;
		//Set y back to the beginning
		//of the square and increment x.
		x++;
	}
}



//This function reads into a vector of structs the index
//values which are already pre-initialised.
void read_const(vector <constant> &vec1, single board[][SIDE]){
	int i, j;
	constant temp;
	for (i = 0; i < SIDE ; i++){		
		for (j = 0 ; j < SIDE ; j++){
			if (board[i][j].num!=0){
				temp.x = i;
				temp.y = j;			
				vec1.push_back(temp);			
			}
		}	
	}

}	

//Can check if element is allowed to be changed.
bool check_elem(vector <constant> &vec1, int a, int b){
	int i;
	for (i = 0; i < vec1.size() ; i++){
		if (vec1[i].x == a && vec1[i].y==b){
			return false;
		}
	}

	return true;
}

void print_board(single board[][SIDE]){
	int i, j;
	for (i = 0; i < SIDE ; i++){
		for (j = 0; j < SIDE ; j++){
			cout<<board[i][j].num<<" ";
		}	
		cout<<""<<endl;
	}

}



bool check_board (single board[][SIDE]){
	int i, j, k = 0;
	int temp;
	vector <int> sub_grid;
	
	//Checks Rows and Columns of Board.
	i = 0;
	while (i < SIDE){		
		for ( j = k + 1 ; j < SIDE ; j ++ ){
			//Checks Rows.
			if ( board[i][k].num == board[i][j].num && board[i][k].num!=0 && board[i][j].num!=0){				
				return false;		
			}
			//Checks Columns.
			if (board[k][i].num == board[j][i].num && board[k][i].num!=0 && board[j][i].num!=0){
				return false;				
			}		
		}
		k ++;
		if (k==8){
			i++;
			k = 0;			
		}		
	}
	
	/*This section divides the sudoku board
	into subgrids and checks each individual
	subgrid. If it detects an invalid subgrid
	then it will return false immediatly to the
	caller. */
	bool result = true;	
	i = 0;
	k = 0;
	while (i < 9 && result == true){
		for (j = k ; j < k + 3 ; j++){
		//Fills in vector with a
		//particular subgrid.
			temp = board[i][j].num;
			sub_grid.push_back(temp);		
		}	
		
		if ((i+1)%3 ==0 && (j%3==0)){
			result = square_check(sub_grid);	
			sub_grid.clear();													
			
			if (!result){
				return result;
				//If there are repeats in a particular subgrid 
				//then "false" is immediatley returned.			
			}			
				
			if (j==9){
				i = i + 1;
				k = 0;
			}		

			else {
				i = i - 2;
				k = k + 3;			
			}	
	
		}
		else {
			i++;		
		}	
	}
	return true;
	/*If it passes the tests above then
	there are no repeats in the rows,
	columns and sub-grids so we return true*/
}

	
bool square_check(vector <int> &square){
	int i, j;
	for (i = 0 ; i < SIDE ; i++){
		for (j = i + 1 ; j < SIDE ; j++){
			if (square[i]!=0 && square[j]!=0 && square[i]==square[j]){
				return false;			
			}		
		}
	}

	//Loop to check line of vectors
	//which represent a sub-grid.
	return true;
	//Return true if subgrid is valid.
}

//Initialising the possibilities and pointers.
//And also it finds squares where only one number is 
//available to fit in, we can then permamently fix 
//these numbers in their respective squares.
void init_board(single board[][SIDE]){
	int i, j, poss_num;
	for (i = 0; i < SIDE ; i++){		
		for (j = 0 ; j < SIDE ; j++){	
			if(board[i][j].num==0){			
				set_max_poss(board, i, j);
				//Set the possibilities from 1-9.
				find_possibilities(board, i, j);
				//This function then removes the values 1-9 from the
				//vector if they are not valid in the square.
				board[i][j].iter = board[i][j].possible.begin();
				if (board[i][j].possible.size() == 2){
					//This means there that there is only one solution
					//(and the zero at the end) for this element so since 
					//we know that we can place it in the square.
					board[i][j].num =  *board[i][j].iter;				
									
				}
		
			}		
		}	
	}
}
	
void update(single board[][SIDE], int i, int j){
	board[i][j].possible.clear();
	//Clear the vector of possibilities.
	
	set_max_poss(board, i, j);
	//Set the maximum number of possibibilities for
	//this element again.

	find_possibilities(board, i, j);
	//Refind the possibilities.
	
	if(board[i][j].num!=0){
		board[i][j].possible.remove(board[i][j].num);
		//Remove the element from the possibilities
		//which already exists within the board.
	}
	
	board[i][j].iter = board[i][j].possible.begin();
	//Set the pointer pointing to the first value
	//of the possibilities.

}
