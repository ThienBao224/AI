#include <iostream> // Thư viện cho nhập/xuất dữ liệu
#include <fstream> // Thư viện cho nhập/xuất file
#include <cstdlib> // Thư viện chuẩn C
#include <ctime> // Thư viện cho thời gian để tạo số ngẫu nhiên
using namespace std; // Sử dụng không gian tên chuẩn để sử dụng hàm của C++

const int MAX_CITIES = 2000; // Định nghĩa số lượng tối đa các thành phố
int M[MAX_CITIES][MAX_CITIES]; // Mảng 2 chiều lưu khoảng cách giữa các thành phố
int solution[MAX_CITIES]; // Mảng lưu trữ lời giải hiện tại
long long cost, n_cost; // Biến lưu trữ chi phí hiện tại và mới
int neighbor[MAX_CITIES]; // Mảng lưu trữ lời giải hàng xóm
int NumberOfCity; // Biến lưu trữ số lượng thành phố

// Hàm đọc dữ liệu từ file
void read_file(string f_name) {
    ifstream file(f_name.c_str()); // Mở file để đọc
    if (!file.is_open()) { // Kiểm tra xem file đã mở thành công chưa
        cout << "Lỗi: Không thể mở file " << f_name << endl; // In ra thông báo lỗi
        return;
    }

    // Đọc số lượng thành phố từ file
    if (!(file >> NumberOfCity)) {
        cout << "Lỗi: Không đọc được số lượng thành phố từ file." << endl; // In ra thông báo lỗi
        file.close(); // Đóng file
        return;
    }

    // Kiểm tra xem số lượng thành phố có vượt quá giới hạn không
    if (NumberOfCity > MAX_CITIES) {
        cout << "Lỗi: Số lượng thành phố vượt quá giới hạn." << endl; // In ra thông báo lỗi
        file.close(); // Đóng file
        return;
    }

    // Đọc ma trận khoảng cách từ file
    for (int i = 0; i < NumberOfCity; i++)
        for (int j = 0; j < NumberOfCity; j++)
            if (!(file >> M[i][j])) { // Kiểm tra xem việc đọc phần tử ma trận có thất bại không
                cout << "Lỗi: Không đọc được phần tử của ma trận từ file." << endl; // In ra thông báo lỗi
                file.close(); // Đóng file
                return;
            }

    file.close(); // Đóng file
}

// Hàm khởi tạo một lời giải cá nhân
void init_individual() {
    // Khởi tạo lời giải với các thành phố theo thứ tự tuần tự
    for (int i = 0; i < NumberOfCity; i++)
        solution[i] = i;
    int j, tmp;
    // Trộn ngẫu nhiên các thành phố
    for (int i = NumberOfCity - 1; i > 0; i--) {
        j = rand() % i;
        tmp = solution[i];
        solution[i] = solution[j];
        solution[j] = tmp;
    }
    cost = 0; // Khởi tạo chi phí là 0
    // Tính toán chi phí ban đầu của lời giải
    for (int i = 1; i < NumberOfCity; i++)
        cost += M[solution[i - 1]][solution[i]];
    cost += M[solution[NumberOfCity - 1]][solution[0]];
}

// Hàm cập nhật lời giải hiện tại với lời giải hàng xóm nếu cải thiện
bool update_solution() {
    n_cost = 0; // Khởi tạo chi phí mới là 0
    // Tính toán chi phí của lời giải hàng xóm
    for (int i = 1; i < NumberOfCity; i++)
        n_cost += M[neighbor[i - 1]][neighbor[i]];
    n_cost += M[neighbor[NumberOfCity - 1]][neighbor[0]];

    // Kiểm tra xem lời giải hàng xóm có cải thiện so với lời giải hiện tại không
    if (n_cost < cost) {
        // Cập nhật lời giải hiện tại với lời giải hàng xóm
        for (int i = 0; i < NumberOfCity; i++)
            solution[i] = neighbor[i];
        cost = n_cost; // Cập nhật chi phí
        return true; // Trả về true cho biết đã cải thiện
    }
    return false; // Trả về false cho biết không có cải thiện
}

