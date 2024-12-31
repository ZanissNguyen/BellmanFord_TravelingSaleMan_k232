#include "bellman.h"
#include "tsm.h"
#include <iostream>
#include <iomanip>
#include <fstream>
#include <vector>
#include <cstdlib> 

using namespace std;

/*
* * * * * * * * * * * * * * * * * * * * * * *
* Ho Chi Minh City University of Technology
* Faculty of Computer Science and Engineering
* Student's answer for Assignment
* Discrete Structure For Computing/Computer Science
* By: Nguyen Thanh Phat
* * * * * * * * * * * * * * * * * * * * * * *
* 
* * * * * * * * * * * * * * * * * * * * * * *
* g++ -o main main.cpp bellman.cpp tsm.cpp
* ./main
* * * * * * * * * * * * * * * * * * * * * * *
*/

// char A->Z: 65->90

void printArray(int array[], int vertex_nums);
void printMatrix(int graph[20][20], int vertex_nums);
void generateMatrix(int a[20][20], int vertex_nums, int max_value);

// # # # # # # //
// EXERCISE 1  //
// # # # # # # //
void Exercise_1(int matrix[20][20], int vertex_nums, char start)
{
    cout << "---------- Exercise 1: Bellman Ford ----------"<< endl;
    cout << "Source: "<< start << endl;
    int value[20];
    int prev[20];

    for (int i = 0; i<vertex_nums; i++)
    {
        value[i] = -1;
        prev[i] = -1;
    }
    value[intVertex(start)] = 0;

    for(int i=0;i<vertex_nums;i++)
    {
        BF(matrix,vertex_nums,start,value,prev);
        cout<<"> Step "<<setw(2) << setfill('0') <<i+1<<":"<<endl << setfill(' ');
        cout << "Value    | ";printArray(value, vertex_nums);
        cout<<endl;
        cout << "Previous | ";printArray(prev, vertex_nums);
        cout<<endl;
    }
}

// # # # # # # //
// EXERCISE 2  //
// # # # # # # //
void Exercise_2(int graph[20][20], int vertex_nums, char start, char goal)
{
    cout << "---------- Exercise 2: Shortest Path ----------"<< endl;
    cout << "Source: " << start << endl;
    cout << "Goal: " << goal << endl;
    cout<< BF_Path(graph,vertex_nums,start,goal) <<endl;
}

// # # # # # # //
// EXERCISE 3  //
// # # # # # # //
void Exercise_3(int graph[20][20], int vertex_nums, char start)
{
    // Exercise 3:
    cout << "---------- Exercise 3: Traveling Salesman Problem ----------"<< endl;
    cout << "Start City: " << start << endl;
    Traveling(graph, vertex_nums, start);
}

// # # # # # //
// TEST CASE //
// # # # # # //
//input:
// file contains data
// start node for 3 exercise and goal for bellman shortest
void testCase(int matrix[20][20], int vertex_nums, char start, char goal, string id)
{
    cout << "--------============< Test Case " << "["<< id<<"]"<<" >============--------"<< endl;
    
    printMatrix(matrix, vertex_nums);
    Exercise_1(matrix, vertex_nums, start);
    Exercise_2(matrix, vertex_nums, start, goal);
    Exercise_3(matrix, vertex_nums, start);

    cout << "--------============< Test Case " << "["<< id<<"]"<<" >============--------"<< endl;
    cout << endl << endl;

    return;
}

void testCase(const string& fileName, char start, char goal)
{
    cout << "--------============< Test Case " << "["<< fileName<<"]"<<" >============--------"<< endl;
    
    fstream fin;
    int matrix[20][20];
    int vertex_nums;

    fin.open(fileName, ios::in);    
    fin >> vertex_nums;

    for(int i=0;i<vertex_nums;i++)
    {
        for(int j=0;j<vertex_nums;j++)
        {
            fin>>matrix[i][j];
        }
    }

    printMatrix(matrix, vertex_nums);
    Exercise_1(matrix, vertex_nums, start);
    Exercise_2(matrix, vertex_nums, start, goal);
    Exercise_3(matrix, vertex_nums, start);

    cout << "--------============< Test Case " << "["<< fileName<<"]"<<" >============--------"<< endl;
    cout << endl << endl;

    return;
}

// TODO::main function
int main(int argc, char* argv[])
{
    // do exercise for random matrix =)) may be it's not random
    int a[20][20];
    int n = 4;
    int max_weight = 5;
    generateMatrix(a, n, max_weight);
    testCase(a, n, 'A', 'D', "000");

    // test case 1
    int tc1_g[20][20] =
    {
        {0, 55, 92, 92, 87, 49, 51, 1},
        {92, 0, 62, 7, 78, 32, 45, 82},
        {78, 51, 0, 81, 91, 22, 8, 73},
        {54, 100, 12, 0, 24, 14, 33, 62},
        {27, 58, 54, 82, 0, 50, 45, 35},
        {99, 63, 36, 56, 91, 0, 9, 34},
        {22, 20, 82, 66, 37, 28, 0, 22},
        {59, 37, 95, 79, 36, 7, 3, 0}
    };
    int tc1_vn = 8;
    testCase(tc1_g, tc1_vn, 'A', 'F', "001");

    //testcase 2
    int tc2_vn = 4;
    int tc2_g[20][20] =
    {   
        {0, 1, 1, 3},
        {2, 0, 3, 1},
        {1, 4, 0, 2},
        {1, 1, 1, 0}
    };
    testCase(tc2_g, tc2_vn, 'A', 'D', "002");

    //testcase 3
    int tc3_vn = 5;
    int tc3_g[20][20] =
    {
        {0, 6, 7, 0, 0},
        {0, 0, 0, -4, 5},
        {0, 8, 0, 9, -3},
        {2, 0, 0, 0, 7},
        {0, -2, 0, 0, 0}
    };
    testCase(tc3_g, tc3_vn, 'A', 'C', "003");

    // You can run on your file
    // first integer in file will be number of vertex |V|
    // then is the matrix |V| x |V| like your inMat... you can read more in testCase function above
    // testCase("inMat4.txt", 'A', 'D');

    return 1;
}

// support function
void printArray(int array[], int size)
{
    for (int i = 0; i<size; i++)
    {
        if (array[i]==INT16_MAX)
        {
            cout << "inf ";
        }
        else cout <<array[i] <<" ";
    }
}

void printMatrix(int graph[20][20], int vertex_nums)
{
    cout << " ";
    for (int i = 0; i<vertex_nums; i++)
    {
        cout << setw(5) << right << char(65+i);
    }
    cout << endl;
    for (int i = 0; i<vertex_nums; i++) 
    {
        for (int j = 0; j<vertex_nums ;j++)
        {
            if (j==0) cout << char(65+i) << setw(5) << right << graph[i][j];
            else if (j==vertex_nums-1) cout << setw(5) << right << graph[i][j] << endl;  //last element of row
            else cout << setw(5) << right << graph[i][j];
        }
    }
}

int intVertex(char c)
{
    if (c>=65 && c<=90) return (int)(c-65);
    else return 0;
}

char vertex(int num)
{
    return (char)(num+65);
}

void generateMatrix(int a[20][20], int vertex_nums, int max_value)
{
    for (int i = 0; i<vertex_nums; i++)
    {
        for (int j = 0; j<vertex_nums; j++)
        {
            if (i==j) a[i][j]=0;
            else a[i][j] = rand() % max_value+1;
        }
    }
}