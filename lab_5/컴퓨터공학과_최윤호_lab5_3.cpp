//
// Created by YunHo on 2020/05/20.
// Lab #05 Q3
//

#include <iostream>
#include <vector>

typedef int itemType;
using namespace std;

// 비교 및 이동 횟수 카운트를 위한 구조체 정의
struct complexity {
    int compCnt = 0;
    int moveCnt = 0;
};

typedef struct node *node_pointer;
typedef struct node{
    itemType value;
    node_pointer next;
};
node_pointer TABLE[10],x,z,temp;

void radixSort(itemType *a, int n, complexity *p);
void sort(itemType* a[], int);
void printArray(itemType*);
void makeA(itemType*, int);
void makeB(itemType*, int);
void makeC(itemType*, int);

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

    radixSort(A, N, &cplxA);
    radixSort(B, N, &cplxB);
    radixSort(C, N, &cplxC);

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

//    FILE* fwp = fopen("result_3.txt", "w");
//    for (int i = 0; i <= N; i += 500) {
//        makeA(A, i);
//        radixSort(A, i, &cplxA);
//        fprintf(fwp, "%d\t%d\n", i, cplxA.moveCnt);
//    }
//    fclose(fwp);

    return 0;
}

void radixSort(itemType *a, int n, complexity *p){
    p->compCnt=0; p->moveCnt=0;
    int i,j,cnt,radix, radix_mod=10,cipher=0;
    i = n;
    while(i > 0){i = i/10; cipher++;} // cipher : 입력 데이터의 자리수 (ex. 450 -> 3)
    for(i=0;i<cipher;i++){
        for(j=0;j<n;j++){
            cnt = 0; radix = (a[j]%radix_mod)/(radix_mod/10);
            /* radix_mod = 10 이면 radix는 a[j]의 일의 자리수
            radix_mod = 100 이면 radix는 a[j]의 십의 자리수 */
            temp = new node; temp -> value = a[j]; temp -> next =z;
            p->moveCnt++;
            if(TABLE[radix] == z){
                // z는 list의 끝을 확인하기 위한 노드 포인터 (NULL에 해당)
                TABLE[radix] = temp;
                p->moveCnt++;
            }
            else{
                x = TABLE[radix];
                p->moveCnt++;
                while(x->next!=z){
                    x = x->next;
                }
                x->next = temp;
                p->moveCnt++;
            }
        }

        for(j=0;j<10;j++){
            if(TABLE[j]!=z){
                x = TABLE[j];
                p->moveCnt++;
                while(x!=z){
                    a[cnt++] = x->value;
                    p->moveCnt++;
                    temp = x; // 메모리에서 노드를 삭제하기 위해 임시저장
                    x = x->next;
                    delete temp;
                }
            }
            TABLE[j] = z;
        }
        radix_mod*=10;
    }
}

void makeA(itemType* A, int N) {
    // 데이터 배열 A 생성
    for (int i = 0; i < N; i++) { // N, N-1, ..., 1
        A[i] = N - i;
    }
}

void makeB(itemType* B, int N) {
    // 데이터 배열 B 생성
    //B[0] = 0;
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
    for(int i=0; i<N;i++)
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