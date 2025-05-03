#include <iostream>
#include <chrono>
#include <vector>
#include <queue>
#include <cstdlib>
#include <ctime>
#include <cmath>
#include <algorithm>
#include <iostream>
#include <fstream>
using namespace std;
using namespace std::chrono;

void print(vector<int> v)
{
    for (int i = 0; i < v.size(); i++)
    {
        cout << v[i] << " ";
    }
    cout << endl;
}

void addedgeadj(vector<vector<int>> &matrixadj, int i, int j)
{
    matrixadj[i][j] = 1;
    matrixadj[j][i] = -1;
}

void display(vector<vector<int>> &matrixadj)
{
    for (int i = 1; i < matrixadj.size(); i++)
    {
        for (int j = 1; j < matrixadj[i].size(); j++)
        {
            cout << matrixadj[i][j] << " ";
        }
        cout << endl;
    }
}

void matrixgraph(vector<vector<int>> &matrixgraph, int n, vector<vector<int>> &matrixadj)
{
    for(int i=1; i<n;i++)
    {
        vector<int> next;
        vector<int> previous;
        vector<int> absence;
        for(int j=1;j<n;j++)
        {
            if(matrixadj[i][j]==1)
                next.push_back(j);
            if(matrixadj[i][j]==-1)
                previous.push_back(j);
            if(matrixadj[i][j]==0)
                absence.push_back(j);
        }
        next.push_back(next.back());
        previous.push_back(previous.back());
        absence.push_back(absence.back());
        for(int j=0;j<next.size()-1;j++)
            matrixgraph[i][next[j]]=next[j+1];

        for(int j=0;j<previous.size()-1;j++)
            matrixgraph[i][previous[j]]=previous[j+1]+n-1;

        for(int j=0;j<absence.size()-1;j++)
            matrixgraph[i][absence[j]]= -1*absence[j+1];

        matrixgraph[i][n]=next.front();
        matrixgraph[i][n+1]=previous.front();
        matrixgraph[i][n+2]=absence.front();
        next.clear();
        previous.clear();
        absence.clear();
    }
}

vector<int> DELmsasiedztwa(vector<vector<int>> &matrixadj, int V)
{
    vector<int> indegree(V);
    for(int i = 1; i<V; i++)
    {
        for(int j = 1; j<V; j++)
        {
            if(matrixadj[i][j] == 1)
                indegree[j]++;
        }
    }   
    queue<int> queue;
    for (int i = 1; i < V; i++)
    {
        if(indegree[i] == 0)
            queue.push(i);
    }
    vector<int> result;
    while(!queue.empty())
    {
        int removed = queue.front();
        queue.pop();
        result.push_back(removed);
        for(int i = 1; i < V; i++)
        {
            if(matrixadj[removed][i] == 1)
            {
                indegree[i]--;
                if(indegree[i] == 0)
                    queue.push(i);
            }
        }
    }

    if(result.size() != V-1)
    {
        cout << "Graph is not a DAG" << endl;
        return vector<int>();
    }
    return result;
    
}


int main()
{
    int n = 11; // Number of vertices
    vector<vector<int>> matrixadj(n, vector<int>(n, 0)); // Adjacency matrix initialized to 0
    vector<vector<int>> matrixgraphs(n, vector<int>(n+3, 0));

    /*addedgeadj(matrixadj, 1, 2);
    addedgeadj(matrixadj, 2, 4);
    addedgeadj(matrixadj, 2, 5);
    addedgeadj(matrixadj, 3, 1);
    addedgeadj(matrixadj, 3, 2);
    addedgeadj(matrixadj, 4, 3);
    addedgeadj(matrixadj, 5, 1);
    addedgeadj(matrixadj, 5, 4);
   */

    addedgeadj(matrixadj, 1, 2);
    addedgeadj(matrixadj, 2, 3);
    addedgeadj(matrixadj, 3, 4);
    addedgeadj(matrixadj, 4, 6);
    addedgeadj(matrixadj, 6, 9);
    addedgeadj(matrixadj, 1, 10);
    addedgeadj(matrixadj, 10, 5);
    addedgeadj(matrixadj, 5, 2);
    addedgeadj(matrixadj, 5, 7);
    addedgeadj(matrixadj, 10, 6);
    addedgeadj(matrixadj, 7, 8);
    addedgeadj(matrixadj, 8, 9);
    addedgeadj(matrixadj, 8, 6);
    addedgeadj(matrixadj, 8, 4);
    addedgeadj(matrixadj, 2, 7);

    vector<int> topsort = DELmsasiedztwa(matrixadj, n);
    print(topsort);

    /*
    matrixgraph(matrixgraphs, n, matrixadj);
    display(matrixgraphs);*/

    return 0;

}