#include "header.h"

bool back_track(int board[][SIDE], int i, int j){
	int x;
	bool result = false;	
	
	if (board[i][j]<9){
		x = board[i][j]+1;	
	}
	
	else{
		board[i][j] = 0;
		return false;	
	}
	
	while(!result){
		board[i][j] = x;			
		result = check_board(board);
		if (result==false && x==9){		
			board[i][j] = 0;
			return false;
		}	
		else{
			x++;
		}
	
	}
	

	return true;

}



/*Read the board into 
a 9x9 bidimensional array*/
void read_file (int board[][SIDE], char *filename){
	int i = 0;
	int j = 0;
	
	ifstream infile (filename);
	
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

//This function will look at the board and
//store any prefilled values in a vector.
//So that when we come to filling out the board
//we do not replace these values by accident.
void read_const(vector <constant> &vec1, int board[][SIDE]){
	int i, j;
	constant temp;
	for (i = 0; i < SIDE ; i++){		
		for (j = 0 ; j < SIDE ; j++){
			if (board[i][j]!=0){
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

void print_board(int board[][SIDE]){
	int i, j;
	for (i = 0; i < SIDE ; i++){
		for (j = 0; j < SIDE ; j++){
			cout<<board[i][j]<<" ";
		}	
		cout<<""<<endl;
	}

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
				return false;		
			}
			//Checks Columns.
			if (board[k][i] == board[j][i] && board[k][i]!=0 && board[j][i]!=0){
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
				return false;			
			}		
		}
	}

	//Loop to check line of vectors
	//which represent a sub-grid.

	return true;
	//Return true if subgrid is valid.
}

//Function which writes the 
//completed board to a file.
void write_file(int board[][9]){
	int i, j;
	
	ofstream outfile("completed.txt");
	if (outfile.fail()){
		cout<<"Could not create file here"<<endl;
		exit(1);
	}
	
	
	for (i = 0 ; i < SIDE ; i++){
		for (j = 0 ; j < SIDE ; j++){
				outfile << board[i][j]<<" ";
			}
			//Move onto new line in file
			//when writing new row onto file.
			outfile<<""<<endl;
	}
	outfile.close();
}


