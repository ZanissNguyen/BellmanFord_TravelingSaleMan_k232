#include <string>
#include <iostream> 
#include <iomanip>
using namespace std;

int intVertex(char);
char vertex(int);

void BF(int graph[20][20], int, char, int *, int *);

string findShortest(char, char, int*, int*);
string BF_Path(int graph[20][20], int, char, char);