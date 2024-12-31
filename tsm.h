#include <string>
#include <iostream>
#include <iomanip>
using namespace std;

void printArray(int array[], int vertex_nums);
int intVertex(char);
char vertex(int);

string Traveling(int matrix[20][20], int vertex_nums, char start);

int minInRange(int array[], int size, int greaterthan, int lessthan);

void TravelingHelper(int matrix[20][20], int vertex_nums, char firstSource, char source, int visit[], string previous, int dis);