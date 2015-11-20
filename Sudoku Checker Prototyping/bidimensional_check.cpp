//*****USING BI-DIMENSIONAL ARRAYS*****//

/*This program is used to check
a 3x3 sudoku board. It will check that
each column, row and square consists
of numbers 1 - 9 which appear only once.
*/ 

/*Further more this program will be used to
check if the inputted value is valid each 
and every time a value is entered.*/

#include <iostream>
#include <fstream>
#include <cstdlib>
#include <ctime>
#include <vector>
using namespace std;


const int SIDE = 9;
//Length of side.

void read_file (int board[][SIDE], char *file_name);
bool check_board (int board[][SIDE]);
bool square_check(vector <int> &square);

int main(int argc, char **argv){
	char *file_name = NULL;
	if(argc == 1){
		cout<<"Please enter board file name, including extension"<<endl;
		exit(1);
	}
	else if(argc==2){
		file_name = argv[1];
	}
	else{
		cout<<"Too many input arguments"<<endl;
		exit(1);
	}

	//Start Clock.
	clock_t begin = clock();
	double length;
	int board[SIDE][SIDE];
	
	read_file(board, file_name);
	bool result = check_board(board);
	
	clock_t end = clock();
	clock_t ticks = end - begin;
	double seconds = ticks/(double) CLOCKS_PER_SEC;

	if(result){
		cout<<"This board is valid"<<endl;
	}
	else{
		cout<<"This board is not valid"<<endl;
	}

	cout<<"Time Taken : "<<seconds<<endl;
	
	return 0;

}

/*Read the board into 
a 9x9 bidimensional array*/
void read_file (int board[][SIDE], char *file_name){
	int i = 0;
	int j = 0;	
	ifstream infile (file_name);
	if (!infile.is_open()){
		cout<<"Could not open file"<<endl;	
		exit(1);
	}

	bool loop_file = true;
	
	while (loop_file){
		infile >> board[i][j];	
			
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

bool check_board (int board[][SIDE]){
	int i, j, k = 0;
	int temp;
	vector <int> sub_grid;
	
	//Checks Rows and Columns of Board.
	i = 0;
	while (i < SIDE){		
		for ( j = k + 1 ; j < SIDE ; j ++ ){
			//Checks Rows.
			if ( board[i][k] == board[i][j] && board[i][k]!=0 && board[i][j]!=0){
				cout<<i<<","<<k<<" and "<<i<<","<<j<<endl;					
				return false;		
			}
			//Checks Columns.
			if (board[k][i] == board[j][i] && board[k][i]!=0 && board[j][i]!=0){
				cout<<k<<","<<i<<" and "<<j<<","<<i<<endl;
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
			temp = board[i][j];
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


//Function to check one subgrid
//at a time.
bool square_check(vector <int> &square){
	int i, j;
	
	for (i = 0 ; i < SIDE ; i++){
		for (j = i + 1 ; j < SIDE ; j++){
			if (square[i]!=0 && square[j]!=0 && square[i]==square[j]){
				cout<<"This Square"<<endl;	
				return false;			
			}		
		}
	}

	//Loop to check line of vectors
	//which represent a sub-grid.

	return true;
	//Return true if subgrid is valid.
}
