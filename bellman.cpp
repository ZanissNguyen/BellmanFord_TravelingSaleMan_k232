#include "bellman.h"

// Exercise 1
void BF(int graph[20][20], int vertex_nums, char start, int * value, int * prev)
{
    if (value[intVertex(start)]==-1) value[intVertex(start)]=0;
    int newValue[vertex_nums];
    int newPrev[vertex_nums];

    for (int j = 0; j<vertex_nums; j++)
    {
        newValue[j] = value[j];
        newPrev[j] = prev[j];
    }

    for (int src = 0; src<vertex_nums; src++) 
    {
        for (int dest = 0; dest<vertex_nums ;dest++)
        {
            int weight = graph[src][dest];

            if (weight!=0 && value[src]!=-1)
            {
                if (newValue[dest]==-1)
                {
                    if (value[src] + weight < INT16_MAX) 
                    {
                        newValue[dest] = newValue[src] + weight;
                        newPrev[dest] = src;
                    }       
                }
                else
                {
                    if (value[src] + weight < newValue[dest]) 
                    {
                        newValue[dest] = value[src] + weight;
                        newPrev[dest] = src;
                    }  
                }
            }
        }
    }

    for (int j = 0; j<vertex_nums; j++)
    {
        value[j] = newValue[j];
        prev[j] = newPrev[j];
    }

    return;
}

// Exercise 2
string findShortest(char start, char end, int* value, int* prev)
{
    string result = "";
    int endInt = intVertex(end);
    int startInt = intVertex(start);

    if (value[endInt]==-1) return "No Path";

    string toAdd = {end, ' '};
    result = toAdd;
    int path = prev[endInt];

    while(path!=startInt)
    {
        toAdd = {vertex(path) , ' '};
        result = toAdd + result;
        path = prev[path];
    }
    toAdd = {start, ' '};
    result = toAdd + result;

    return result;
}

string BF_Path(int graph[20][20], int vertex_nums, char start, char goal)
{
    if (start==goal)
    {
        string path = {start};
        return path;
    } 

    int value[20];
    int prev[20];
    for (int i = 0 ; i<vertex_nums; i++) 
    {
        value[i] = -1; prev[i] = -1;
    }

    for(int i=0;i<vertex_nums;i++)
    {
        BF(graph,vertex_nums,start,value,prev);
    }

    string path = findShortest(start, goal, value, prev);
    return path;
}