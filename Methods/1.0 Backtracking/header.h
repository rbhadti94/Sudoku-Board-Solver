#ifndef HEADER_H
#define HEADER_H

#include <fstream>
#include <iostream>
#include <vector>
#include <cstdlib>
using namespace std;
//The relevant headers required 
//for the program to operate.

typedef struct {
	int x;
	int y;
}constant;
//The structure which contains the values
//of the elements that cannot be changed.

const int SIDE = 9;

void read_file (int board[][SIDE], char *filename);
bool check_board (int board[][SIDE]);
bool square_check(vector <int> &square);
void read_const(vector <constant> &vec1, int board[][SIDE]);
bool check_elem(vector <constant> &vec1, int a, int b);
void print_board(int board[][SIDE]);
bool back_track(int board[][SIDE], int i, int j);
void write_file(int board[][SIDE]);

#endif

