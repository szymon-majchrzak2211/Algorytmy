#include <iostream>
#include <chrono>
using namespace std;
using namespace std::chrono;




void bubblesort(int T[], int n)
{
    for(int i=0; i<n-1; i++)
    {
        for(int j=0; j<n-i-1; j++)
        {
            if(T[j]<T[j+1])
            {
                swap(T[j], T[j+1]);
            }
        }
    }
}

void insertionsort(int T[], int n)
{
    for(int j=1; j<n; j++)
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

void selectionsort(int T[], int n)
{
    for(int i=0; i<n-1; i++)
    {
        int max = i;
        for(int j=i+1; j<n; j++)
        {
            if(T[j]>T[max])
            {
                max = j;
            }
        }
        swap(T[i], T[max]);
    }
}

int* merge(int* L, int* R)
{
    int* merged = new int[sizeof(L)+sizeof(R)];
    int i=0, j=0, k=0;
    while(i<sizeof(L) && j<sizeof(R))
    {
        if(L[i]<R[j])
        {
            merged[k] = L[i];
            i++;
        }
        else
        {
            merged[k] = R[j];
            j++;
        }
        k++;
    }
    while(i<sizeof(L))
    {
        merged[k] = L[i];
        i++;
        k++;
    }
    while(j<sizeof(R))
    {
        merged[k] = R[j];
        j++;
        k++;
    }
    return merged;
}

int* mergesort(int* T, int n)
{
    if(n==1)
    {
        return T;
    }
    int mid = n/2;
    int* L = new int[mid];
    int* R = new int[n-mid];
    for(int i=0; i<mid; i++)
    {
        L[i] = T[i];
    }
    for(int i=mid; i<n; i++)
    {
        R[i-mid] = T[i];
    }
    L = mergesort(L, mid);
    R = mergesort(R, n-mid);
    
    return merge(L,R);
}


int main()
{
    int n=10;
    int T[n];
    for (int i=0; i<n; i++)
    {
      T[i] = rand()%10;
      cout<<T[i]<<" ";
    }
    

    auto start = high_resolution_clock::now();
    //bubblesort(T, n);
    //insertionsort(T, n);
    //selectionsort(T, n);
    mergesort(T, n);
    auto stop = high_resolution_clock::now();
    auto duration = duration_cast<microseconds>(stop - start);
    cout<<"Sorted array: ";
    for(int i=0; i<n; i++)
    {
        cout<<T[i]<<" ";
    }
    cout<<endl;
    cout<<"Time taken: "<<duration.count()<<" microseconds"<<endl;
    return 0;
}