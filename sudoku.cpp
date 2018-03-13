/*
 * Author: Majid Aziz
 * Email: aziz112@mail.chapman.edu
 * DATE: 3/7/18
 * Program: Sudoku validation using 9 threads other than main.
 * */
#include <iostream>
#include <fstream>
#include <pthread.h>
#include <cstdlib>
#include <string>
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
/* just a global counter */
int glb_cnt = 0;
/* Creates sudoku grid */
void create_grid(char* argv);
/* Error Checks if duplicate value in either same row or column, depending on argument values */
void *same_line_validation(void *arguments);
/* Error Checks sub grid to contain one of each value ranging from [1,9]  */
void *sub_grid_validation(void *arguments);
void print_grid();

int main(int argc, char* argv[])
{
    create_grid(argv[1]);
    print_grid();
    cout << "Errors will be listed below..if any" << endl << endl;
    pthread_t threads[HEIGHT];
    struct thread_data args[HEIGHT];
    int rc;
    int i;
    // ROW CHECKING
    for(i=0; i<HEIGHT; ++i)
    {
        args[i].row = i;
        args[i].col = 0;
	args[i].row_on = true;
	args[i].col_on = false;
        //cout << "row before _create: " << args[i].row << endl;
        rc = pthread_create(&threads[i], NULL, same_line_validation, (void *) &args); 
        //cout << "row after _create: " << args[i].row << endl;
        if(rc)
        {
            cout << "Uh oh " << rc << endl;
            exit(-1);
        }
    }
    pthread_join(threads[8], NULL);
    // COLUMN CHECKING
    glb_cnt = 0;
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
    if(args->row_on)
    {
        args->row = glb_cnt;
        args->col = 0;
    }
    else if(args->col_on)
    {
        args->col = glb_cnt;
        args->row = 0;
    }
    glb_cnt++;
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
        {
            args->col++;
        }    
        else if(args->col_on)
        {
            args->row++;
        }
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
    if(one>=2)
    {
        cout << one << " one's, ";
        error_counter++;
    }
    if(two>=2)
    {
        cout << two << " two's, ";
        error_counter++;
    }
    if(three>=2)
    {
        cout << three << " three's, ";
        error_counter++;
    }
    if(four>=2)
    {
        cout << four << " four's, ";
        error_counter++;
    }
    if(five>=2)
    {
        cout << five << " five's, ";
        error_counter++;
    }
    if(six>=2)
    {
        cout << six << " six's, ";
        error_counter++;
    }
    if(seven>=2)
    {
        cout << seven << " seven's, ";
        error_counter++;
    }
    if(eight>=2)
    {
        cout << eight << " eight's, ";
        error_counter++;
    }
    if(nine>=2)
    {
        cout << nine << " nine's, ";
        error_counter++;
    }
    if(error_counter > 0)
    {

        if(args->row_on)
        {
            cout << "on row " << args->row + 1 << endl;
        }
        else if(args->col_on)
        {
            cout << "on column " << args->col + 1 << endl;
        }
    }
    if(glb_cnt == 9 && error_counter > 0)
    {
        cout << endl;
    }
 }

void *sub_grid_validation(void *arguments)
{
    struct thread_data *args;
    args = (struct thread_data *) arguments;
    // I don't know why args-row is set to 9 but this fixes that, same with ->col set to 8..
    if(args->row == 9)
    {
        args->row = 0;
    }
    if(args->col == 8)
    {
        args->col = 0;
    }
    int error_counter = 0;
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
        if(counter == 2)
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
        cout << one << " one's, ";
    }
    if(two>1)
    {
        error_counter++;
        cout << two << " two's, ";
    }
    if(three>1)
    {
        error_counter++;
        cout << three << " three's, ";
    }
    if(four>1)
    {
		error_counter++;
        cout << four << " four's, ";
    }
    if(five>1)
    {
        error_counter++;
        cout << five << " five's, ";
    }
    if(six>1)
    {
        error_counter++;
        cout << six << " six's, ";
    }
    if(seven>1)
    {
        error_counter++;
        cout << seven << " seven's, ";
    }
    if(eight>1)
    {
        error_counter++;
        cout << eight << " eight's, ";
    }
    if(nine>1)
    {
		error_counter++;
        cout << nine << " nine's, ";
    }
    if(error_counter > 0)
    {
       cout << "in sub grid rows [" << args->row - 2 << "," << args->row << "] "
            << "columns [" << args->col + 1 << "," << args->col + 3 << "]" << endl;
	}
}

void print_grid()
{
    cout << "Testing Grid Below" << endl << endl;
    for(int i=0; i<HEIGHT; ++i)
    {
        for(int j=0; j<HEIGHT; ++j)
        {
           cout << grid[i][j] << ","; 
        }
        cout << endl;
    }
    cout << endl;
}
