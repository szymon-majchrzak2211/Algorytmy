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
#include <iomanip>
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

void addedgeadj(vector<vector<int>> &matrixadj, int i, int j) //nieskierowany
{
    matrixadj[i][j] = 1;
    matrixadj[j][i] = 1;
}

void addedgelist(vector<vector<int>> &listadj, int i, int j) //skierowany
{
    listadj[i].push_back(j);
}

void display(vector<vector<int>> &matrixadj)
{
    int numw=4;
    cout<<setw(numw)<<setfill(' ')<<" "<<"|";
    for (int i = 1; i < matrixadj[1].size(); i++)
        cout<<setw(numw)<<setfill(' ')<<i;
    cout<<endl;
    for (int i = 1; i < matrixadj[1].size()+1; i++)
        cout<<setw(numw)<<setfill('-')<<"-";
    cout<<endl;

    for (int i = 1; i < matrixadj.size(); i++)
    {
        cout<<setw(numw)<<setfill(' ')<<i<<"|";
        for (int j = 1; j < matrixadj[i].size(); j++)
        {
            cout <<setw(numw)<<setfill(' ')<<matrixadj[i][j];
        }
        cout << endl;
    }
}

void displaylist(vector<vector<int>> &listadj)
{
    int numw=4;
    for (int i = 1; i < listadj.size(); i++)
    {
        cout<<setw(numw)<<setfill(' ')<<i<<"|";
        for (int j = 0; j < listadj[i].size(); j++)
        {
            cout <<setw(numw)<<setfill(' ')<<listadj[i][j];
        }
        cout << endl;
    }
}

bool Hamiltonian(vector<vector<int>> &matrixadj, int V, int node, int start, vector<bool> &visited, int visitedcount, vector<int> &Path)
{
    visited[node] = true;
    visitedcount++;
    for (int i = 1; i < V; i++)
    {
        if (matrixadj[node][i] == 1)
        {
            if(i==start && visitedcount == V-1)
            {
                return true;
            }
            if (!visited[i])
            {
                if (Hamiltonian(matrixadj, V, i, start, visited, visitedcount, Path))
                {
                    Path.push_back(i);
                    return true;
                }
            }
        }
    }
    visited[node] = false;
    visitedcount--;
    return false;
}

vector<int> Hamiltonadj(vector<vector<int>> &matrixadj, int V)
{
    vector<int> Path;
    vector<bool> visited(V, false);
    int start = 1, visitedcount = 0;
    visited[start] = true;
    if(!Hamiltonian(matrixadj, V, start, start, visited, visitedcount, Path))
    {
        cout << " Graf nie zawiera cyklu Hamiltona." << endl;
        return vector<int>();
    }
    else
    {
        Path.push_back(start);
        reverse(Path.begin(), Path.end());
        return Path;
    }
}

bool Hamiltonianlist(vector<vector<int>> &listadj, int V, int node, int start, vector<bool> &visited, int visitedcount, vector<int> &Path)
{
    visited[node] = true;
    visitedcount++;
    for (int i = 0; i < listadj[node].size(); i++)
    {
        if (listadj[node][i] == start && visitedcount == V-1)
        {
            return true;
        }
        if (!visited[listadj[node][i]])
        {
            if (Hamiltonianlist(listadj, V, listadj[node][i], start, visited, visitedcount, Path))
            {
                Path.push_back(listadj[node][i]);
                return true;
            }
        }
    }
    visited[node] = false;
    visitedcount--;
    return false;
}

vector<int> Hamiltonlist(vector<vector<int>> &listadj, int V)
{
    vector<int> Path;
    vector<bool> visited(V, false);
    int start = 1, visitedcount = 0;
    visited[start] = true;
    if(!Hamiltonianlist(listadj, V, start, start, visited, visitedcount, Path))
    {
        cout << " Graf nie zawiera cyklu Hamiltona." << endl;
        return vector<int>();
    }
    else
    {
        Path.push_back(start);
        reverse(Path.begin(), Path.end());
        return Path;
    }
}

