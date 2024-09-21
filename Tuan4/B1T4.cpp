#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>

using namespace std;

#define max 2000

struct Vertex {
    int id;
    int degree;
    Vertex(int _id, int _degree) : id(_id), degree(_degree) {}

    bool operator<(const Vertex &other) const {
        return degree > other.degree;
    }
};

int n;
int c[max][max];

void readFile(const string &filename) {
    ifstream file(filename);
    if (!file) {
        cout << "Khong tim thay file.\n";
        return;
    }
    file >> n;
    for (int i = 0; i < n; ++i)
        for (int j = 0; j < n; ++j)
            file >> c[i][j];
    file.close();
}

void writeFile(int num_colors, const vector<int> &colors) {
    ofstream outfile("output_color.txt");
    for (int i = 0; i < n; ++i) {
        outfile << "Dinh " << i + 1 << " duoc to mau " << colors[i] << endl;
    }
    outfile << "So mau su dung: " << num_colors << endl;
    outfile.close();
}

int welshPowell() {
    vector<Vertex> vertices;
    for (int i = 0; i < n; ++i) {
        int degree = 0;
        for (int j = 0; j < n; ++j) {
            if (c[i][j]) {
                ++degree;
            }
        }
        vertices.push_back(Vertex(i, degree));
    }

    stable_sort(vertices.begin(), vertices.end());

    vector<int> colors(n, 0);

    int color = 1;
    bool all_colored, can_color;

    while (true) {
        all_colored = true;

        for (vector<Vertex>::iterator it = vertices.begin(); it != vertices.end(); ++it) {
            Vertex vertex = *it;

            if (!colors[vertex.id]) {
                can_color = true;

                for (int i = 0; i < n; ++i) {
                    if (c[vertex.id][i] && colors[i] == color) {
                        can_color = false;
                        break;
                    }
                }

                if (can_color) {
                    colors[vertex.id] = color;
                    all_colored = false;
                }
            }
        }

        if (all_colored) {
            break;
        }

        ++color;
    }

    writeFile(color - 1, colors);
    return color - 1;
}

int main() {
    string filename = "colorx.txt";
    readFile(filename);
    int num_colors = welshPowell();
    cout << "So mau su dung: " << num_colors << endl;
    return 0;
}
