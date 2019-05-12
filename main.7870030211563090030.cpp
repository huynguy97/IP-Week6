#include <cassert>
#include <fstream> //             
#include <iostream>

using namespace std;

/*                                                                   
                
                                 
                              

                                                                   */

enum Cell {
  Dead = 0,
  Live
}; //                                                                           

//                                                          
const char DEAD = '.';
const char LIVE =
    '*'; //                                                          
const int NO_OF_ROWS =
    40; //                                                                      
const int NO_OF_COLUMNS = 60; //                                              
                              //                          
const int ROWS = NO_OF_ROWS + 2; //                                        
                                 //                                    
const int COLUMNS =
    NO_OF_COLUMNS + 2; //                                                     
                       //                          

int generation_count = 0;

//                                                            
//                       
const int MAX_FILENAME_LENGTH = 80;

//                                
bool enter_filename(char filename[MAX_FILENAME_LENGTH]) {
  //                                                
  assert(MAX_FILENAME_LENGTH >= 0);
  //                                                                          
  //                         

  cout << "Enter a name filename (including .txt, up to " << MAX_FILENAME_LENGTH
       << " characters)" << endl; //               
  //                                                    
  int nr_of_elements = 0;
  do {
    //                                                     
    if (nr_of_elements != 0) {
      nr_of_elements = 0;
      cout << "Enter a smaller name" << endl;
    }

    //            
    char c = ' ';

    //                                                      
    //                                      
    while (c != '\n') {
      cin.get(c);
      if (nr_of_elements < MAX_FILENAME_LENGTH) {
        filename[nr_of_elements] = c; //                   
        nr_of_elements++;
      }
    }
    filename[nr_of_elements - 1] = '\0'; //                                   
  } while (nr_of_elements >= MAX_FILENAME_LENGTH);
  return true;
}

//                           
bool read_universe_file(ifstream &inputfile, Cell universe[ROWS][COLUMNS]) {
  //                                                                            
  //                                                                      
  //                                                                 

  if (!inputfile.is_open()) {
    return false;
  }
  for (int y = 0; y < ROWS; y++) {
    for (int x = 0; x < COLUMNS; x++) {
      //                                   
      universe[y][x] = Dead;
    }
  }
  int x = 1;
  int y = 1;
  while (inputfile) {
    char c;
    inputfile.get(c);
    switch (c) {
    case LIVE:
      universe[y][x] = Live;
      break;
    case DEAD:
      universe[y][x] = Dead;
      break;
    case '\n':
      //                    
      x = 0;
      y++;
      break;
    default:
      break;
    }
    x++;
  }
  return true;
}

void show_universe(Cell universe[ROWS][COLUMNS]) {
  //               
  assert(ROWS >= 0 && COLUMNS >= 0);
  //                
  //                                                                      
  //                                                                          

  cout << "Showing universe at generation " << generation_count << endl;

  for (int y = 0; y < ROWS; y++) {
    for (int x = 0; x < COLUMNS; x++) {
      if (universe[y][x] == Live) {
        cout << LIVE;
      } else {
        cout << DEAD;
      }
    }
    cout << endl;
  }
}

//                             
void next_generation(Cell now[ROWS][COLUMNS], Cell next[ROWS][COLUMNS]) {
  //                
  assert(ROWS >= 0 && COLUMNS >= 0 && generation_count >= 0);
  //                 
  //                                          

  //                                
  generation_count++;

  //                                       
  for (int y = 1; y < ROWS - 1; y++) {
    for (int x = 1; x < COLUMNS - 1; x++) {

      //                                                
      int counter = 0;

      //                                                           
      for (int a = y - 1; a <= y + 1; a++) {
        for (int b = x - 1; b <= x + 1; b++) {
          if (now[a][b] == Live && !(a == y && b == x)) {
            counter++;
          }
        }
      }

      //                                                                     
      //            
      switch (counter) {
      case 0:
      case 1:
        next[y][x] = Dead;
        break;
      case 2:
        if (now[y][x] == Live) {
          next[y][x] = Live;
        } else {
          next[y][x] = Dead;
        }
        break;
      case 3:
        next[y][x] = Live;
        break;
      case 4:
      case 5:
      case 6:
      case 7:
      case 8:
        next[y][x] = Dead;
        break;
      }
    }
  }
}

int main() {
  char filename[MAX_FILENAME_LENGTH];
  enter_filename(filename);
  cout << filename << endl;

  //                                                      
  ifstream input_file;
  input_file.open(filename);

  Cell universe[ROWS][COLUMNS];
  read_universe_file(input_file, universe);
  cout << (universe[NO_OF_ROWS - 2][4] == Live) << endl;
  show_universe(universe);
  Cell next_universe[ROWS][COLUMNS];
  next_generation(universe, next_universe);
  show_universe(next_universe);
  while (true) {
  }
}

