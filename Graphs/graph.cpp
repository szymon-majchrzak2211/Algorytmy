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
#include <set>
#include <random>
using namespace std;
using namespace std::chrono;

struct Edge {
    int from;
    int to;
};

void generateDAG(int vertices, int edges) {
    vector<Edge> result;
    set<pair<int, int>> existing_edges;

    // Tworzymy wierzchołki 1..V
    vector<int> nodes(vertices);
    for (int i = 0; i < vertices; ++i)
        nodes[i] = i + 1;  // <-- indeksowanie od 1

    random_shuffle(nodes.begin(), nodes.end());

    mt19937 rng(time(0));

    while ((int)result.size() < edges) {
        int i = rng() % vertices;
        int j = rng() % vertices;

        if (i >= j) continue;

        int from = nodes[i];
        int to = nodes[j];

        if (existing_edges.count({from, to}) == 0) {
            result.push_back({from, to});
            existing_edges.insert({from, to});
        }
    }
    ofstream outfile("graf.txt");
     // Pierwsza linia: liczba wierzchołków i krawędzi
    outfile << vertices << " " << edges << "\n";

    // Lista krawędzi (indeksy od 1)
    for (const auto& edge : result) {
        outfile << edge.from << " " << edge.to << "\n";
    }
    outfile.close();
}

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
        if(next.size()==0)
            next.push_back(0);
        if(previous.size()==0)
            previous.push_back(0);
        if(absence.size()==0)
            absence.push_back(0);
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
        cout << " Graf zawiera cykl. Sortowanie niemozliwe." << endl;
        return vector<int>();
    }
    return result;
    
}

vector<int> DELmgrafu(vector<vector<int>> &matrixgraph, int V)
{
    vector<int> indegree(V,0);
    for(int i = 1; i<V; i++)
    {
        int j;
        j=matrixgraph[i][V+1];
        while((j+V-1)!=matrixgraph[i][j] && j!=0)
        {
                indegree[i]++;
                j=matrixgraph[i][j]-(V-1);
        }
        if(j!=0)
            indegree[i]++;
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
        int k=matrixgraph[removed][V];
        while(k!=matrixgraph[removed][k] && k!=0)
        {
            indegree[k]--;
            if(indegree[k] == 0)
                queue.push(k);
            k=matrixgraph[removed][k];
        }
        if(k!=0)
        {
            indegree[k]--;
            if(indegree[k] == 0)
                queue.push(k);
        }
    }

    if(result.size() != V-1)
    {
        cout << " Graf zawiera cykl. Sortowanie niemozliwe." << endl;
        return vector<int>();
    }
    return result;
    
}

bool DFSs(vector<vector<int>> &matrixadj, int V, int node, vector<int> &visited, vector<int> &result)
{
    visited[node] = 1;
    for(int i = 1; i < V; i++)
    {
        if(matrixadj[node][i]==1)
        {
            if(visited[i]==1)
                return false;
            if(visited[i]==0)
                if(!DFSs(matrixadj, V, i,visited, result))
                    return false;
        }
    }
    visited[node] = 2;
    result.push_back(node);
    return true;
}

vector<int> DFSmsasiedztwa(vector<vector<int>> &matrixadj, int V)
{
    vector<int> visited(V, 0);
    vector<int> result;
    for(int i=1;i<V;i++)
    {
        if(visited[i]==0)
            if(!DFSs(matrixadj, V, i, visited, result))
            {
                cout << " Graf zawiera cykl. Sortowanie niemozliwe." << endl;
                return vector<int>();
            }
    }
    reverse(result.begin(), result.end());
    return result;
}

bool DFSg(vector<vector<int>> &matrixgraph, int V, int node, vector<int> &visited, vector<int> &result)
{
    visited[node] = 1;
    int i=matrixgraph[node][V];
    while(i!=0 && i!=matrixgraph[node][i])
    {
        if(visited[i]==1)
            return false;
        if(visited[i]==0)
            if(!DFSg(matrixgraph, V, i,visited, result))
                return false;
        i=matrixgraph[node][i];
    }
    if(i!=0)
    {
        if(visited[i]==1)
            return false;
        if(visited[i]==0)
            if(!DFSg(matrixgraph, V, i,visited, result))
                return false;
    }
    visited[node] = 2;
    result.push_back(node);
    return true;
}

vector<int> DFSmgrafu(vector<vector<int>> &matrixgraph, int V)
{
    vector<int> visited(V, 0);
    vector<int> result;
    for(int i=1;i<V;i++)
    {
        if(visited[i]==0)
            if(!DFSg(matrixgraph, V, i, visited, result))
            {
                cout << " Graf zawiera cykl. Sortowanie niemozliwe." << endl;
                return vector<int>();
            }
    }
    reverse(result.begin(), result.end());
    return result;
}


