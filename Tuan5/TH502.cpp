#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>

using namespace std;

vector<int> readInput(const string& filename) {
    ifstream file(filename);
    if (!file.is_open()) {
        cerr << "Khong tim thay file " << endl;
        exit(1);
    }
    int n;
    file >> n;
    vector<int> jobTimes(n);
    for (int i = 0; i < n; ++i) {
        file >> jobTimes[i];
    }
    file.close();
    return jobTimes;
}

int findMaxEfficiency(const vector<int>& jobTimes, int numMachines) {
    int n = jobTimes.size();
    vector<int> machines(numMachines, 0);
    for (int i = 0; i < n; ++i) {
        int minIndex = min_element(machines.begin(), machines.end()) - machines.begin();
        machines[minIndex] += jobTimes[i];
    }
    return *max_element(machines.begin(), machines.end());
}

int main() {
    string filename = "scheduled.txt";
    vector<int> jobTimes = readInput(filename);
    int numMachines = 3;
    int maxEfficiency = findMaxEfficiency(jobTimes, numMachines);
    cout << "Hieu qua cong viec: " << maxEfficiency << endl;
    return 0;
}