// Hàm thực hiện phép đảo trên lời giải hiện tại
bool reverse() {
    // Tạo các chỉ số ngẫu nhiên để đảo một phần của lời giải
    int x = rand() % (NumberOfCity - 1);
    int y = x + rand() % (NumberOfCity - x - 1);
    // Thực hiện phép đảo
    for (int i = 0; i < x; i++)
        neighbor[i] = solution[i];
    for (int i = x; i <= y; i++)
        neighbor[i] = solution[y - i + x];
    for (int i = y + 1; i < NumberOfCity; i++)
        neighbor[i] = solution[i];

    // Cập nhật lời giải hiện tại với lời giải hàng xóm nếu có cải thiện
    return update_solution();
}

// Hàm thực hiện phép chèn (chưa được triển khai)
bool insert() {
    return false; // Giữ chỗ, chưa được triển khai
}

// Hàm thực hiện phép cắt (chưa được triển khai)
bool cut() {
    return false; // Giữ chỗ, chưa được triển khai
}

// Hàm thực hiện phép đổi chỗ (chưa được triển khai)
bool exchange() {
    return false; // Giữ chỗ, chưa được triển khai
}

// Hàm ghi kết quả ra file
void write_file(string name, long start, long stop) {
    fstream file(name.c_str(), ios::out | ios::app); // Mở file để ghi (chế độ nối)
    if (!file.is_open()) { // Kiểm tra xem file đã mở thành công chưa
        cout << "Lỗi khi ghi file!" << endl; // In ra thông báo lỗi
        return;
    }
    // Ghi thời gian thực thi ra file
    file << "Thời gian: " << (stop - start) * 1.0 / CLOCKS_PER_SEC << endl;
    // Ghi chi phí của lời giải ra file
    file << cost << endl;
    // Ghi lời giải ra file
    for (int i = 0; i < NumberOfCity; i++)
        file << solution[i] + 1 << " ";
    file << solution[0] + 1; // Ghi thành phố đầu tiên một lần nữa để hoàn thành chu trình
    file << endl << "----------------------" << endl; // Ghi dấu phân cách
    file.close(); // Đóng file
}

// Hàm thực hiện Tìm kiếm Biến đổi Vùng (VNS)
void VNS() {
    init_individual(); // Khởi tạo lời giải
    bool flag; // Biến để theo dõi việc cải thiện
    int loop = 0; // Khởi tạo biến đếm vòng lặp
    // Thực hiện các lần lặp VNS
    while (loop < 10000000) { // Giới hạn số lần lặp
        // Thử các cấu trúc hàng xóm khác nhau và cập nhật lời giải nếu cải thiện
        flag = (reverse() || cut() || insert() || exchange());
        loop = flag ? 0 : loop + 1; // Đặt lại biến đếm nếu tìm thấy cải thiện
    }
}

int main() {
    string files[1] = {"tspa.txt"}; // Mảng các tên file đầu vào
    string outs[1] = {"out_a.txt"}; // Mảng các tên file đầu ra

    // Lặp qua từng file đầu vào
    for (int j = 0; j < 3; j++) {
        read_file(files[j]); // Đọc dữ liệu từ file
        // Thực hiện VNS và ghi kết quả
        for (int i = 0; i < 2; i++) {
            srand(time(NULL)); // Khởi tạo seed cho hàm random
            long start = clock(); // Lấy thời điểm bắt đầu thực thi
            VNS(); // Thực hiện Tìm kiếm Biến đổi Vùng
            long stop = clock(); // Lấy thời điểm kết thúc thực thi
            write_file(outs[j], start, stop); // Ghi kết quả ra file
        }
    }

    // Đọc dữ liệu từ file (chưa triển khai)
    read_file("tspa.txt");
    srand(time(NULL)); // Khởi tạo seed cho hàm random
    long start = clock(); // Lấy thời điểm bắt đầu thực thi
    VNS(); // Thực hiện Tìm kiếm Biến đổi Vùng
    long stop = clock(); // Lấy thời điểm kết thúc thực thi
    write_file("out_1.txt", start, stop); // Ghi kết quả ra file

    return 0; // Kết thúc chương trình
}
