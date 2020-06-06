#include <iostream>
#include <time.h>

using namespace std;
typedef int itemType;

struct complexity {
	int compCnt = 0;
	int moveCnt = 0;
};

complexity insertion(itemType a[], int);
void sort(itemType* a[], int);
void printArray(int*);
void makeA(itemType*, int);
void makeB(itemType*, int);

int main() {
	int N;
	cin >> N;

	itemType* A = new itemType[N + 1];
	itemType* B = new itemType[N + 1];

	makeA(A, N);
	makeB(B, N);

	complexity comA, comB;
	comA = insertion(A, N);
	comB = insertion(B, N);

	cout << "SortedData_A : ";
	printArray(A);
	cout << endl;
	cout << "SortedData_B : ";
	printArray(B);	
	
	cout << endl;
	cout << "Compare_Cnt_A " << comA.compCnt << ", DataMove_Cnt_A " << comA.moveCnt << endl;	
	cout << "Compare_Cnt_B " << comB.compCnt << ", DataMove_Cnt_B " << comB.moveCnt << endl;
		
	FILE* fwp = fopen("result_1.txt", "w");
	for (int i = 0; i <= N; i+=500) {
		makeA(A, i);
		comA = insertion(A, i);
		fprintf(fwp, "%d\t%d\n", i, comA.moveCnt);
	}
	fclose(fwp);
}

complexity insertion(itemType a[], int n) {
	int i, j; itemType v;
	complexity temp;
	for (i = 2; i <= n; i++) {
		temp.moveCnt++;
		v = a[i];		
		j = i;
		while (a[j - 1] > v) {
			temp.compCnt++;
			temp.moveCnt++;
			a[j] = a[j - 1];
			j--;
		}
		a[j] = v;
		temp.moveCnt++;
	}
	return temp;
}

void makeA(itemType* A, int N) {
	// 데이터 배열 A 생성
	A[0] = INT_MIN; // 삽입정렬 위한 dummy data
	for (int i = 1; i <= N; i++) {
		A[i] = N - i + 1;
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
	for (int i = 1; i <= N; i++) {
		B[i] = a[i][1];
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
	for (int i = 1; i <= 20; i++)
		cout << a[i] << " ";
}