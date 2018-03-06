#include <stdio.h>
#include <string.h>
#include <iostream>
#include <fstream>
#include <pthread.h>
#include <cstdlib>
using namespace std;

#define WIDTH 9
#define HEIGHT 9

struct thread_data
{
    int row;
    int col;
    bool row_on;
    bool col_on;
};

/* 9x9 grid of sudoku input */
char grid[HEIGHT][WIDTH];
/* Creates sudoku grid */
void create_grid(char* argv);
/* Error Checks if duplicate value in either same row or column, depending on argument values */
void *same_line_validation(void *arguments);
/* Error Checks sub grid to contain one of each value ranging from [1,9]  */
void *sub_grid_validation(void *arguments);

string err_msg = "";

int main(int argc, char* argv[])
{
    create_grid(argv[1]);
    pthread_t threads[HEIGHT];
    struct thread_data args[HEIGHT];
    int rc;
	int i;
    int j;
    for(i=0;i<9;++i)
    {
        for(j=0;j<9;++j)
        {
            cout << grid[i][j];
        }
        cout << endl;
    }
	for(i=0; i<HEIGHT; ++i)
    {
        args[i].row = i;
        args[i].col = 0;
		args[i].row_on = true;
		args[i].col_on = false;
        rc = pthread_create(&threads[i], NULL, same_line_validation, (void *) &args); 
        if(rc)
        {
            cout << "Uh oh " << rc << endl;
            exit(-1);
        }
    }
	pthread_join(threads[8], NULL);
	for(i=0; i<HEIGHT; ++i)
    {
        args[i].row = 0;
        args[i].col = i;
		args[i].row_on = false;
		args[i].col_on = true;
        rc = pthread_create(&threads[0], NULL, same_line_validation, (void *) &args); 
        if(rc)
        {
            cout << "RIP " << rc << endl;
            exit(-1);
        }
	}
	pthread_join(threads[8], NULL);
	int cnt0 = 0;
	int cnt1 = 0;
	for(i=0; i<HEIGHT; ++i)
	{
		args[i].row = (3*cnt0);
		args[i].col = (3*cnt1);
		rc = pthread_create(&threads[i], NULL, sub_grid_validation, (void *) &args[i]);
		if(rc)
		{
			cout << "Your machine appears to be alergic to multi threads :( " << rc << endl;
			exit(-1);
		}
		cnt1++;
		if(args[i].col == 6)
		{
			cnt1 = 0;
			cnt0++;
		}
	}
	pthread_join(threads[8], NULL);
    return 0;
}

void create_grid(char *argv)
{
    ifstream myfile;
    myfile.open(argv);
    string line;
    int row_c = 0;
    int col_c = 0;
    if(myfile.is_open())
    {
        while(getline(myfile,line))
        {
            for(int i=0; i<line.size(); ++i)
            {
                if(line[i] != ',')
                {
                    grid[row_c][col_c] = line[i];
                    col_c++;
                }
            }
            row_c++;
            col_c = 0;
        }
    }
}

void *same_line_validation(void *arguments)
{
    struct thread_data *args;
    args = (struct thread_data *) arguments;
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
        c = grid[args->row][args->col];
        if(args->row_on)
            args->col++;
        else if(args->col_on)
            args->row++;
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
    int error_counter = 0;
    string error_message = "";
    if(one>=2)
    {
        error_message += one + " one's, ";
        error_counter++;
    }
    if(two>=2)
    {
        error_message += two + " two's, ";
        error_counter++;
    }
    if(three>=2)
    {
        error_message += three + " three's, ";
        error_counter++;
    }
    if(four>=2)
    {
        error_message += four + " four's, ";
        error_counter++;
    }
    if(five>=2)
    {
        error_message += five + " five's, ";
        error_counter++;
    }
    if(six>=2)
    {
        error_message += six + " six's, ";
        error_counter++;
    }
    if(seven>=2)
    {
        error_message += seven + " seven's, ";
        error_counter++;
    }
    if(eight>=2)
    {
        error_message += eight + " eight's, ";
        error_counter++;
    }
    if(nine>=2)
    {
        error_message += nine + " nine's, ";
        error_counter++;
    }
    if(error_counter > 0)
    {
        if(args->row_on)
        {
            error_message += "on row " + args->row;
        }   
        else if(args->col_on)
        {
            error_message += "on column " + args->col;
        }
		err_msg += (error_message + "\n");
    }
	//cout << "error message: " << err_msg << endl;
 }

void *sub_grid_validation(void *arguments)
{

    struct thread_data *args;
    args = (struct thread_data *)arguments;
    int error_counter = 0;
    string error_message = "";
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
        c = grid[args->row][args->col];
        if(counter = 2)
        {
           args->col -= 3;
            args->row++;
            counter = -1;
        }
        args->col++;
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
        error_counter++;
        error_message += one + " one's, ";
    }
    if(two>1)
    {
        error_counter++;
        error_message += two + " two's, ";
    }
    if(three>1)
    {
        error_counter++;
        error_message += three + " three's, ";
    }
    if(four>1)
    {
		error_counter++;
		error_message += four + " four's, ";

    }
    if(five>1)
    {
        error_counter++;
        error_message += five + " five's, ";
    }
    if(six>1)
    {
        error_counter++;
        error_message += six + " six's, ";
    }
    if(seven>1)
    {
        error_counter++;
        error_message += seven + " seven's, ";
    }
    if(eight>1)
    {
        error_counter++;
        error_message += eight + " eight's, ";
    }
    if(nine>1)
    {
		error_counter++;
		error_message += nine + " nine's, ";
    }
	string last;
    if(error_counter > 0)
    {
		// Initially these below were chars but I'm lazy so I just switch to string.
		string first = "on sub grid row [" + (args->row + 1);
        string second = "," + (args->row + 4);
        string third = first + second;
        string fourth = " and column [" + (args->col + 1);
        string fifth = "," + (args->col + 4);
        string sixth = "].";
        string sev = third + fourth;
        string ayy = sev + fifth;
        string last = ayy + sixth;
		err_msg += (error_message + last);
	}
}
