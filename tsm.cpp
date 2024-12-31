#include "tsm.h"
#include <cmath>

static long long int counter = 0;
static int minDis = INT16_MAX;
static string answer = "No Result";

string Traveling(int matrix[20][20], int vertex_nums, char start)
{ 
    answer = "";

    counter = 0;
    minDis = INT16_MAX;

    int i;
    int visit[vertex_nums];

    for (i = 0; i<vertex_nums; i++)
    {
        visit[i] = 0;
    }

    TravelingHelper(matrix, vertex_nums, start, start, visit, "", 0);

    if (answer!="") 
    {
        cout << answer << endl;
        cout << "Min Distance: " << minDis << endl;
    }
    else cout << "No Solution for this graph!" << endl;
    
    return answer;
}

int minInRange(int array[], int size, int greaterthan, int lessthan)
{
    int min = lessthan;
    for (int i = 0; i<size; i++)
    {
        if (array[i]<min && array[i]>greaterthan) min = array[i];
    }
    return min;
}

bool isThroughAll(int visit[], int vertex_nums)
{
    int sum = 0;
    for (int i = 0; i<vertex_nums;i++)
    {
        sum += visit[i];
    }

    return (sum==vertex_nums+1);
}

void TravelingHelper(int matrix[20][20], int vertex_nums, char firstSource, char source, int visit[], string previous, int dis)
{
    int i;
    int id = intVertex(source);
    visit[id]++;

    string toAdd = {source, ' '};
    previous += toAdd;

    counter++;
    if (counter>=1200000) return;

    if (visit[intVertex(firstSource)]==2)
    { 
        if (isThroughAll(visit, vertex_nums) && dis<minDis)
        {
            minDis = dis;
            answer = previous;
            return;
        }
        else 
        {
            visit[intVertex(firstSource)]--;
            return;
        }
    }

    int weight[vertex_nums];
    for (i = 0; i<vertex_nums; i++)
    {
        weight[i] =matrix[id][i];
    }
    int lastmin = 0;
    while (minInRange(weight, vertex_nums, lastmin, INT16_MAX)!=INT16_MAX)
    {
        int value = minInRange(weight, vertex_nums, lastmin, INT16_MAX);
        for (i = 0; i<vertex_nums;i++)
        {
            if (value==weight[i]) 
            {
                int disTemp = dis + weight[i];

                if (i!=intVertex(firstSource) && visit[i]==1) {continue;}
                bool check = true;
                for (int k = 0 ;k<vertex_nums; k++)
                {
                    if (visit[k]!=1) check = false;
                }
                if (!check && i==intVertex(firstSource)) {continue;}
                if (minDis<=disTemp) {continue;}

                int visitTemp[vertex_nums];
                for (int k = 0; k<vertex_nums; k++)
                {
                    visitTemp[k] = visit[k];
                }
                TravelingHelper(matrix, vertex_nums, firstSource, vertex(i), visitTemp, previous, disTemp);
            }
        }
        lastmin = value;
    }

    return;
}