#include <iostream>
#include <fstream>
#include <cassert>
using namespace std;
//                                           

enum Cell {Dead=0, Live};                         //                                                                           

const char DEAD             = '.' ;               //                                                          
const char LIVE             = '*' ;               //                                                          
const int NO_OF_ROWS        = 40 ;                //                                                                      
const int NO_OF_COLUMNS     = 60 ;                //                                                                        
const int ROWS              = NO_OF_ROWS    + 2 ; //                                                                            
const int COLUMNS           = NO_OF_COLUMNS + 2 ; //                                                                               
const int MAX_FILENAME_LENGTH = 80 ;              //                                                                                   

//                                
//                                                                          
// 

    //                               

// 
bool open_file(ifstream& inputfile)
{
    assert(true);//              
    string filename;
    cout<<"please enter filename \n";
    cin>>filename;
    if(filename.length()>80)
        return false;
    inputfile.open(filename.c_str()); //                                                                                     
    if (!inputfile)
    {
        return false;
    }
    else return true; //                      
}

//                           
void read_universe_file (ifstream& inputfile, Cell universe [ROWS][COLUMNS])
{
    //               
    assert(inputfile.is_open());//
    //               
    string line;                   //                            
    int rownumber=1;              //                                        
    while (getline(inputfile,line)) //                                             
    {
        for (int column=1; (column)<COLUMNS ; column++) //                                                                                                                                                       
        {
            if (line[column-1]=='*') //                                                                                                            
                universe[rownumber][column]=(Cell) Live;
            else
                universe[rownumber][column]=(Cell) Dead;
        }
        rownumber++;
    }

    //                                                                                                                                                                             
    inputfile.clear();
    inputfile.close();

}

/*                                                  
 
                                                      
                                                                             
                                                                                                                    
                                      
     
                                                     
                                          
                   
     
 */ //                              
void show_universe (Cell universe [ROWS][COLUMNS])
{
    //                                                
    assert(true);//                                                          
    //                                                                                                              
    for (int srow=0; srow<ROWS;srow++)
    {
        for (int scolumn=0;scolumn<COLUMNS;scolumn++)
            if (universe[srow][scolumn]==(Cell) Live)
                cout<<LIVE;
            else
                cout<<DEAD;
        cout<<"\n";
    }
}

//                             
void next_generation (Cell now [ROWS][COLUMNS], Cell next [ROWS][COLUMNS])
{
    //               
    assert(true); //                                                          
    int sum=0;
    for (int row=1;(row+1)<ROWS;row++) //                         
    {
        for (int column=1;(column+1)<COLUMNS;column++)
        {
            for(int brow=row-1;brow<=row+1;brow++) //                            
            {
                for(int bcolumn=column-1;bcolumn<=column+1;bcolumn++) //                                      
                {
                    sum+=now[brow][bcolumn];  //                               
                }
            }
            sum=sum-now[row][column]; //                                                           
            if (now[row][column]==(Cell) Live) //                     
            {
                if(!(sum==2||sum==3))  //                                                                                                                                                      
                    next[row][column]=(Cell) Dead;
                else                 //                              
                    next[row][column]=(Cell) Live;
            }
            else
            {
                if(sum==3) //         
                    next[row][column]=(Cell) Live;
            }

            sum=0;//                                        
        }
    }
    //                                                                                                               
}

int main ()
{
    ifstream inputfile;
    string  filename;
    Cell universe[ROWS][COLUMNS];
    Cell next_universe[ROWS][COLUMNS];
        for (int rows=0; rows<ROWS ; rows++) //                         
    {
        for (int columns=0; columns<COLUMNS;columns++)
        {
            universe[rows][columns]=Dead;
        }
    }
    if (!open_file(inputfile))
    {
        cout<<"wrong filename or too long of a filename.";
         return 0;
    }

    read_universe_file (inputfile, universe);
    show_universe(universe);
    next_generation(universe,next_universe);
    cout<<"now to the next universe! \n";
    show_universe(next_universe);
    return 1;
}

