//            
//                            
//                          

#include <iostream>
#include <fstream>
#include <cassert>
#include <windows.h>
#include "cursor.h"
using namespace std;

enum Cell {Dead=0, Live};                         //                                                                           

const char DEAD             = '.' ;               //                                                          
const char LIVE             = '*' ;               //                                                          
const int NO_OF_ROWS        = 40 ;                //                                                                      
const int NO_OF_COLUMNS     = 60 ;                //                                                                        
const int ROWS              = NO_OF_ROWS    + 2 ; //                                                                            
const int COLUMNS           = NO_OF_COLUMNS + 2 ; //                                                                               

const int MAX_FILENAME_LENGTH = 80 ;              //                                                                                   

//                                
bool enter_filename (char filename [MAX_FILENAME_LENGTH])
{
	//              
	assert(true);
	//                                                                                                

	cin.clear();
	cin.seekg(0, ios::beg);

	cout << "Please enter a filename (less than 80 chars)." << endl;

	int length = 0;
	char c;
	cin.get(c);

	while (cin)
	{
		if (length > 80)
		{
			return false;
		}

		if (c == '\n')
		{
			filename [length] = '\0';
			return true;
		}

		filename [length] = c;

		length++;
		cin.get(c);
	}
	return false;
}

bool open_file(ifstream& inputfile)
{
	//              
	assert(!inputfile.is_open());
	//               
	//                                                                                                  

	cout << "Please enter a filename." << endl;

		char c;
		cin.get(c);

		string filename = "";

		while (cin)
		{
			if (c == '\n')
			{
				break;
			}

			filename += c;

			cin.get(c);
		}

		inputfile = (ifstream) filename.c_str();

		if (inputfile.is_open())
		{
			cout << "File opened." << endl;
			return true;
		}
		else
		{
			cout << "Invalid file." << endl;
			return false;
		}
}

bool open_output_file(ofstream& outputfile)
{
	//              
	assert(!outputfile.is_open());
	//               
	//                                                                                      
	cout << "Please enter a filename." << endl;

	char c;
	cin.get(c);

	string filename = "";

	while (cin)
	{
		if (c == '\n')
		{
			break;
		}

		filename += c;

		cin.get(c);
	}

	outputfile = (ofstream) filename.c_str();

	if (outputfile.is_open())
	{
		cout << "File opened." << endl;
		return true;
	}
	else
	{
		cout << "Invalid file." << endl;
		return false;
	}
}

//                           
bool read_universe_file (ifstream& inputfile, Cell universe [ROWS][COLUMNS])
{
	//              
	assert(inputfile.is_open());
	//               
	//                                                         
	//                                                    
	//                                                                                 

	cin.clear();
	cin.seekg(0, ios::beg);

	bool b = open_file(inputfile);
	if(!b)
	{
		cin.clear();
		cin.seekg(0, ios::beg);
		return false;
	}

	for (int i = 0; i < 62; i++)
	{
		universe [0][i] = Dead;
		universe [41][i] = Dead;
	}

	for (int i = 0; i < 42; i++)
	{
		universe [i][0] = Dead;
		universe [i][61] = Dead;
	}

	char ch;
	inputfile.get(ch);

	int row = 1;
	int column = 1;

	while (inputfile)
	{
		if (ch == '\n')
		{
			row++;
			column = 0;
		}
		else if (ch == DEAD)
		{
			universe [row][column] = Dead;
		}
		else if (ch == LIVE)
		{
			universe [row][column] = Live;
		}

		column++;
		inputfile.get(ch);
	}
	return true;
}

void show_universe (Cell universe [ROWS][COLUMNS])
{
	//              
	assert (true);
	//               
	//                                                                               

	for(int i = 0; i < 42; i++)
	{
		for (int i1 = 0; i1 < 62; i1++)
		{
			Cell c = universe [i][i1];
			if (c == Live)
			{
				cout << "*";
			}
			else if (c == Dead)
			{
				cout << ".";
			}
		}
		cout << "\n";
	}
}

