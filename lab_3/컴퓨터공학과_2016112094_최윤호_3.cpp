#include <iostream>
#include <time.h>

using namespace std;
typedef int itemType;

struct complexity {
	int compCnt = 0;
	int moveCnt = 0;
};

int Bubble(int sorted, itemType* a, int n, complexity* p);
complexity bubbleSort(itemType a[], int n);
void sort(itemType* a[], int);
void printArray(itemType*);
void makeA(itemType*, int);
void makeB(itemType*, int);

int main() {
	int N;
	cin >> N;

	itemType* A = new itemType[N];
	itemType* B = new itemType[N];

	makeA(A, N);
	makeB(B, N);

	complexity comA, comB;
	comA = bubbleSort(A, N);
	comB = bubbleSort(B, N);

	cout << "SortedData_A : ";
	printArray(A);
	cout << endl;
	cout << "SortedData_B : ";
	printArray(B);

	cout << endl;
	cout << "Compare_Cnt_A " << comA.compCnt << ", DataMove_Cnt_A " << comA.moveCnt << endl;
	cout << "Compare_Cnt_B " << comB.compCnt << ", DataMove_Cnt_B " << comB.moveCnt << endl;

	FILE* fwp = fopen("result_3.txt", "w");
	for (int i = 0; i <= N; i += 500) {
		makeA(A, i);
		comA = bubbleSort(A, i);
		fprintf(fwp, "%d\t%d\n", i, comA.moveCnt);
	}
	fclose(fwp);
}

int Bubble(int sorted, itemType* a, int n, complexity *p) {
	int temp;
	if (*(a - 1) > * a) {
		p->compCnt++;
		p->moveCnt++;
		temp = *(a - 1);

		*(a - 1) = *a;
		p->moveCnt++;

		*a = temp;
		p->moveCnt++;

		sorted = false;
	}
	return sorted;
}

complexity bubbleSort(itemType a[], int n) {
	int i, Sorted;
	complexity temp;

	Sorted = false;
	while (!Sorted) {
		Sorted = true;
		for (i = 1; i < n; i++) {
			Sorted = Bubble(Sorted, &a[i], n, &temp);
		}
	}
	return temp;
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