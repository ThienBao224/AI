#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void taofile(int n) {
    FILE *f = fopen("HNtower.txt", "w");
    if (f == NULL) {
        printf("Khong the tao file HNtower.txt");
        return;
    }

    fprintf(f, "%d\n", n);

    srand(time(NULL));
    int discs[n];

    for (int i = 0; i < n; i++) {
        discs[i] = i + 1;
    }

    for (int i = 0; i < n; i++) {
        int j = rand() % n;
        int temp = discs[i];
        discs[i] = discs[j];
        discs[j] = temp;
    }

    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < n; j++) {
            if (j < n - i) {
                fprintf(f, "%d ", discs[j]);
            } else {
                fprintf(f, "0 ");
            }
        }
        fprintf(f, "\n");
    }

    fclose(f);
}

int main() {
    int n;
    printf("Nhap gia tri cua n (3 <= n <= 16): ");
    scanf("%d", &n);

    if (n < 3 || n > 16) {
        printf("Gia tri cua n khong hop le.\n");
        return 1;
    }

    taofile(n);
    printf("Da tao file HNtower.txt thanh cong.\n");
    return 0;
}
