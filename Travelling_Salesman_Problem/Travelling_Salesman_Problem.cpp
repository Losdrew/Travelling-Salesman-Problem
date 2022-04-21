#include <iostream>
#include <random>
#include <string>
#include <vector>
#include <cmath>

using namespace std;

int** GenerateMatrix(int n, int S);
void Permutations(int** matrix, int n, int S);
void Greedy(int** matrix, int n, int S);

int main()
{
    cout << "Enter the number of experiments: ";
    int k;
    cin >> k;
    cin.get();

    for (int i = 0; i < k; i++)
    {
        cout << "\nExperiment #" << i + 1 << ":\n\n";

        cout << "Enter the number of vertices: ";
        int n;
        cin >> n;
        cin.get();

        cout << "\nEnter the starting vertex: ";
        int S;
        cin >> S;
        cin.get();

        int** matrix = GenerateMatrix(n, S);

        cout << "\nPermutation algorithm:" << endl;
        Permutations(matrix, n, S - 1);

        cout << "\nGreedy algorithm:" << endl;
        Greedy(matrix, n, S - 1);

        for (int i = 0; i < n; i++)
            delete[] matrix[i];
    }
}

//
// Generate matrix and print it on screen
//
int** GenerateMatrix(int n, int S)
{
    // random processor
    random_device rd;
    mt19937 mersenne(rd());

    cout << "\nIn this experiment: n = " << n << ", S = " << S << endl;

    int** matrix = new int* [n];

    for (int i = 0; i < n; i++)
        matrix[i] = new int[n];

    // fill matrix with random numbers < 100
    for (int i = 0; i < n; i++)
    {
        for (int m = 0; m < n; m++)
        {
            // main diagonal elements are equal to 0
            if (i == m)
                matrix[i][m] = 0;

            else
                if (matrix[i][m] < 0)
                    matrix[i][m] = matrix[m][i] = 1 + mersenne() % 100;
        }
    }

    // print matrix
    if (n < 20)
    {
        cout << "\nThe adjacency matrix:\n\n";
        for (int i = -1; i < n; i++)
        {
            if (i == -1)
            {
                for (int m = 1; m <= n; m++)
                    cout << "\t" << m;
                cout << "\n\n";
            }

            else
            {
                cout << i + 1;
                for (int m = 0; m < n; m++)
                    cout << "\t" << matrix[i][m];
                cout << endl;
            }
        }
    }
    return matrix;
}

//
// Permutations algorithm
//
void Permutations(int** matrix, int n, int S)
{
    // write all vertexes except the first
    vector<int> vertex;
    for (int i = 0; i < n; i++)
        if (i != S)
            vertex.push_back(i);

    int min_path = n * n * 100;

    string path = "";

    do {
        int current_pathweight = 0;

        // index value for rows
        int k = S;

        // get weight of current path
        for (unsigned int i = 0; i < vertex.size(); i++)
        {
            current_pathweight += matrix[k][vertex[i]];

            if (current_pathweight > min_path)
                break;

            k = vertex[i];
        }

        // add start-end edge weight
        current_pathweight += matrix[k][S];

        if (current_pathweight < min_path)
        {
            min_path = min(min_path, current_pathweight);

            // write min path to string
            path = to_string(S + 1) + "->";
            for (unsigned int i = 0; i < vertex.size(); i++)
                path += to_string(vertex[i] + 1) + "->";
        }

    } while (next_permutation(vertex.begin(), vertex.end()));

    cout << "\nThe shortest tour is: " << path << S + 1 << " with the cost of: " << min_path << endl;
}

//
// Greedy algorithm
//
void Greedy(int** matrix, int n, int S)
{
    vector<int> visited;
    visited.push_back(S);

    unsigned long min_path = 0;
    int remaining = n;

    // index value for rows
    int k = S;

    while (remaining > 1)
    {
        int current_pathweight = 100;

        for (int i = 0; i < n; i++)

            if (matrix[k][i] != 0 && find(visited.begin(), visited.end(), i) == visited.end())
                current_pathweight = min(current_pathweight, matrix[k][i]);

        min_path += current_pathweight;

        // index of min weight in current row becomes index of next row
        k = distance(matrix[k], find(matrix[k], matrix[k] + n, current_pathweight));

        visited.push_back(k);

        remaining--;
    }

    // add weight of route to initial city
    min_path += matrix[k][S];

    cout << "\nThe shortest tour is: ";

    // write vertexes that were passed
    for (unsigned int i = 0; i < visited.size(); i++)
        cout << visited[i] + 1 << "->";

    cout << S + 1 << " with the cost of: " << min_path << endl;
}