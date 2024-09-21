#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void taofile(int n) {
    FILE *f = fopen("taci.txt", "w");
    if (f == NULL) {
        printf("Tao file khong thanh cong");
        return;
    }
    fprintf(f, "%d\n", n);
    srand(time(NULL));
    int a[n*n];
    for (int i = 0; i < n*n; i++) {
        a[i] = i;
    }
    for (int i = 0; i < n*n; i++) {
        int j = rand() % (n*n);
        int temp = a[i];
        a[i] = a[j];
        a[j] = temp;
    }

    int count = 0;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            fprintf(f, "%d ", a[count]);
            count++;
        }
        fprintf(f, "\n");
    }
    fclose(f);
}

int main() {
    int n;
    printf("Nhap gia tri cua n (3 <= n <= 99): ");
    scanf("%d", &n);

    if (n < 3 || n > 99) {
        printf("Gia tri khong hop le.\n");
        return 1;
    }

    taofile(n);
    printf("Da tao file thanh cong.\n");
    return 0;
}
