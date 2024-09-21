#include <iostream>
#include <fstream>
#include <vector>
#include <queue>
#include <algorithm>
#include <limits>
using namespace std;

const int INF = numeric_limits<int>::max();

struct Vertex {
    int id;
    int g;
    int h;
    Vertex(int i, int gg, int hh) : id(i), g(gg), h(hh) {}
    bool operator<(const Vertex& other) const {
        return g + h > other.g + other.h;
    }
};

void readFile(const string& filename, int& n, int& m, int& s, int& t, vector<vector<pair<int, int>>>& graph, vector<int>& h_values) {
    ifstream file(filename);
    if (!file.is_open()) {
        cerr << "Khong mo duoc file." << endl;
        exit(1);
    }

    file >> n >> m >> s >> t;

    graph.resize(n + 1);
    for (int i = 0; i < m; ++i) {
        int u, v, w;
        file >> u >> v >> w;
        graph[u].push_back({v, w});
    }

    h_values.resize(n + 1);
    for (int i = 1; i <= n; ++i) {
        file >> h_values[i];
    }

    file.close();
}

int aStar(int n, int s, int t, const vector<vector<pair<int, int>>>& graph, const vector<int>& h_values) {
    vector<int> g(n + 1, INF);
    priority_queue<Vertex> pq;
    pq.push(Vertex(s, 0, h_values[s]));
    g[s] = 0;

    while (!pq.empty()) {
        Vertex u = pq.top();
        pq.pop();

        if (u.id == t) {
            return u.g; // Đã tìm được đường đi ngắn nhất đến đích
        }

        for (const auto& edge : graph[u.id]) {
            int v = edge.first;
            int w = edge.second;
            int new_g = u.g + w;
            if (new_g < g[v]) {
                g[v] = new_g;
                pq.push(Vertex(v, new_g, h_values[v]));
            }
        }
    }

    return -1; // Không tìm thấy đường đi từ s đến t
}

int main() {
    int n, m, s, t;
    vector<vector<pair<int, int>>> graph;
    vector<int> h_values;

    readFile("graph2.txt", n, m, s, t, graph, h_values);

    int shortest_path_length = aStar(n, s, t, graph, h_values);
    if (shortest_path_length != -1) {
        cout << "Do dai duong di ngan nhat tu dinh " << s << " den dinh " << t << " la " << shortest_path_length << endl;
    } else {
        cout << "Khong ton tai duong di tu dinh " << s << " den dinh " << t << endl;
    }

    return 0;
}
