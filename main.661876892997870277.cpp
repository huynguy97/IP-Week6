//                                    
//                                    

#include <iostream>
#include <fstream>
#include <cassert>
#include <string>
using namespace std;

enum Cell { Dead = 0, Live };                         //                                                                           

const char DEAD = '.';               //                                                          
const char LIVE = '*';               //                                                          
const int NO_OF_ROWS = 40;                //                                                                      
const int NO_OF_COLUMNS = 60;                //                                                                        
const int ROWS = NO_OF_ROWS + 2; //                                                                            
const int COLUMNS = NO_OF_COLUMNS + 2; //                                                                               

const int MAX_FILENAME_LENGTH = 80;              //                                                                                   

												 //                                
bool enter_filename(char filename[MAX_FILENAME_LENGTH])
{
	//             
	assert(true);
	//                                                                                                                                              

	cout << "Enter a file name with max " << MAX_FILENAME_LENGTH - 1 << " characters (include .txt)" << endl;
	char c = ' ';

	int i = 0;
	while (c != '\n') {
		if (i >= MAX_FILENAME_LENGTH) return false;
		cin.get(c);
		char tempc = c;
		if (c == '\n') tempc = '\0';
		filename[i] = tempc;
		i++;
	}
	return true;
}

void addborder(Cell universe[ROWS][COLUMNS]) {
	//             
	assert(true);
	//                                                                                       
	// 	                   

	for (int i = 0; i < COLUMNS; i++) {
		universe[0][i] = Dead;
	}
	// 	                                                                      
	for (int j = 1; j <= ROWS - 2; j++) {
		universe[j][0] = Dead;
		universe[j][COLUMNS - 1] = Dead;
	}
	// 	                  
	for (int i = 0; i < COLUMNS; i++) {
		universe[ROWS - 1][i] = Dead;
	}
}
//                           
bool read_universe_file(ifstream& inputfile, Cell universe[ROWS][COLUMNS])
{
	//                                           
	assert(inputfile.is_open());
	//                                                                                 

	char c = ' ';
	int Row = 1;
	int Column = 1;
	Cell state;
	while (inputfile) {
		inputfile.get(c);
		if (c == '*') state = Live;
		else if (c == '.') state = Dead;
		else if (c == '\n') {
			Column = 1;
			Row++;
			inputfile.get(c);
			if (c == '*') state = Live;
			else if (c == '.') state = Dead;
		}
		universe[Row][Column] = state;
		Column++;
	}
	addborder(universe);
	return true;
}

void show_universe(Cell universe[ROWS][COLUMNS])
{
	//            
	assert(true);
	//                                                         

	for (int i = 0; i < ROWS; i++) {
		for (int j = 0; j < COLUMNS; j++) {
			if (universe[i][j] == Live) cout << "*";
			else  cout << ".";
		}
		cout << '\n';
	}
}

/*
                                                                                        
                                                                                
                                                                               
                                                                                            
                                
*/

int count_cell_neighbours(Cell universe[ROWS][COLUMNS], int row, int column) {

	//                                             
	assert(row < ROWS && column < COLUMNS  && row >= 0 && column >= 0);
	//                                                          

	int neighbours = 0;
	if (universe[row + 1][column] == Live) neighbours++;
	if (universe[row - 1][column] == Live) neighbours++;
	if (universe[row][column + 1] == Live) neighbours++;
	if (universe[row][column - 1] == Live) neighbours++;
	if (universe[row + 1][column + 1] == Live) neighbours++;
	if (universe[row + 1][column - 1] == Live) neighbours++;
	if (universe[row - 1][column + 1] == Live) neighbours++;
	if (universe[row - 1][column - 1] == Live) neighbours++;
	return neighbours;
}

Cell dead_alive(int neighbours,Cell state) {
	//                                                                      
	assert(neighbours <= 8 && neighbours >= 0);
	//             
	//                                                                    
	if (state == Live) {
		if (neighbours < 2 || neighbours > 3) return Dead;
		else if (neighbours == 2 || neighbours == 3) return Live;
	}
	else
	{
		if (neighbours == 3) return Live;
		else return Dead;
	}
}

//                             
void next_generation(Cell now[ROWS][COLUMNS], Cell next[ROWS][COLUMNS])
{
	//           
	assert(true);
	//                                                                              

	for (int i = 1; i < ROWS - 1; i++) {
		for (int j = 1; j < COLUMNS - 1; j++) {
			int neighbours = count_cell_neighbours(now, i, j);
			next[i][j] = dead_alive(neighbours, now[i][j]);
		}
	}
	addborder(next);
}

int main()
{
	char filename[MAX_FILENAME_LENGTH];

	if (enter_filename(filename))
	{
		cout << "Succesfully read the filename" << endl;

		Cell Cellboard[ROWS][COLUMNS];
		Cell NextCellBoard[ROWS][COLUMNS];

		ifstream reader(filename);
		read_universe_file(reader, Cellboard);

		show_universe(Cellboard);
		cout << "Next gen: " << endl;
		next_generation(Cellboard, NextCellBoard);
		show_universe(NextCellBoard);
	}
	else cout << "The filename was too long" << endl;

	return 0;
}
