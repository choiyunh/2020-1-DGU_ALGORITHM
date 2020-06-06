//
// Created by YunHo on 2020/05/20.
// Lab #05 Q2
//

#include <iostream>
#include <vector>

// 비교 및 이동 횟수 카운트를 위한 구조체 정의
struct complexity {
    int compCnt = 0;
    int moveCnt = 0;
};

typedef int itemType;
using namespace std;

void sort(itemType* a[], int);
void printArray(itemType*);
void makeA(itemType*, int);
void makeB(itemType*, int);
void makeC(itemType*, int);
void CountSort(itemType *a, itemType *b, itemType *N, int n, int k, complexity *p);

int main() {
    int N;
    cin >> N;

    itemType* A = new itemType[N+1];
    itemType* B = new itemType[N+1];
    itemType* C = new itemType[N+1];

    makeA(A, N);
    makeB(B, N);
    makeC(C, N);
    complexity cplxA,cplxB,cplxC;

    itemType *sortedA = new itemType[N];
    itemType *sortedB = new itemType[N];
    itemType *sortedC = new itemType[N];
    itemType *n = new itemType[N];

    CountSort(A,sortedA,n,N,N,&cplxA); // 배열 A 정렬
    CountSort(B,sortedB,n,N,N,&cplxB); // 배열 B 정렬
    CountSort(C,sortedC,n,N,N,&cplxC); // 배열 C 정렬

    // 결과 출력
    cout << "SortedData_A : ";
    printArray(sortedA);
    cout << "SortedData_B : ";
    printArray(sortedB);
    cout << "SortedData_C : ";
    printArray(sortedC);

    cout << "Compare_Cnt_A " << cplxA.compCnt << ", DataMove_Cnt_A " << cplxA.moveCnt << endl;
    cout << "Compare_Cnt_B " << cplxB.compCnt << ", DataMove_Cnt_B " << cplxB.moveCnt << endl;
    cout << "Compare_Cnt_C " << cplxC.compCnt << ", DataMove_Cnt_C " << cplxC.moveCnt << endl;

//    FILE* fwp = fopen("result_2.txt", "w");
//    for (int i = 0; i <= N; i += 500) {
//        makeA(A, i);
//        CountSort(A,sortedA,n,i,i,&cplxA);
//        fprintf(fwp, "%d\t%d\n", i, cplxA.moveCnt);
//    }
//    fclose(fwp);

    return 0;
}

void CountSort(itemType *a, itemType *b, itemType *N, int n, int k, complexity *p) {
    p->compCnt=0; p->moveCnt=0;
    int i,j;
    for(i=1; i<=k; i++) N[i]=0;
    for(i=1; i<=n; i++) N[a[i]] = N[a[i]] + 1;
    for(i=2; i<=k; i++) N[i] = N[i] + N[i-1];
    for(j=n; j>=1; j--) {
        b[N[a[j]]] = a[j];
        p->moveCnt++;
        N[a[j]] = N[a[j]] - 1;
    }
}

void makeA(itemType* A, int N) {
    // 데이터 배열 A 생성
    A[0]=0; //dummy
    for (int i = 1; i <= N; i++) { // N, N-1, ..., 1
        A[i] = N - i + 1;
    }
}

void makeB(itemType* B, int N) {
    // 데이터 배열 B 생성
    B[0] = 0; // dummy
    itemType** a = new itemType * [N + 1];
    a[0] = new int[2]; a[0][0] = -1; a[0][1] = 0; // dummy
    srand((unsigned int)time(NULL));
    for (int i = 1; i <= N; i++) {
        a[i] = new int[2];
        a[i][0] = (1 + rand() % N);
        a[i][1] = i;
    }
    sort(a, N);
    for (int i = 1; i <= N; i++) {
        B[i] = a[i][1];
    }
    for (int i = 0; i < N; i++) delete[] a[i];
    delete[] a;
}

void makeC(itemType* C, int N){
    // 데이터 배열 C 생성
    C[0]=0; //dummy
    for(int i=1; i<=N;i++)
        C[i] = rand() % N + 1;
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
    for (int i = 1; i <= 20; i++)
        cout << a[i] << " ";
    cout<<endl;
}