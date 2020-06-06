#include <iostream>
#include <time.h>

using namespace std;
typedef int itemType;

int resultBubble = 0;
int resultInsertion = 0;
int resultShell = 0;

void insertion(itemType a[], int n);
void shellSort(itemType a[], int n);
int Bubble(int sorted, itemType* a, int n);
void bubbleSort(itemType a[], int n);

int main() {
	int N;
	cin >> N;

	itemType* A = new itemType[N + 1];

	// 데이터 배열 A 생성
	A[0] = -1; // 삽입정렬 위한 dummy data
	for (int i = 1; i <= N; i++) {
		A[i] = N - i + 1;
	}

	insertion(A, N);
	cout << "Insertion Sort : " << resultInsertion << endl;

	for (int i = 0; i < N; i++) {
		A[i] = N - i;
	}
	bubbleSort(A, N);
	cout << "Bubble Sort : " << resultBubble << endl;

	for (int i = 0; i <N; i++) {
		A[i] = N - i;
	}
	shellSort(A, N);
	cout << "Shell Sort : " << resultShell << endl;
}

int Bubble(int sorted, itemType* a, int n) {
	int temp;
	if (*(a - 1) > * a) {
		temp = *a;
		*a = *(a - 1);
		*(a - 1) = temp;
		resultBubble += (temp * 2 + *(a));
		sorted = false;
	}
	return sorted;
}

void bubbleSort(itemType a[], int n) {
	int i, Sorted;
	Sorted = false;
	while (!Sorted) {
		Sorted = true;
		for (i = 1; i < n; i++) {
			Sorted = Bubble(Sorted, &a[i], n);
		}
	}
}

void shellSort(itemType a[], int n) {
	int i, j, h;
	itemType v;
	h = 1;
	do {
		h = 3 * h + 1;
	} while (h < n);
	do {
		h = h / 3;
		for (i = h; i < n; i++) {
			v = a[i];
			j = i;
			while (a[j - h] > v) {
				a[j] = a[j - h];
				resultShell += a[j - h];
				j -= h;
				if (j <= h - 1) break;
			}
			a[j] = v;
			resultShell += 2 * v;
		}
	} while (h > 1);
}

void insertion(itemType a[], int n) {
	int i, j;
	itemType v;
	for (i = 2; i <= n; i++) {
		v = a[i];
		j = i;
		while (a[j - 1] > v) {
			a[j] = a[j - 1];
			resultInsertion += a[j - 1];
			j--;
		}
		a[j] = v;
		resultInsertion += 2 * v;
	}
}