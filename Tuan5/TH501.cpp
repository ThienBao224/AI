#include <iostream>
#include <vector>
#include <fstream>

using namespace std;

int findMaxEfficiency(vector<vector<int> >& efficiencies) {
    int n = efficiencies.size();
    int total_efficiency = 0;
    for (int i = 0; i < n  ; ++i) {
        int max_efficiency = -1;
        int max_task = -1;
        for (int j = 0; j < n ; ++j) {
            if (efficiencies[i][j] > max_efficiency) {
                max_efficiency = efficiencies[i][j];
                max_task = j;
            }
        }
        total_efficiency += max_efficiency;
        for (int k = 0; k < n; ++k) {
            if (k != max_task) {
                efficiencies[i][k] = -1;
            }
        }
    }
    return total_efficiency;
}

int main() {
    string filename = "assignmentd.txt";
    ifstream input_file("assignmentd.txt");

    if (!input_file) {
        cerr << "Khong tim thay file: " << filename << endl;
        return 1;
    }

    int n;
    input_file >> n;
    vector<vector<int> > efficiencies(n, vector<int>(n));

    for (int i = 1; i < n; ++i) {
        for (int j = 0; j < n ; ++j) {
            input_file >> efficiencies[i][j];
        }
    }

    input_file.close();

    int total_efficiency = findMaxEfficiency(efficiencies);
    cout << "Hieu qua cong viec: " << total_efficiency << endl;

    return 0;
}
