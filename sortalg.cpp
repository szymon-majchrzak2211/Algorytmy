#include <iostream>
#include <chrono>
#include <vector>
#include <cmath>
using namespace std;
using namespace std::chrono;

void print(vector<int>& T)
{
    for(int i=0; i<T.size(); i++)
    {
        cout<<T[i]<<" ";
    }
    cout<<endl;
}

void bubblesort(vector<int>& T)
{
    for(int i=0; i<T.size()-1; i++)
    {
        for(int j=0; j<T.size()-i-1; j++)
        {
            if(T[j]<T[j+1])
            {
                swap(T[j], T[j+1]);
            }
        }
    }
}

void insertionsort(vector<int>& T)
{
    for(int j=1; j<T.size(); j++)
    {
        int key = T[j];
        int i = j-1;
        while(i>=0 && T[i]<key)
        {
            T[i+1] = T[i];
            i--;
        }
        T[i+1] = key;
    }
}

void selectionsort(vector<int>& T)
{
    for(int i=0; i<T.size()-1; i++)
    {
        int max = i;
        for(int j=i+1; j<T.size(); j++)
        {
            if(T[j]>T[max])
            {
                max = j;
            }
        }
        swap(T[i], T[max]);
    }
}

void merge(vector<int>& T, vector<int>& L, vector<int>& R)
{
    int i=0, j=0, k=0;
    while(i<L.size() && j<R.size())
    {
        if(L[i]>R[j])
        {
            T[k] = L[i];
            i++;
        }
        else
        {
            T[k] = R[j];
            j++;
        }
        k++;
    }
    while(i<L.size())
    {
        T[k] = L[i];
        i++;
        k++;
    }
    while(j<R.size())
    {
        T[k] = R[j];
        j++;
        k++;
    }
}

void mergesort(vector<int>& T)
{
    if(T.size()==1)
    {
        return;
    }
    int mid = T.size()/2;
    vector<int> L(mid);
    vector<int> R(T.size()-mid);
    for(int i=0; i<mid; i++)
    {
        L[i] = T[i];
    }
    for(int i=mid; i<T.size(); i++)
    {
        R[i-mid] = T[i];
    }
    mergesort(L);
    mergesort(R);
    merge(T, L, R);
}

void heapify(vector<int>& T, int n, int i)
{
    int smallest = i;
    int l = 2*i+1;
    int r = 2*i+2;
    if(l<n && T[l]<T[smallest])
    {
        smallest = l;
    }
    if(r<n && T[r]<T[smallest])
    {
        smallest = r;
    }
    if(smallest!=i)
    {
        swap(T[i], T[smallest]);
        heapify(T, n, smallest);
    }
}
void heapsort(vector<int>& T)
{
    for(int i=T.size()/2-1; i>=0; i--)
    {
        heapify(T, T.size(), i);
    }
    for(int i=T.size()-1; i>0; i--)
    {
        swap(T[0], T[i]);
        heapify(T, i, 0);
    }
}

int partition(vector<int>& T, int p, int r)
{
    int pivot = T[r];
    int i = p, j=r;
    while (true)
    {
        while (T[i]<pivot)
        {
            i++;
        }
        while (T[j]>pivot)
        {
            j--;
        }
        if(i<=j)
        {
            swap(T[i], T[j]);
            i++;
            j--;
        }
        else
        {
        return j;
        }
    }
    
}

void quicksort(vector<int>& T, int p, int r)
{
    if(p<r)
    {
        int q = partition(T, p, r);
        quicksort(T, p, q-1);
        quicksort(T, q+1, r);
    }
}

/*void shellsort(vector<int>& T)
{
}
*/

int main()
{
    int n=10;
    vector<int> T(n);
    for (int i=0; i<n; i++)
    {
      T[i] = rand()%1000;
    }
    print(T);
    auto start = high_resolution_clock::now();
    //bubblesort(T);
    insertionsort(T);
    //selectionsort(T);
    //mergesort(T);
    //heapsort(T);
    //quicksort(T, 0, T.size()-1);
    //shellsort(T);
    auto stop = high_resolution_clock::now();
    auto duration = duration_cast<microseconds>(stop - start);
    //print(T);
    cout<<"Time taken: "<<duration.count()<<" microseconds"<<endl;
    return 0;
}