//                             
void next_generation (Cell now [ROWS][COLUMNS], Cell next [ROWS][COLUMNS])
{
	//              
	assert (true);
	//               
	//                                                                           
	//                                                               

	for (int i = 1; i < 41; i++)
	{
		for (int i1 = 1; i1 < 61; i1++)
		{
			int amount = 0;
			Cell c1 = now [i-1][i1-1];
			if (c1 == Live)
			{
				amount++;
			}
			Cell c2 = now [i-1][i1];
			if (c2 == Live)
			{
				amount++;
			}
			Cell c3 = now [i-1][i1+1];
			if (c3 == Live)
			{
				amount++;
			}
			Cell c4 = now [i][i1-1];
			if (c4 == Live)
			{
				amount++;
			}
			Cell c5 = now [i][i1+1];
			if (c5 == Live)
			{
				amount++;
			}
			Cell c6 = now [i+1][i1-1];
			if (c6 == Live)
			{
				amount++;
			}
			Cell c7 = now [i+1][i1];
			if (c7 == Live)
			{
				amount++;
			}
			Cell c8 = now [i+1][i1+1];
			if (c8 == Live)
			{
				amount++;
			}

			Cell c = now [i][i1];
			if (c == Live)
			{
				if (amount < 2 || amount > 3)
				{
					next[i][i1] = Dead;
				}
				else
				{
					next[i][i1] = Live;
				}
			}
			else
			{
				if (amount == 3)
				{
					next[i][i1] = Live;
				}
				else
				{
					next[i][i1] = Dead;
				}
			}
		}
	}
	for (int i = 0; i < 62; i++)
	{
		next [0][i] = Dead;
		next [41][i] = Dead;
	}

	for (int i = 0; i < 42; i++)
	{
		next [i][0] = Dead;
		next [i][61] = Dead;
	}
}

void output_generation(Cell generation [ROWS][COLUMNS])
{
	//              
	assert(true);
	//               
	//                                                                 
	//                                                                       

	cin.clear();
	cin.seekg(0, ios::beg);
	ofstream output;
	bool b = open_output_file(output);
	if(!b)
	{
		return;
	}

	for(int i = 0; i < 42; i++)
	{
		for(int i1 = 0; i1 < 62; i1++)
		{
			Cell c = generation [i][i1];
			if(c == Live)
			{
				output << LIVE;
			}
			else
			{
				output << DEAD;
			}
		}
		output << "\n";
	}
	cout << "Generation printed to output file!" << endl;
}

void copy_array(Cell source [ROWS][COLUMNS], Cell dest [ROWS][COLUMNS])
{
	//              
	assert (true);
	//               
	//                                                         

	for(int i1 = 0; i1 < 42; i1++)
	{
		for(int i = 0; i < 62; i++)
		{
			Cell c = source[i1][i];
			dest[i1][i] = c;
		}
	}
}

void show_generations(int amount, Cell universe [ROWS][COLUMNS])
{
	//              
	assert (amount >= 0);
	//               
	//                                                                           
	//                                                       

	Cell now [ROWS][COLUMNS];
	copy_array(universe, now);
	for(int i = 0; i < amount; i++)
	{
		Cell next [ROWS][COLUMNS];
		next_generation(now, next);
		copy_array(next, now);
		cls();
		show_universe(now);
		Sleep(1000);
	}
	output_generation(now);
}

void show_amount_of_generations()
{
	//              
	assert(true);
	//               
	//                                                                                          
	//                                                                                 
	//                            

	ifstream input;
	Cell cell [ROWS][COLUMNS];
	bool b = read_universe_file(input, cell);
	if(!b)
	{
		cin.clear();
		cin.seekg(0, ios::beg);
		return;
	}

	show_universe(cell);

	cin.clear();
	cin.seekg(0, ios::beg);

	cout << "Please enter the amount of generations you want to calculate." << endl;
	int amount;
	cin >> amount;
	show_generations(amount, cell);
}

int main ()
{
	//              
	assert (true);
	//               
	//                                                                             
	//                                      

	while (true)
	{
		cout << "Please enter the number of the algorithm you want to run:" << endl;
		cout << "1) Enter file name" << endl;
		cout << "2) Show universe of file" << endl;
		cout << "3) Calculate next generation" << endl;
		cout << "4) Show x number of generations (bonus)" << endl;
		cout << "5) Terminate program" << endl;

		int i;
		cin >> i;

		if(i == 1)
		{
			char filename[MAX_FILENAME_LENGTH];
			bool b = enter_filename(filename);
			cout << "Value: " << b << endl;
		}
		else if(i == 2)
		{
			ifstream input;
			Cell cell [ROWS][COLUMNS];
			bool b = read_universe_file(input, cell);
			if(b)
			{
				show_universe(cell);
			}
		}
		else if(i == 3)
		{
			ifstream input;
			Cell now [ROWS][COLUMNS];
			Cell next [ROWS][COLUMNS];
			read_universe_file(input, now);
			next_generation(now, next);
			show_universe(next);
		}
		else if(i == 4)
		{
			show_amount_of_generations();
		}
		else if(i == 5)
		{
			return 0;
		}
		else
		{
			cout << "Invalid input. Please try again." << endl;
		}
	}
}

