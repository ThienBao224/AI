#include <iostream>
#include <fstream>
#include <vector>
#include <set>
#include <limits>

using namespace std;

// Định nghĩa một đỉnh trong đồ thị
struct Vertex {
    int id;             // ID của đỉnh
    int degree;         // Bậc của đỉnh
    int color;          // Màu của đỉnh
    set<int> adj;       // Danh sách kề của đỉnh
};

// Đọc đồ thị từ file và khởi tạo danh sách các đỉnh
vector<Vertex> readGraph(const string& filename) {
    ifstream file(filename);
    int numVertices, numEdges;
    file >> numVertices >> numEdges;
    vector<Vertex> graph(numVertices);

    int u, v;
    for (int i = 0; i < numEdges; ++i) {
        file >> u >> v;
        graph[u].adj.insert(v);
        graph[v].adj.insert(u);
        graph[u].degree++;
        graph[v].degree++;
    }

    file.close();
    return graph;
}

// Tìm đỉnh chưa được tô có bậc lớn nhất
int findNextVertex(const vector<Vertex>& graph) {
    int maxDegree = numeric_limits<int>::min();
    int nextVertexId = -1;
    for (int i = 0; i < graph.size(); ++i) {
        if (graph[i].degree > maxDegree && graph[i].color == -1) {
            nextVertexId = i;
            maxDegree = graph[i].degree;
        }
    }
    return nextVertexId;
}

// Chọn màu cho một đỉnh
int chooseColor(const vector<Vertex>& graph, int vertexId) {
    set<int> usedColors;
    for (int adjVertex : graph[vertexId].adj) {
        if (graph[adjVertex].color != -1) {
            usedColors.insert(graph[adjVertex].color);
        }
    }

    int color = 0;
    while (usedColors.count(color)) {
        color++;
    }
    return color;
}

// Tô màu cho đồ thị
void colorGraph(vector<Vertex>& graph) {
    while (true) {
        int nextVertexId = findNextVertex(graph);
        if (nextVertexId == -1) {
            break; // Không còn đỉnh chưa được tô
        }

        int color = chooseColor(graph, nextVertexId);
        graph[nextVertexId].color = color;

        // Cập nhật bậc của các đỉnh kề
        for (int adjVertex : graph[nextVertexId].adj) {
            if (graph[adjVertex].color == -1) {
                graph[adjVertex].degree--;
            }
        }

        // Đặt bậc của đỉnh đã tô màu là 0
        graph[nextVertexId].degree = 0;
    }
}

// Tính số lượng màu được sử dụng
int countColorsUsed(const vector<Vertex>& graph) {
    set<int> usedColors;
    for (const Vertex& vertex : graph) {
        if (vertex.color != -1) {
            usedColors.insert(vertex.color);
        }
    }
    return usedColors.size();
}

int main() {
    vector<Vertex> graph = readGraph("color3.txt");
    for (int i = 0; i < graph.size(); ++i) {
        graph[i].id = i;
        graph[i].color = -1;            // Khởi tạo màu của tất cả các đỉnh là -1 (chưa được tô)
    }

    colorGraph(graph);
    int numColorsUsed = countColorsUsed(graph);
    cout << "Number of colors used: " << numColorsUsed << endl;

    return 0;
}
