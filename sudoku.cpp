#include <string>
#include <iostream>
#include <fstream>
using namespace std;

#define WIDTH 9
#define HEIGHT 9

/* 9x9 grid of sudoku input */
char grid[HEIGHT][WIDTH];

/* Creates sudoku grid */
void createGrid(char** argv);
/* Error Checks if duplicate value in either same row or column, depending on argument values */
void sameLineValidation(int row, int col, int y, int x);
/* Error Checks sub grid to contain one of each value ranging from [1,9]  */
void subGridValidation(int row, int col);

int main(int argc, char** argv)
{
    createGrid(&argv[1]);
    return 0;
}

void createGrid(char** argv)
{
    int rowCount = 0;
    int colCount = 0;
    string line;
    ifstream myfile(argv[1]);
    if(myfile.is_open())
    {
        while(getline(myfile,line))
        {
            for(int i=0; i<line.size();++i)
            {
                /* input known that commas separate correct values, so we disregard comma input */
                if(line[i] != ',')
                {
                    grid[rowCount][colCount] = line[i];
                    colCount++;
                }
            }
            colCount = 0;
            rowCount++;
            myfile.close();
        }
    }
}

void sameLineValidation(int row, int col, int y, int x)
{
    char c;
    int one=0,
        two=0,
        three=0,
        four=0,
        five=0,
        six=0,
        seven=0,
        eight=0,
        nine=0;
    for(int i=0; i<HEIGHT;++i)
    {
        c = grid[y][x];
        if(row == 1)
            x++;
        else if(col == 1)
            y++;
        if(c == '1')
            one++;
        else if(c == '2')
            two++;
        else if(c == '3')
            three++;
        else if(c == '4')
            four++;
        else if(c == '5')
            five++;
        else if(c == '6')
            six++;
        else if(c == '7')
            seven++;
        else if(c == '8')
            eight++;
        else if(c == '9')
            nine++;
    }
    int errorCounter = 0;
    string errorMessage = "";
    if(one>=2)
    {
        errorMessage += one + " one's, ";
        errorCounter++;
    }
    if(two>=2)
    {
        errorMessage += two + " two's, ";
        errorCounter++;
    }
    if(three>=2)
    {
        errorMessage += three + " three's, ";
        errorCounter++;
    }
    if(four>=2)
    {
        errorMessage += four + " four's, ";
        errorCounter++;
    }
    if(five>=2)
    {
        errorMessage += five + " five's, ";
        errorCounter++;
    }
    if(six>=2)
    {
        errorMessage += six + " six's, ";
        errorCounter++;
    }
    if(seven>=2)
    {
        errorMessage += seven + " seven's, ";
        errorCounter++;
    }
    if(eight>=2)
    {
        errorMessage += eight + " eight's, ";
        errorCounter++;
    }
    if(nine>=2)
    {
        errorMessage += nine + " nine's, ";
        errorCounter++;
    }
    if(errorCounter > 0)
    {
        if(row == 1)
            errorMessage += "on row " + y;
        else if(col == 1)
            errorMessage += "on column " + x;
    }
    //WARNING: UNFINISHED FUNCTION, WAITING ON CREATION AND BEHAVIOR OF THREADS
 }

void subGridValidation(int row, int col)
{
    int errorCounter = 0;
    string errorMessage = "";
    int one=0,
        two=0,
        three=0,
        four=0,
        five=0,
        six=0,
        seven=0,
        eight=0,
        nine=0;
    char c;
    int counter=0;
    for(int i=0; i<HEIGHT;++i)
    {
        c = grid[row][col];
        if(counter = 2)
        {
            col -= 3;
            row++;
            counter = -1;
        }
        col++;
        counter++;
        if(c == '1')
            one++;
        else if(c == '2')
            two++;
        else if(c == '3')
            three++;
        else if(c == '4')
            four++;
        else if(c == '5')
            five++;
        else if(c == '6')
            six++;
        else if(c == '7')
            seven++;
        else if(c == '8')
            eight++;
        else if(c == '9')
            nine++;
    }
    if(one>1)
    {
        errorCounter++;
        errorMessage += one + " one's, ";
    }
    if(two>1)
    {
        errorCounter++;
        errorMessage += two + " two's, ";
    }
    if(three>1)
    {
         errorCounter++;
         errorMessage += three + " three's, ";
    }
    if(four>1)
    {
        errorCounter++;
        errorMessage += four + " four's, ";

    }
    if(five>1)
    {
        errorCounter++;
        errorMessage += five + " five's, ";
    }
    if(six>1)
    {
        errorCounter++;
        errorMessage += six + " six's, ";
    }
    if(seven>1)
    {
        errorCounter++;
        errorMessage += seven + " seven's, ";
    }
    if(eight>1)
    {
        errorCounter++;
        errorMessage += eight + " eight's, ";
    }
    if(nine>1)
    {
        errorCounter++;
        errorMessage += nine + " nine's, ";
    }
    if(errorCounter > 0)
    {
        string first = "on sub grid row[" + (row + 1);
        string second = "," + (row + 4);
        string third = first + second;
        string fourth = " and column[" + (col + 1);
        string fifth = "," + (col + 4);
        string sixth = "].";
        string sev = third + fourth;
        string ayy = sev + fifth;
        string last = ayy + sixth;
    }
}