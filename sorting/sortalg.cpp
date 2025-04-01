#include <iostream>
#include <chrono>
#include <vector>
#include <cmath>
#include <algorithm>
#include <cstdlib>
#include <ctime>
#include <iostream>
#include <fstream>
using namespace std;
using namespace std::chrono;

long long porownania = 0;
long long zamiany = 0;
int scalania = 0;
vector<int> P;

void print(vector<int>& T)
{
    for(int i=0; i<T.size(); i++)
    {
        cout<<T[i]<<" ";
    }
    cout<<endl;
}

vector<int> generateRandomSequence(int n) {
    vector<int> seq(n);
    for (int &num : seq) {
        num = rand() % (10*n);
    }
    return seq;
}

vector<int> generateIncreasingSequence(int n) {
    vector<int> seq = generateRandomSequence(n);
    sort(seq.begin(), seq.end());
    return seq;
}

vector<int> generateDecreasingSequence(int n) {
    vector<int> seq = generateIncreasingSequence(n);
    reverse(seq.begin(), seq.end());
    return seq;
}

vector<int> generateAShapeSequence(int n) {
    vector<int> firstHalf = generateIncreasingSequence(n / 2);
    vector<int> secondHalf = generateDecreasingSequence(n - n / 2);
    firstHalf.insert(firstHalf.end(), secondHalf.begin(), secondHalf.end());
    return firstHalf;
}

vector<int> generateVShapeSequence(int n) {
    vector<int> firstHalf = generateDecreasingSequence(n / 2);
    vector<int> secondHalf = generateIncreasingSequence(n - n / 2);
    firstHalf.insert(firstHalf.end(), secondHalf.begin(), secondHalf.end());
    return firstHalf;
}

//Algorytmy sortujące

void bubblesort(vector<int>& T)
{
    for(int i=0; i<T.size()-1; i++)
    {
        for(int j=0; j<T.size()-i-1; j++)
        {
            porownania++;
            if(T[j]<T[j+1])
            {
                zamiany++;
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
        porownania++;
        while(i>=0 && T[i]<key)
        {
            porownania++;
            T[i+1] = T[i];
            i--;
        }
        zamiany++;
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
            porownania++;
            if(T[j]>T[max])
            {
                max = j;
            }
        }
        zamiany++;
        swap(T[i], T[max]);
    }
}

void merge(vector<int>& T, vector<int>& L, vector<int>& R)
{
    scalania++;
    int i=0, j=0, k=0;
    while(i<L.size() && j<R.size())
    {
        porownania++;
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
    porownania++;
    if(l<n && T[l]<T[smallest])
    {
        smallest = l;
    }
    porownania++;
    if(r<n && T[r]<T[smallest])
    {
        smallest = r;
    }
    porownania++;
    if(smallest!=i)
    {
        zamiany++;
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
        zamiany++;
        swap(T[0], T[i]);
        heapify(T, i, 0);
    }
}

int partition(vector<int>& T, int p, int r)
{
    int pivot = T[r];
    P.push_back(pivot);
    int i = p, j=r;
    while (true)
    {
        porownania++;
        while (T[i]>pivot)
        {
            porownania++;
            i++;
        }
        porownania++;
        while (T[j]<pivot)
        {
            porownania++;
            j--;
        }
        porownania++;
        if(i<=j)
        {
            zamiany++;
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
    porownania++;
    if(p<r)
    {
        int q = partition(T, p, r);
        quicksort(T, p, q);
        quicksort(T, q+1, r);
    }
}

void shellsort(vector<int>& T)
{
    int n = T.size();
    int gap = 1; 
    while (gap < n) 
    {
        gap = gap * 3 + 1;
    }
    while (gap > 0) 
    {
        for (int i = gap; i < n; i++) 
        {
            int temp = T[i];
            int j = i;
            porownania++;
            while (j >= gap && T[j - gap] < temp) 
            {
                porownania++;
                T[j] = T[j - gap];
                j -= gap;
            }
            zamiany++;
            T[j] = temp;
        }
        gap = (gap - 1) / 3;
    }

}


int main()
{
    srand(time(0));
    ofstream fout("results.csv");
    int N[]={1000, 10000, 25000, 50000, 75000, 100000, 125000, 150000, 175000, 200000, 2000000 };
    vector<int> T,T0, T1, T2, T3, T4, T5, T6, T7, T8, T9;
    cout << "1 - bubblesort, 2 - insertionsort, 3 - selectionsort, 4 - mergesort, 5 - heapsort, 6 - quicksort, 7 - shellsort" << endl;
    for(int j=0; j<11; j++)
    {
        cout<<j<<endl;
        fout<<N[j]<<endl;
        T0=generateVShapeSequence(N[j]);
        T1=generateVShapeSequence(N[j]);
        T2=generateVShapeSequence(N[j]);
        /*T3=generateRandomSequence(N[j]);
        T4=generateRandomSequence(N[j]);
        T5=generateRandomSequence(N[j]);
        T6=generateRandomSequence(N[j]);
        T7=generateRandomSequence(N[j]);
        T8=generateRandomSequence(N[j]);
        T9=generateRandomSequence(N[j]);*/
        for(int i=5; i<6;i++)
        {
        fout<<i<<endl;
        for(int k=0; k<3; k++)
        {
        porownania = 0;
        zamiany = 0;
        switch(k)
        {
            case 0:
            T=T0;
            break;
            case 1:
            T=T1;
            break;
            case 2:
            T=T2;
            break;
            case 3:
            T=T3;
            break;
            case 4:
            T=T4;
            break;
            case 5:
            T=T5;
            break;
            case 6:
            T=T6;
            break;
            case 7:
            T=T7;
            break;
            case 8:
            T=T8;
            break;
            case 9:
            T=T9;
            break;
        }
        //print(T);
        auto start = high_resolution_clock::now();
        int sortwybor=i;
        switch(sortwybor)
        {
            case 1:
                bubblesort(T);
                break;
            case 2:
                insertionsort(T);
                break;
            case 3:
                selectionsort(T); 
                break;
            case 4:
                mergesort(T);
                break;
            case 5:
                heapsort(T);
                break;
            case 6:
                quicksort(T, 0, T.size()-1);
                break;
            case 7:
                shellsort(T);
                break;
        }
        auto stop = high_resolution_clock::now();
        auto duration = duration_cast<microseconds>(stop - start);
        //print(T);
        fout<<duration.count()<<";";
        fout<<porownania<<";";
        fout<<zamiany<<";";
        /*if (sortwybor == 4)
        {
            fout<<scalania<<";";
        }*/
        /* if(sortwybor == 6)
        {
            cout<<"Pivot: ";
            print(P);
        }*/
        fout<<endl;
        }
    }
}
    cout<<"Koniec"<<endl;
    fout.close();
    return 0;

}