void Test()
{
    ofstream foutT("AdjDel.csv");
    ofstream foutM("AdjDSF.csv");
    ofstream foutI("GraphDel.csv");
    ofstream foutR("GraphDSF.csv");
    vector<vector<int>> matrixadj(101, vector<int>(101, 0)); // Adjacency matrix initialized to 0
    vector<vector<int>> matrixgraphs(101, vector<int>(104, 0));
    int V[11]={100,250,400,550,700,850,1000,1150,1300,1450,1600};
    for(int i=0; i<11; i++)
    {
        
        cout<<V[i]<<" ";
        V[i]++;
        matrixadj.resize(V[i], vector<int>(V[i], 0)); // Resize the adjacency matrix
        matrixgraphs.resize(V[i], vector<int>(V[i]+3, 0)); // Resize the graph matrix
        int E=0.5*V[i]*(V[i]-1)/2;
        cout<<E<<endl;
        generateDAG(V[i]-1,E);
        ifstream fin("graf.txt");
        while(!fin.eof())
        {
            int i, j;
            fin >> i >> j;
            if(i<=0 || j<=0)
                break;
            if(i>=V[i] || j>=V[i])
                break;
            addedgeadj(matrixadj, i, j);
        }
        fin.close();
        matrixgraph(matrixgraphs, V[i], matrixadj);
        auto start = high_resolution_clock::now();
        DELmsasiedztwa(matrixadj, V[i]);
        auto stop = high_resolution_clock::now();
        auto duration = duration_cast<microseconds>(stop - start);
        foutT <<V[i]-1<<";"<<duration.count()<<endl;
        auto start1 = high_resolution_clock::now();
        DELmgrafu(matrixgraphs, V[i]);
        auto stop1 = high_resolution_clock::now();
        auto duration1 = duration_cast<microseconds>(stop1 - start1);
        foutI <<V[i]-1<<";"<<duration1.count()<<endl;
        auto start2 = high_resolution_clock::now();
        DFSmsasiedztwa(matrixadj, V[i]);
        auto stop2 = high_resolution_clock::now();
        auto duration2 = duration_cast<microseconds>(stop2 - start2);
        foutM <<V[i]-1<<";"<<duration2.count()<<endl;
        auto start3 = high_resolution_clock::now();
        DFSmgrafu(matrixgraphs, V[i]);
        auto stop3 = high_resolution_clock::now();
        auto duration3 = duration_cast<microseconds>(stop3 - start3);
        foutR <<V[i]-1<<";"<<duration3.count()<<endl;
        matrixadj.clear();
        matrixgraphs.clear();
    }
    foutT.close();
    foutM.close();
    foutI.close();
    foutR.close();
    cout<<"Zapisano wyniki do plikow"<<endl;
}


int main()
{
    srand(time(0));
    cout << "Wybierz operacje: 1-test, 2-reszta " << endl;
    int t;
    cin >> t;
    if(t==1)
    {
        Test();
    }
    else
    {
    ifstream fin("graf.txt");
    if (!fin) {
        cerr << "Error opening file" << endl;
        return 1;
    }
    int V, E;
    fin >> V >> E;
    V++; // Increase V by 1 to account for 1-based indexing
    vector<vector<int>> matrixadj(V, vector<int>(V, 0)); // Adjacency matrix initialized to 0
    vector<vector<int>> matrixgraphs(V, vector<int>(V+3, 0));
    while(!fin.eof())
    {
        int i, j;
        fin >> i >> j;
        if(i<=0 || j<=0)
            break;
        if(i>=V || j>=V)
            break;
        addedgeadj(matrixadj, i, j);
    }
/*  Test graph 1
    addedgeadj(matrixadj, 1, 2);  
    addedgeadj(matrixadj, 2, 4);
    addedgeadj(matrixadj, 2, 5);
    addedgeadj(matrixadj, 3, 1);
    addedgeadj(matrixadj, 3, 2);
    addedgeadj(matrixadj, 4, 3);
    addedgeadj(matrixadj, 5, 1);
    addedgeadj(matrixadj, 5, 4);

    Test graph 2
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
    addedgeadj(matrixadj, 7, 9);
    addedgeadj(matrixadj, 7, 6);
*/   

    matrixgraph(matrixgraphs, V, matrixadj);
    //display(matrixgraphs);
    cout << "Macierz sasiedztwa DEL:" << endl;
    print(DELmsasiedztwa(matrixadj, V));
    cout<< "Macierz grafu DEL:" << endl;
    print(DELmgrafu(matrixgraphs, V));
    cout << "Macierz sasiedztwa DFS:" << endl;
    print(DFSmsasiedztwa(matrixadj, V));
    cout<< "Macierz grafu DFS:" << endl;
    print(DFSmgrafu(matrixgraphs, V));
    }
    return 0;

}