#include <iostream>
#include <vector>
#include <fstream>
#include <cmath>
#include <algorithm>
using namespace std;

struct Diem{
    double x, y;
    Diem(double x, double y) : x(x), y(y) {}
};

double tinhKhoangCach(const Diem& p1, const Diem& p2){
    return sqrt(pow(p1.x - p2.x, 2) + pow(p1.y - p2.y, 2));
}

void hienthiCum(const vector<Diem>& dulieu, const vector<int>& cum){
    for(size_t i = 0; i < dulieu.size(); ++i){
        cout << "Cum " << cum[i] + 1 << " gom: (" << dulieu[i].x << ", " << dulieu[i].y << ")\n";
    }
    cout << "------------------------------\n";
}

void kMeans(vector<Diem>& duLieu, vector<Diem>& tamCum, int soLanLapToiDa) {
    vector<int> cum(duLieu.size(), 0);
    for (int lap = 0; lap < soLanLapToiDa; ++lap) {
        for (size_t i = 0; i < duLieu.size(); ++i) {
            int tamCumGanNhat = 0;
            double khoangCachNhoNhat = tinhKhoangCach(duLieu[i], tamCum[0]);

            for (size_t j = 1; j < tamCum.size(); ++j) {
                double khoangCach = tinhKhoangCach(duLieu[i], tamCum[j]);
                if (khoangCach < khoangCachNhoNhat) {
                    khoangCachNhoNhat = khoangCach;
                    tamCumGanNhat = j;
                }
            }
            cum[i] = tamCumGanNhat;
        }
        vector<int> demCum(tamCum.size(), 0);
        vector<Diem> tamCumMoi(tamCum.size(), {0, 0});
        for (size_t i = 0; i < duLieu.size(); ++i) {
            tamCumMoi[cum[i]].x += duLieu[i].x;
            tamCumMoi[cum[i]].y += duLieu[i].y;
            demCum[cum[i]]++;
        }
        for (size_t i = 0; i < tamCum.size(); ++i) {
            if (demCum[i] != 0) {
                tamCumMoi[i].x /= demCum[i];
                tamCumMoi[i].y /= demCum[i];
            }
        }
        tamCum = tamCumMoi;
    }
    vector<pair<int, Diem>> ketQua;
    for (size_t i = 0; i < duLieu.size(); ++i) {
        ketQua.push_back(make_pair(cum[i], duLieu[i]));
    }
    sort(ketQua.begin(), ketQua.end(), [](const auto& lhs, const auto& rhs) {
        return lhs.first < rhs.first;
    });
    for (const auto& pair : ketQua) {
        cout << "Cum " << pair.first + 1 << " gom: (" << pair.second.x << ", " << pair.second.y << ")\n";
    }
    cout << "-----------------------------\n";
}

void docFile(const string& tenFile, vector<Diem>& duLieu, vector<Diem>& tamCum) {
    ifstream file(tenFile);
    if (file.is_open()) {
        int n, k;
        file >> n >> k;
        double x, y;
        for (int i = 0; i < n; ++i) {
            file >> x >> y;
            duLieu.push_back(Diem(x, y));
        }
        for (int i = 0; i < k; ++i) {
            file >> x >> y;
            tamCum.push_back(Diem(x, y));
        }
        file.close();
    } else {
        cout << "Khong the mo file.\n";
    }
}

int main() {
    vector<Diem> duLieu, tamCum;
    int soLanLapToiDa=100;
    docFile("input2.txt", duLieu, tamCum);
    kMeans(duLieu, tamCum, soLanLapToiDa);
    return 0;
}