bool Eulerian(vector<vector<int>> &matrixadj, int V)
{
    for (int i = 1; i < V; i++)
    {
        int degree = 0;
        for (int j = 1; j < V; j++)
        {
            if (matrixadj[i][j] == 1)
                degree++;
        }
        if (degree % 2 != 0)
            return false;
    }
    return true;
}

void DFSEuler(vector<vector<int>> &matrixadj, int node, vector<int> &Path)
{
    for (int i = 1; i < matrixadj[node].size(); i++)
    {
        if (matrixadj[node][i] == 1)
        {
            matrixadj[node][i] = 0;
            matrixadj[i][node] = 0;
            DFSEuler(matrixadj, i, Path);
        }
    }
    Path.push_back(node);
}

vector<int> Euleradj(vector<vector<int>> &matrixadj, int V)
{
    vector<int> Path;
    vector<vector<int>> matrixadjcopy = matrixadj;
    if (!Eulerian(matrixadj, V))
    {
        cout << " Graf nie zawiera cyklu Eulera." << endl;
        return vector<int>();
    }
    else
    {
        DFSEuler(matrixadjcopy, 1, Path);
        reverse(Path.begin(), Path.end());
        return Path;
    }

}

bool Eulerianlist(vector<vector<int>> &listadj, int V)
{
    vector<int> indegree(V, 0);
    for (int i = 1; i < V; i++)
    {
        for (int j = 0; j < listadj[i].size(); j++)
        {
            indegree[listadj[i][j]]++;
        }
    }
    for (int i = 1; i < V; i++)
    {
        if (indegree[i]!= listadj[i].size())
            return false;
    }
    return true;
}
void DFSEulerlist(vector<vector<int>> &listadj, int node, vector<int> &Path)
{
    while (listadj[node].size() > 0)
    {
        int next = listadj[node][0];
        listadj[node].erase(listadj[node].begin());
        DFSEulerlist(listadj, next, Path);
    }
    Path.push_back(node);
}
vector<int> Eulerlist(vector<vector<int>> &listadj, int V)
{
    vector<int> Path;
    vector<vector<int>> listadjcopy = listadj;
    if (!Eulerianlist(listadj, V))
    {
        cout << " Graf nie zawiera cyklu Eulera." << endl;
        return vector<int>();
    }
    else
    {
        DFSEulerlist(listadjcopy, 1, Path);
        reverse(Path.begin(), Path.end());
        return Path;
    }
}


int main()
{
    ifstream fin1("graf1.txt");
    ifstream fin2("graf2.txt");
    if (!fin1) {
        cerr << "Error opening file" << endl;
        return 1;
    }
    int V1, E1,V2, E2;
    fin1 >> V1 >> E1;
    fin2 >> V2 >> E2;
    V1++;
    V2++; // Increase V by 1 to account for 1-based indexing
    vector<vector<int>> matrixadj(V1, vector<int>(V1, 0)); // Adjacency matrix initialized to 0
    vector<vector<int>> listadj(V2); // Adjacency list initialized to empty vectors
    while(!fin1.eof())
    {
        int i, j;
        fin1 >> i >> j;
        if(i<=0 || j<=0)
            break;
        if(i>=V1 || j>=V1)
            break;
        addedgeadj(matrixadj, i, j);
    }
    while(!fin2.eof())
    {
        int i, j;
        fin2 >> i >> j;
        if(i<=0 || j<=0)
            break;
        if(i>=V2 || j>=V2)
            break;
        addedgelist(listadj, i, j);
    }

    cout<<"Hamilton matrixadj: " << endl;
    print(Hamiltonadj(matrixadj, V1));
    cout<<"Hamilton listadj: " << endl;
    print(Hamiltonlist(listadj, V2));
    cout<<"Euler matrixadj: " << endl;
    print(Euleradj(matrixadj, V1));
    cout<<"Euler listadj: " << endl;
    print(Eulerlist(listadj, V2));
    return 0;
}