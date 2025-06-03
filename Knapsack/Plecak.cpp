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

void bruteforce(vector<int> &weights, vector<int> &values, int B)
{
    int n = weights.size();
    int max_value = 0;
    int best_combination = 0;
    for (int i = 0; i < (1 << n); i++)
    {
        int current_weight = 0;
        int current_value = 0;
        for (int j = 0; j < n; j++)
        {
            if (i & (1 << j)) // If the j-th item is included
            {
                current_weight += weights[j];
                current_value += values[j];
            }
        }
        if (current_weight <= B)
        {
            max_value = max(max_value, current_value);
            if (max_value == current_value)
                best_combination = i;
        }

    }
    cout << "Maksymalna wartosc: " << max_value << endl;
    cout << "Wybrane przedmioty: ";
    for (int i = 0; i < n; ++i) {
        if (best_combination & (1 << i)) {
            cout << i << " ";
        }
    }
    cout << endl;


}

void greed(vector<int> &weights, vector<int> &values, int B)
{
    vector<int> selected_items;
    int n = weights.size();
    vector<pair<float, int>> ratio;
    for (int i = 0; i < n; i++)
    {
        ratio.push_back({(float)values[i] / weights[i], i});
    }
    sort(ratio.rbegin(), ratio.rend());
    int current_weight = 0;
    int current_value = 0;
    while (true)
    {
        int index = ratio[0].second;
        ratio.erase(ratio.begin());
        if (current_weight + weights[index] <= B)
        {
            current_weight += weights[index];
            current_value += values[index];
            selected_items.push_back(index);
        }
        else
        {
            break;
        }
    }
    sort(selected_items.begin(), selected_items.end());
    cout << "Maksymalna wartosc: " << current_value << endl;
    cout << "Wybrane przedmioty: ";
    for (int i = 0; i < selected_items.size(); i++)
    {
        cout << selected_items[i] << " ";
    }
    cout << endl;
}

void dynamic(vector<int> &weights, vector<int> &values, int B)
{
    int n = weights.size();
    vector<vector<int>> dp(n + 1, vector<int>(B + 1, 0));
    for (int i = 1; i <= n; i++)
    {
        for (int j = 0; j <= B; j++)
        {
            if (weights[i - 1] <= j) // weights i values jest indeksowane od 0           
            {
                dp[i][j] = max(dp[i - 1][j], dp[i - 1][j - weights[i - 1]] + values[i - 1]);
            }
            else
            {
                dp[i][j] = dp[i - 1][j];
            }
        }
    }
    cout << "Maksymalna wartosc: " << dp[n][B] << endl;

    vector<int> selected_items;
    int b = B;
    for (int i = n; i > 0; i--) 
    {
        if (dp[i][b] != dp[i - 1][b]) {
            selected_items.push_back(i - 1);
            b -= weights[i-1];
        }
    }
    cout << "Wybrane przedmioty: ";
    for (int i = selected_items.size()-1; i >= 0; i--) {
        cout << selected_items[i] << " ";
    }
    cout << endl;
}

void get_data(vector<int> &weights, vector<int> &values, int &B)
{
    ifstream file("dane.txt");
    if (!file.is_open())
    {
        cout << "Nie mozna otworzyc pliku!" << endl;
        return;
    }
    int n;
    file >> n;
    file >> B;
    weights.resize(n);
    values.resize(n);
    for (int i = 0; i < n; i++)
    {
        file >> weights[i];
        file >> values[i];
    }
    cout << "Wczytano dane z pliku." << endl;
}

int main()
{
    vector<int> weights;
    vector<int> values;
    int B;
    get_data(weights, values, B);
    bruteforce(weights, values, 8);
    cout << "------------------------" << endl;
    greed(weights, values, 8);
    cout << "------------------------" << endl;
    dynamic(weights, values, 8);
    return 0;
}