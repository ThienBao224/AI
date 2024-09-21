#include <iostream>
#include <fstream>
#include <cstdlib>
#include <cmath>
using namespace std;

const int maxn = 10;

void docfile(int a[maxn][maxn], int b[maxn][maxn], int &n) {
    ifstream file("taci1.txt");
    if (!file) {
        cerr << "Khong the mo file." << endl;
        exit(1);
    }

    file >> n; // Đọc kích thước ma trận

    // Đọc ma trận a
    for (int i = 1; i <= n; ++i) {
        for (int j = 1; j <= n; ++j) {
            file >> a[i][j];
        }
    }

    // Đọc ma trận b
    for (int i = 1; i <= n; ++i) {
        for (int j = 1; j <= n; ++j) {
            file >> b[i][j];
        }
    }

    file.close();
}

int h1(int a[maxn][maxn], int b[maxn][maxn], int n) {
    int d = 0;
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
            if (a[i][j] != 0 && a[i][j] != b[i][j]) {
                d++;
            }
        }
    }
    return d;
}

void timvitri(int a[maxn][maxn], int b[maxn][maxn], int n, int i, int j, int &x, int &y) {
    for (int k = 1; k <= n; k++) {
        for (int l = 1; l <= n; l++) {
            if (a[i][j] == b[k][l]) {
                x = k;
                y = l;
                return;
            }
        }
    }
}

int h2(int a[maxn][maxn], int b[maxn][maxn], int n) {
    int x, y, s = 0;
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
            if (a[i][j] != 0) {
                timvitri(a, b, n, i, j, x, y);
                s = s + abs(x - i) + abs(y - j);
            }
        }
    }
    return s;
}

int main() {
    int a[maxn][maxn], b[maxn][maxn], n;
    docfile(a, b, n);
    cout << "Gia tri do do H1: " << h1(a, b, n) << endl;
    cout << "Gia tri do do H2: " << h2(a, b, n) << endl;
    return 0;
}
