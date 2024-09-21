#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>

using namespace std;

struct Job {
    int index;
    int machine1Time;
    int machine2Time;
};

pair<vector<Job>, vector<Job>> divideJobs(const vector<Job>& jobs) {
    vector<Job> N1, N2;
    for (const auto& job : jobs) {
        if (job.machine1Time <= job.machine2Time) {
            N1.push_back(job);
        } else {
            N2.push_back(job);
        }
    }
    return {N1, N2};
}

bool compareJobs(const Job& job1, const Job& job2) {
    return job1.machine1Time < job2.machine1Time;
}

vector<Job> johnsonAlgorithm(const vector<Job>& jobs) {
    vector<Job> sortedJobs;
    auto [N1, N2] = divideJobs(jobs);
    sort(N1.begin(), N1.end(), [](const Job& job1, const Job& job2) {
        return job1.machine1Time < job2.machine1Time;
    });
    sort(N2.begin(), N2.end(), [](const Job& job1, const Job& job2) {
        return job1.machine2Time > job2.machine2Time;
    });
    sortedJobs = N1;
    sortedJobs.insert(sortedJobs.end(), N2.begin(), N2.end());

    return sortedJobs;
}

vector<Job> readInput(const string& filename) {
    ifstream file(filename);
    if (!file.is_open()) {
        cerr << "Khong the mo file!" << endl;
        exit(1);
    }

    int n;
    file >> n;
    vector<Job> jobs(n);
    for (int i = 0; i < n; ++i) {
        jobs[i].index = i;
        file >> jobs[i].machine1Time;
    }
    for (int i = 0; i < n; ++i) {
        file >> jobs[i].machine2Time;
    }

    file.close();
    return jobs;
}

int main() {
    string filename = "Johnsond.txt";
    vector<Job> jobs = readInput(filename);
    vector<Job> scheduledJobs = johnsonAlgorithm(jobs);
    int lastEndTimeOnMachineB = 0;
    int currentTimeOnMachineA = 0;
    for (const auto& job : scheduledJobs) {
        currentTimeOnMachineA += job.machine1Time;
        lastEndTimeOnMachineB = max(lastEndTimeOnMachineB, currentTimeOnMachineA) + job.machine2Time;
    }
    cout << "Thoi gian hoan thanh tat ca cong viec: " << lastEndTimeOnMachineB << endl;

    return 0;
}
