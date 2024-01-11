#include <stdio.h>
#include <limits.h>
#define INF INT_MAX // Giá trị vô cùng
#define V 6 // Số đỉnh của đồ thị

// Hàm tìm đỉnh có khoảng cách nhỏ nhất từ các đỉnh chưa xét
int TimDinhNhoNhat(long long khoangCach[], int daXet[]) {
    int minIndex = -1;
    long long min = INF;
    
    for (int v = 0; v < V; v++) {
        if (!daXet[v] && khoangCach[v] < min) {
            min = khoangCach[v];
            minIndex = v;
        }
    }

    return minIndex; // Trả về đỉnh có khoảng cách nhỏ nhất
}

// Hàm in đường đi và khoảng cách từ nguồn đến các đích
void HienThiDuongDi(long long khoangCach[], int n, int truoc[], int nguon) {
    printf("Dinh \t Khoang cach tu nguon\tDuong di\n");
    for (int i = 0; i < V; i++) {
        printf("%d \t %lld \t\t\t", i, khoangCach[i]);

        // Truy vết đường đi từ nguồn tới đỉnh i
        int j = i;
        while (j != nguon) {
            printf("%d <- ", j);
            j = truoc[j];
        }
        printf("%d\n", nguon);
    }
}

// Thuật toán Dijkstra
void Dijkstra(int doThi[V][V], int nguon) {
    long long khoangCach[V]; // Mảng lưu khoảng cách ngắn nhất từ nguồn đến các đỉnh
    int daXet[V]; // Mảng đánh dấu các đỉnh đã xét
    int truoc[V]; // Mảng lưu đỉnh đến trước đỉnh hiện tại trên đường đi ngắn nhất

    for (int i = 0; i < V; i++) {
        khoangCach[i] = INF; // Khởi tạo khoảng cách của tất cả các đỉnh là vô cùng
        daXet[i] = 0; // Gán tất cả các đỉnh chưa xét có giá trị là 0
        truoc[i] = -1; // Gán tất cả các đỉnh đến trước đỉnh hiện tại với giá trị là -1
    }

    khoangCach[nguon] = 0;

    // Tìm đỉnh có khoảng cách nhỏ nhất từ các đỉnh chưa xét
    for (int count = 0; count < V - 1; count++) {
        int u = TimDinhNhoNhat(khoangCach, daXet); // Lấy đỉnh có khoảng cách nhỏ nhất

        daXet[u] = 1; // Đánh dấu đỉnh đã xét

        // Cập nhật khoảng cách của các đỉnh kề với đỉnh vừa xét
        for (int v = 0; v < V; v++) {
            if (!daXet[v] && doThi[u][v] != INF &&
                khoangCach[u] != INF &&
                khoangCach[u] + doThi[u][v] < khoangCach[v])
            {
                khoangCach[v] = khoangCach[u] + doThi[u][v];
                truoc[v] = u; // Cập nhật đỉnh đến trước đỉnh hiện tại
            }
        }
    }

    HienThiDuongDi(khoangCach, V, truoc, nguon);
}


int main() {
    int doThi[V][V] = {
        {0,   10,  4,   INF, INF, INF},
        {10,  0,   1,   2,   1,   INF},
        {4,   1,   0,   4,   5,   INF},
        {INF, 2,   4,   0,   4,   6},
        {INF, 1,   5,   4,   0,   7},
        {INF, INF, INF, 6,   7,   0}
    };

    int nguon;
    printf("\nNhap dinh bat dau: ");
    scanf_s("%d", &nguon);

    Dijkstra(doThi, nguon);

    return 0;
}
