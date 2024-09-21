#include <iostream>
#include <iomanip>
#include <fstream>
#include <vector>
#include <algorithm>
#include <queue>
#include <limits>
#include <string>
#include <ctime>
using namespace std;


const int INF = numeric_limits<int>::max();
const int start = 0;
int n;
vector<vector<int> > c;
int best_cost = INF;
vector<int> best_tour;
vector<bool> visited;
const string file_path = "tps1a.txt";
const string file_temp = "temp1.txt";
ofstream temp(file_temp.c_str());


void readFile();
void writeFile(const int &cost, const vector<int> &tour);
void outputTour(const vector<int> &tour);
int reduceMatrix(vector<vector<int> > &matrix, const int &cur, const int &next);
int calculateCost(vector<int> &tour);
void getTheBestCost();
void TSP_BranchAndBound(const int &cur, int &cost, const int &count, vector<int> &tour, vector<vector<int> > &reduced_matrix);
void TSP();

struct State
{
    int cost, city;

    State(int cost, int city) : cost(cost), city(city) {}
};

struct Heap
{
    vector<State> heap;

    void push(State state)
    {
        heap.push_back(state);
        heapify_up(heap.size() - 1);
    }

    State pop()
    {
        State state = heap[0];
        heap[0] = heap.back();
        heap.pop_back();
        heapify_down(0);
        return state;
    }

    bool empty() const
    {
        return heap.empty();
    }

    void heapify_up(int idx)
    {
        int parent_idx = (idx - 1) / 2;
        if (idx > 0 && compare(heap[idx], heap[parent_idx]))
        {
            swap(heap[idx], heap[parent_idx]);
            heapify_up(parent_idx);
        }
    }

    void heapify_down(const int &idx)
    {
        int left_idx = idx * 2 + 1;
        int right_idx = idx * 2 + 2;
        int max_idx = idx;
        if (left_idx < heap.size() && compare(heap[left_idx], heap[max_idx]))
            max_idx = left_idx;
        if (right_idx < heap.size() && compare(heap[right_idx], heap[max_idx]))
            max_idx = right_idx;
        if (max_idx != idx)
        {
            swap(heap[idx], heap[max_idx]);
            heapify_down(max_idx);
        }
    }

    bool compare(const State s1, const State s2) const
    {
        return s1.cost < s2.cost;
    }

    void swap(State &s1, State &s2)
    {
        State temp = s1;
        s1 = s2;
        s2 = temp;
    }
};

void readFile()
{
    ifstream fin((file_path + ".txt").c_str());
    fin >> n;
    c.resize(n, vector<int>(n));
    for (int i = 0; i < n; ++i)
    	for (int j = 0; j < n; ++j)
    		fin >> c[i][j];
    fin.close();
}

void writeFile(const int &cost, const vector<int> &tour)
{
    ofstream fout((file_path + "_BAB.out").c_str());
    fout << cost << endl;
    for (int i = 0; i <= n; ++i)
    	fout << tour[i] << " ";
    fout << endl;
    fout.close();
}

void outputTour(const vector<int> &tour)
{
    for (int i = 0; i <= n; ++i)
    	cout << tour[i] << " ";
    cout << endl;
}

int reduceMatrix(vector<vector<int> > &matrix, const int &cur, const int &next)
{
    int min_row;
    vector<int> min_column(n, INF);
    matrix[next][start] = INF;
    int reduction = 0;
    if (cur != next)
        for (int i = 0; i < n; ++i)
            matrix[cur][i] = matrix[i][next] = INF;

    for (int i = 0; i < n; ++i)
    {
        min_row = INF;
        for (int j = 0; j < n; ++j)
        {
            min_row = min(min_row, matrix[i][j]);
            min_column[j] = min(min_column[j], matrix[i][j]);
        }
        if (min_row != 0 && min_row != INF)
        {
            for (int j = 0; j < n; ++j)
            {
                if (matrix[i][j] != INF)
                    matrix[i][j] -= min_row;
                min_column[j] = min(min_column[j], matrix[i][j]);
            }
            reduction += min_row;
        }
    }

    for (int i = 0; i < n; ++i)
    {
        if (min_column[i] != 0 && min_column[i] != INF)
        {
            for (int j = 0; j < n; ++j)
                if (matrix[j][i] != INF)
                    matrix[j][i] -= min_column[i];
            reduction += min_column[i];
        }
    }
    return reduction;
}

int calculateCost(vector<int> &tour)
{
    int cost = 0;
    for (int i = 0; i < n; ++i)
        cost += c[tour[i]][tour[i + 1]];
    return cost;
}

void getTheBestCost()
{
    readFile();
    int cost;
    vector<int> tour(n + 1);
    ifstream fin(file_temp.c_str());
    while (!fin.eof())
    {
        fin >> cost;
        for (int i = 0; i <= n; ++i)
        	fin >> tour[i];
        cost = calculateCost(tour);
        if (cost < best_cost)
        {
            best_cost = cost;
            best_tour = tour;
        }
    }
}

void TSP_BranchAndBound(const int &cur, int &cost, const int &count, vector<int> &tour, vector<vector<int> > &reduced_matrix)
{
    if (count == n)
    {
        cost += c[cur][start];
        if (cost < best_cost)
        {
            best_cost = cost;
            best_tour = tour;
            cout << best_cost << ": ";
            outputTour(tour);
            // write the tour to file temp.txt
            temp << cost << " ";
            for (int i = 0; i <= n; ++i)
            	temp << tour[i] << " ";
            temp << endl;
        }
        return;
    }

    vector<vector<vector<int> > > reduce_matrices(n, reduced_matrix);
    Heap candidates;
    for (int next = 0; next < n; ++next)
    {
        if (!visited[next])
        {
            int new_cost = c[cur][next] + cost + reduceMatrix(reduce_matrices[next], cur, next);
            if (new_cost < best_cost)
                candidates.push(State(new_cost, next));
        }
    }

    while (!candidates.empty())
    {
        State candidate = candidates.pop();

        int next = candidate.city;
        visited[next] = true;
        tour[count] = next;
        TSP_BranchAndBound(next, candidate.cost, count + 1, tour, reduce_matrices[next]);
        visited[next] = false;
    }
}

void TSP()
{
    readFile();
    for (int i = 0; i < n; ++i)
        c[i][i] = INF;
    int cost = reduceMatrix(c, start, start);
    int count = 1;
    vector<int> tour(n + 1);
    tour[0] = tour[n] = start;
    visited.resize(n, false);
    visited[start] = true;
    TSP_BranchAndBound(start, cost, count, tour, c);

    getTheBestCost();

    cout << "Best cost: " << best_cost << endl;
    cout << "Best tour: ";
    outputTour(best_tour);
    writeFile(best_cost, best_tour);
}

int main()
{
    clock_t start_time = clock();

	TSP();

    clock_t end_time = clock();
    double duration = (end_time - start_time) * 1000.0 / CLOCKS_PER_SEC;
    cout << "Execution time: " << fixed << setprecision(4) << duration << "ms" << endl;
    return 0;
}
