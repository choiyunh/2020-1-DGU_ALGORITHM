#include <iostream>
#include <vector>
#include <time.h>
#include <algorithm>

struct complexity {
    int compCnt = 0;
    int moveCnt = 0;
};
typedef int itemType;
using namespace std;

void merge(itemType a[], int l, int mid, int r, complexity* p);
void mergesort(itemType a[], int l, int r, complexity* p);
void sort(itemType* a[], int);
void printArray(itemType*);
void makeA(itemType*, int);
void makeB(itemType*, int);

itemType* sorted;

int main() {
    int N;
    cin >> N;

    itemType* A = new itemType[N];
    itemType* B = new itemType[N];
    sorted = new itemType[N];

    makeA(A, N);
    makeB(B, N);

    complexity cplxA, cplxB;
    mergesort(A, 0, N - 1, &cplxA);
    mergesort(B, 0, N - 1, &cplxB);

    // 결과 출력
    cout << "SortedData_A : ";
    printArray(A);
    cout << endl;
    cout << "SortedData_B : ";
    printArray(B);

    cout << endl;
    cout << "Compare_Cnt_A " << cplxA.compCnt << ", DataMove_Cnt_A " << cplxA.moveCnt << endl;
    cout << "Compare_Cnt_B " << cplxB.compCnt << ", DataMove_Cnt_B " << cplxB.moveCnt << endl;


//    FILE* fwp = fopen("result_2.txt", "w");
//    for (int i = 0; i <= N; i+=500) {
//        makeA(A, i);
//        mergesort(A, 0, i-1, &cplxA);
//        fprintf(fwp, "%d\t%d\n", i, cplxA.moveCnt);
//    }
//    fclose(fwp);

    return 0;
}


void merge(itemType a[], int l, int mid, int r, complexity* p) {
    int i, j, k, n;
    i = l; j = mid + 1; k = l;
    while (i <= mid && j <= r) {
        if (a[i] <= a[j]) {
            p->compCnt++;
            sorted[k++] = a[i++];
            p->moveCnt++;
        }
        else {
            p->compCnt++;
            sorted[k++] = a[j++];
            p->moveCnt++;
        }
    }
    if (i > mid) {
        for (n = j; n <= r; n++) {
            sorted[k++] = a[n];
            p->moveCnt++;
        }
    }
    else {
        for (n = i; n <= mid; n++) {
            sorted[k++] = a[n];
            p->moveCnt++;
        }
    }
    for (n = l; n <= r; n++) {
        a[n] = sorted[n];
        p->moveCnt++;
    }
}

void mergesort(itemType a[], int l, int r, complexity* p) {
    int mid;
    if (l < r) {
        mid = (l + r) / 2;
        mergesort(a, l, mid, p);
        mergesort(a, mid + 1, r, p);
        merge(a, l, mid, r, p);
    }
}

void makeA(itemType* A, int N) {
    // 데이터 배열 A 생성
    for (int i = 0; i < N; i++) {
        A[i] = N - i;
    }
}

void makeB(itemType* B, int N) {
    // 데이터 배열 B 생성
    B[0] = INT_MIN; // 삽입정렬 위한 dummy data
    itemType** a = new itemType * [N + 1];
    a[0] = new int[2]; a[0][0] = -1; a[0][1] = 0; // dummy
    srand((unsigned int)time(NULL));
    for (int i = 1; i <= N; i++) {
        a[i] = new int[2];
        a[i][0] = (1 + rand() % N);
        a[i][1] = i;
    }
    sort(a, N);
    for (int i = 0; i < N; i++) {
        B[i] = a[i + 1][1];
    }
    for (int i = 0; i < N; i++) delete[] a[i];
    delete[] a;
}

// 데이터 배열 B 생성을 위한 정렬 함수(삽입정렬)
void sort(itemType* a[], int n) {
    itemType* temp = new itemType[2];
    int i, j;
    for (i = 2; i <= n; i++) {
        temp = a[i];
        j = i;
        while (a[j - 1][0] > temp[0]) {
            a[j] = a[j - 1];
            j--;
        }
        a[j] = temp;
    }
}

void printArray(int* a) {
    for (int i = 0; i < 20; i++)
        cout << a[i] << " ";
}
