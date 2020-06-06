#include <iostream>
#include <time.h>

using namespace std;
typedef int itemType;

struct complexity {
    int compCnt = 0;
    int moveCnt = 0;
};

inline void swap(itemType a[], int i, int j);
int partition(itemType a[], int l, int r, complexity* p);
void quicksort(itemType a[], int l, int r,complexity* p);
void sort(itemType* a[], int);
void printArray(itemType*);
void makeA(itemType*, int);
void makeB(itemType*, int);

int main() {
    int N;
    cin >> N;

    itemType* A = new itemType[N];
    itemType* B = new itemType[N];

    // 배열 생성
    makeA(A, N);
    makeB(B, N);

    // 정렬
    complexity cplxA, cplxB;
    quicksort(A, 0, N - 1, &cplxA);
    quicksort(B, 0, N - 1, &cplxB);

    // 결과 출력
    cout << "SortedData_A : ";
    printArray(A);
    cout << endl;
    cout << "SortedData_B : ";
    printArray(B);

    cout << endl;
    cout << "Compare_Cnt_A " << cplxA.compCnt << ", DataMove_Cnt_A " << cplxA.moveCnt << endl;
    cout << "Compare_Cnt_B " << cplxB.compCnt << ", DataMove_Cnt_B " << cplxB.moveCnt << endl;

//    FILE* fwp = fopen("result_1.txt", "w");
//    for (int i = 0; i <= N; i += 500) {
//        makeA(A, i);
//        quicksort(A, 0, i-1, &cplxA);
//        fprintf(fwp, "%d\t%d\n", i, cplxA.moveCnt);
//    }
//    fclose(fwp);

}

inline void swap(itemType a[], int i, int j) {
    itemType  t = a[i];
    a[i] = a[j];
    a[j] = t;
}

int partition(itemType a[], int l, int r, complexity* p) {
    int i, j;
    itemType v;
    if (r > l) {
        v = a[l];
        p->moveCnt++;
        i = l;
        j = r + 1;
        for (;;) {
            while (1) {
                if (a[++i] < v)
                    p->compCnt++;
                else {
                    p->compCnt++;
                    break;
                }
            }
            while (1) {
                if (a[--j] > v)
                    p->compCnt++;
                else {
                    p->compCnt++;
                    break;
                }
            }
            if (i >= j)break;
            else {
                swap(a, i, j);
                p->moveCnt += 3;
            }
        }
        swap(a, j, l);
        p->moveCnt += 3;
    }
    return j;
}

void quicksort(itemType a[], int l, int r, complexity* p) {
    int  j;
    if (r > l) {
        j = partition(a, l, r, p);
        quicksort(a, l, j - 1, p);
        quicksort(a, j + 1, r, p);
    }
}



void makeA(itemType * A, int N) {
    // 데이터 배열 A 생성
    for (int i = 0; i < N; i++) {
        A[i] = N - i;
    }
}

void makeB(itemType * B, int N) {
    // 데이터 배열 B 생성
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
void sort(itemType * a[], int n) {
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
