//
// Created by YunHo on 2020/05/20.
// Lab #05 Q1
//

#include <iostream>
#include <time.h>

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

class MAKE_HEAP {
private:
    itemType *a;
    int N;
public:
    MAKE_HEAP(int max) {
        a = new itemType[max];
        N = 0;
    }
    ~MAKE_HEAP() { delete a; }

    void swap(itemType a[], int i, int j, complexity *p) {

        int temp;

        temp = a[j];
        a[j] = a[i];
        a[i] = temp;
        p->moveCnt += 3;
    }

    void MakeHeap(itemType a[], int Root, int LastNode, complexity *p) {

        int Parent, LeftSon, RightSon, Son;
        itemType RootValue;

        Parent = Root;
        RootValue = a[Root];
        p->moveCnt++;

        LeftSon = 2 * Parent + 1;
        RightSon = LeftSon + 1;

        while (LeftSon <= LastNode) {
            //자식 노드끼리 비교
            p->compCnt++;

            if (RightSon <= LastNode && a[LeftSon] < a[RightSon])
                Son = RightSon;

            else
                Son = LeftSon;
            // root 노드와 비교
            p->compCnt++;

            if (RootValue < a[Son]) {
                a[Parent] = a[Son];
                p->moveCnt++;

                Parent = Son;
                LeftSon = Parent * 2 + 1;
                RightSon = LeftSon + 1;
            }
            else
                break;
        }

        a[Parent] = RootValue;
        p->moveCnt++;
    }

    void heapsort(itemType a[], int N, complexity *p) {
        int i;
        p->compCnt=0;
        p->moveCnt=0;
        for (i = N / 2; i >= 1; i--)
            MakeHeap(a, i - 1, N - 1, p);

        for (i = N - 1; i >= 1; i--) {
            swap(a, 0, i, p);
            MakeHeap(a, 0, i - 1, p);
        }
    }
};

int main() {
    int N;
    cin >> N;

    itemType* A = new itemType[N];
    itemType* B = new itemType[N];
    itemType* C = new itemType[N];

    makeA(A, N);
    makeB(B, N);
    makeC(C, N);
    complexity cplxA,cplxB,cplxC;

    MAKE_HEAP heap(N);
    heap.heapsort(A, N, &cplxA); // 배열 A heapsort
    heap.heapsort(B, N, &cplxB); // 배열 B heapsort
    heap.heapsort(C, N, &cplxC); // 배열 C heapsort

    // 결과 출력
    cout << "SortedData_A : ";
    printArray(A);
    cout << "SortedData_B : ";
    printArray(B);
    cout << "SortedData_C : ";
    printArray(C);

    cout << "Compare_Cnt_A " << cplxA.compCnt << ", DataMove_Cnt_A " << cplxA.moveCnt << endl;
    cout << "Compare_Cnt_B " << cplxB.compCnt << ", DataMove_Cnt_B " << cplxB.moveCnt << endl;
    cout << "Compare_Cnt_C " << cplxC.compCnt << ", DataMove_Cnt_C " << cplxC.moveCnt << endl;

//    FILE* fwp = fopen("result_1.txt", "w");
//    for (int i = 0; i <= N; i += 500) {
//        makeA(A, i);
//        heap.heapsort(A, i, &cplxA);
//        fprintf(fwp, "%d\t%d\n", i, cplxA.moveCnt);
//    }
//    fclose(fwp);

    return 0;
}

void makeA(itemType* A, int N) {
    // 데이터 배열 A 생성
    A[0]=0; //dummy
    for (int i = 0; i < N; i++) { // N, N-1, ..., 1
        A[i] = N - i;
    }
}

void makeB(itemType* B, int N) {
    // 데이터 배열 B 생성
    B[0] = 0;
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
        B[i] = a[i+1][1];
    }
    for (int i = 0; i < N; i++) delete[] a[i];
    delete[] a;
}

void makeC(itemType* C, int N){
    // 데이터 배열 C 생성
    for(int i=0; i<N; i++)
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
    for (int i = 0; i < 20; i++)
        cout << a[i] << " ";
    cout<<endl;
}
