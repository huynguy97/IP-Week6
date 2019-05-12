//                                                       
#include <iostream>
#include <fstream>
#include <cassert>
using namespace std;

enum Cell {Dead=0, Live};                         //                                                                           

const char DEAD             = '.' ;               //                                                          
const char LIVE             = '*' ;               //                                                          
const int NO_OF_ROWS        = 40 ;                //                                                                      
const int NO_OF_COLUMNS     = 60 ;                //                                                                        
const int ROWS              = NO_OF_ROWS    + 2 ; //                                                                            
const int COLUMNS           = NO_OF_COLUMNS + 2 ; //                                                                               
const int DiffX[8]			={1,1,1,0,-1,-1,-1,0};//                                                          
const int DiffY[8]			={-1,0,1,1,1,0,-1,-1};

const int MAX_FILENAME_LENGTH = 80 ;              //                                                                                   

//                                
bool enter_filename (char filename [MAX_FILENAME_LENGTH])
{
    //            
    assert(true);
    //             
    //                                  
	int index = -1;
    do{
    	index++; //                                      
    	cin.get(filename[index]);
    	if (filename[index] == '\n')
    		filename[index] = '\0';
    }while(cin and filename[index] != '\0' and index < MAX_FILENAME_LENGTH);
    if (!cin or index >= MAX_FILENAME_LENGTH){
    	return false;
    }
    return true;
}

//                           

bool open_input_file(char filename[MAX_FILENAME_LENGTH], ifstream& in){
	//              
	assert(true);
	//                                              
	in.open(filename);
	if(in.is_open())
		return true;
	else
		return false;
}

bool read_universe_file (ifstream& inputfile, Cell universe [ROWS][COLUMNS])
{
//              
	assert(inputfile.is_open());
	//                                                                          
	for(int r=1; r<=NO_OF_ROWS and inputfile; r++){
		for(int c=1; c<NO_OF_COLUMNS and inputfile; c++){
			char cell;
			inputfile.get(cell);
			if(cell==LIVE)
				universe[r][c] = Live;
			else
				universe[r][c] = Dead;
		}
		char c = '\0';
		//                                                
		while(inputfile and c!='\n'){
			inputfile.get(c);
		}
	}
	if(!inputfile)
		return false;
	return true;
}

void show_universe (Cell universe [ROWS][COLUMNS])
{
	//              
	assert(true);
	//                                                       
	for(int r=1; r<=NO_OF_ROWS; r++){
		for(int c=1; c<=NO_OF_COLUMNS; c++){
			if(universe[r][c]==Live)
				cout << LIVE;
			else
				cout << DEAD;
		}
		cout << endl;
	}
}

//                             
void next_generation (Cell now [ROWS][COLUMNS], Cell next [ROWS][COLUMNS])
{
	//            
	assert(true);
	//             
	//                                                              
	//                                        
	for (int i = 1;i<ROWS-1;i++){
		for (int j = 1;j<COLUMNS-1;j++){
			int numNeighbor = 0;
			//                                
			//                                                                  
			for (int dir = 0;dir<8;dir++){
				numNeighbor += now[i+DiffY[dir]][j+DiffX[dir]];
			}
			next[i][j] = now[i][j];
			if (now[i][j] == Dead and numNeighbor == 3){
				next[i][j] = Live;
			}
			if (now[i][j] == Live and (numNeighbor < 2 or numNeighbor > 3)){
				next[i][j] = Dead;
			}
		}
	}
    return;
}

int main (){
	char filename [MAX_FILENAME_LENGTH];
	enter_filename(filename);
	ifstream in;
	if(!open_input_file(filename, in)){
		cout << "error opening input file, are you sure it exists?" << endl;
		return 0;
	}
	Cell universe[ROWS][COLUMNS];
	for(int r=0; r<ROWS; r++){
		for(int c=0; c<COLUMNS; c++){
			universe[r][c] = Dead;
		}
	}
	if(!read_universe_file(in, universe)){
		cout << "ERROR READING config file" << endl;
		return 0;
	}
	Cell next[ROWS][COLUMNS];
	next_generation(universe, next);
	show_universe(next);
}

