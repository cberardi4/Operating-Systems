#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include <string>
#include <fstream>

using namespace std;

void *checkRow(void* file);
void *checkColumn(void* file);
void *checkSubmatrix(void* file);
int * readRow(ifstream &f);

// values that save where error was for row, column, and subgrid
// doubleNumber = what will be replaced
// neverAppearedNumber = what will replace doubleNumber
int doubleNumberRow = 0;
int neverAppearedNumberRow = 0;
int doubleNumberColumn = 0;
int neverAppearedNumberColumn = 0;
int doubleNumberSubgrid = 0;
int neverAppearedNumberSubgrid = 0;


int main()
{
    // read in files

    string fileName;

    // ask user what test file they want to run
    cout << "Enter test file name: ";
    cin >> fileName;

    pthread_t row_thread, column_thread, submatrix_thread;
    char *id_row = "Row";
    char *id_column = "Column";
    char *id_submatrix = "Submatrix";


    // create Marco and Polo threads
    // last parameter from documentation: "It must be passed by reference as a pointer cast of type void"
    pthread_create( &row_thread, NULL, *checkRow, &fileName);
    //pthread_create( &column_thread, NULL, *checkColumn, (void *)id_polo);
    //pthread_create( &submatrix_thread, NULL, *checkSubmatrix, (void *)id_polo);

    // join threads
    pthread_join( row_thread, NULL);
    //pthread_join( column_thread, NULL);
    //pthread_join( submatrix_thread, NULL);

    return 0;

}

void* checkRow(void *name)
{
    ifstream testFile;
    //char *fileName = (char *) name;
    string fileName = *static_cast<string*>(name);
    int numIndex;
    bool checkForMissingNumber = false;

    int *characters [9];
    bool numInGrid [9];

    string line;

    // open file
    testFile.open(fileName);

    // make sure that file is valid
    // if it isn't program ends
    if(testFile.fail())
    {
      cout << "Error: File doesn't exist." << endl;
      return 0;
    }

    // loop through every line of a file
    for(int row = 1; row < 11; ++row)
    {
        *characters = readRow (testFile);

        // first need to initalize two arrays
        // initialize boolean array to false and fill one
        // row of file into characters array
        for (int column = 1; column < 11; ++column)
        {
            // get number from row and input into array
            characters[column] = (int*)(testFile.get());
            cout <<"index [" << row << "][" << column << "] = "  <<characters[column] << endl;

            // skipping comma
            testFile.get();

            // initializing boolean array to false for every value in row
            // once a number appears in the row, index will be true
            numInGrid[column] = false;
        }
        // find where error is within one row
        // looping through one row
        for (int j = 0; j < 9; ++j)
        {
            cout << "in second for loop" << endl;
            // if a number from 1-9 is within the row, set that index
            // value in the numInGrid array to true
            numIndex = characters[j];

            // number has not already been accounted for
            if (numInGrid[numIndex] == false)
            {
                cout << "in if statement" << endl;
                numInGrid[numIndex] = true;
            }
            // number is repeated because already been accounted for
            // save that number in an int so that it knows where to fix problem
            else
            {
              doubleNumberRow = numIndex;
            }

            // don't need to loop through array if there were no issues
            // so that's why you check if you need to find where number didn't appear
            if (checkForMissingNumber)
            {
              for (int k = 0; k < 9; ++k)
              {
                if (numInGrid[k] == false)
                {
                  neverAppearedNumberRow = k;
                  checkForMissingNumber = false;
                  cout << "Missing number " << neverAppearedNumberRow << endl;
                } // end if
              } // end for
            } // end if

          } // end for
      } // end for


  } // end function

  int * readRow (ifstream &f)
  {

      char charsFinal[9];
      getline(f, line);
      char charsTemp[line.size() + 1];
      cout << line << endl;
      strncpy(charsTemp, line.c_str(), sizeof(charsTemp));
      length = sizeof(charsTemp) / sizeof(*charsTemp);
      cout << length << endl;
      for (int k = 0; k < length - 2; ++k)
      {
        cout << "put in final array: "<< charsTemp[k] << endl;
        charsFinal[k] = charsTemp[k++];
        cout << k << endl;

        if (k == 18)
        {
            cout << "breaking" << endl;
        }
       }
        return charsFinal;

  }
