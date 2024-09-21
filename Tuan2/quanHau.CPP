#include<iostream>
#include<cmath>
using namespace std;

int N;
int count = 0;
int a[100];

void display() {
    cout << "Cach " << ++count << ": ";
    for (int m = 0; m < N; m++) {
        cout << a[m] + 1 << " ";
    }
    cout << endl;
}

bool UCV(int m, int n) {
    for (int i = 0; i < m; i++)
        if (a[i] == n || abs(i - m) == abs(a[i] - n))
            return false;
    return true;
}

void GiaiQuanHau(int m) {
    for (int n = 0; n < N; n++) {
        if (UCV(m, n)) {
            a[m] = n;
            if (m == N - 1)
                display();
            else
                GiaiQuanHau(m + 1);
        }
    }
}

int main() {
    cout << "Nhap gia tri cua N cho ban co NxN: ";
    cin >> N;

    GiaiQuanHau(0);

    return 0;
}
