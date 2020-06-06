#include <iostream>
#include <random>
#include <time.h>
#include <stdio.h>
#include <vector>

#define MAX_NUM 55 // ������ ���� ����� ���� ������ MAX�� ����

using namespace std;

class Set {
private:
	vector<int> numSet; // ������ ������ vector �������
	int setSize; // ������ ũ�⸦ ������ int �������
public:
	Set(int size = 10) {  // �������� �Ű������� ������ size�� ���
		setSize = size;	  // �ش� ũ�⸸ŭ�� ���� ���� ���� ����
		numSet.resize(size);
		MakeRandomSet(); 
	}
	Set(vector<int> v) {    // �������� �Ű������� vector�� ���
		setSize = v.size(); // �ش� vector�� ���� ����
		numSet = v;
	}	

	void MakeRandomSet() { // ���� ���� ���� �޼ҵ�
		int flag = 0; // ���� �� ������ �ߺ� �Ǻ� ���� flag
		for (int i = 0; i < setSize; i++) {
			numSet[i] = rand() % MAX_NUM + 1; // ���� ����
			for (int j = 0; j < i; j++) { // ������ ������ �ߺ��� �� ���� üũ
				if (numSet[i] == numSet[j]) {
					flag = 1;
					break;
				}
			}
			if (flag == 1) { // ������ ������ �ߺ��� �� �϶�
				i--;
				flag = 0;
				continue;
			}
		}
		sort(numSet.begin(), numSet.end()); // �������� ����
	}

	// �����հ� �������� ���ϴ� �޼ҵ�
	vector<vector<int>> OperSet(Set B) { 
		int ixA = 0, ixB = 0; //���� A��B�� �ε��� ����
		vector<int> unionSet; // �������� ������ vector
		vector<int> interSectionSet; // �������� ������ vector

		while (ixA < setSize || ixB < B.setSize) { // �� ������ �ε����� ��� ������ �����ϸ� �ݺ��� ����
			if (ixA == setSize) {				// ���� A�� �ε����� ������ ����������
				unionSet.push_back(B.numSet[ixB++]); // ���� B�� ���� ���Ҹ� ��� unionSet�� ����
				continue;
			}
			if (ixB == B.setSize) {				// ���� B�� �ε����� ������ ����������
				unionSet.push_back(numSet[ixA++]); // ���� A�� ���� ���Ҹ� ��� unionSet�� ����
				continue;
			}
			// �� ������ ���Ҹ� ���Ͽ� ���� ���Ҹ� unionSet�� �����ϰ�
			// �ش� ������ �ε����� 1 ����
			if (numSet[ixA] < B.numSet[ixB]) 
				unionSet.push_back(numSet[ixA++]);
			else if (numSet[ixA] > B.numSet[ixB]) 
				unionSet.push_back(B.numSet[ixB++]);
			// �� ������ ���Ұ� ���� ��� interSectionSet�� unionSet�� �����ϰ�
			// �� ������ �ε��� ��� 1�� ����
			else {
				unionSet.push_back(numSet[ixA++]);
				interSectionSet.push_back(B.numSet[ixB++]);
			}				
		}
		vector<vector<int>> res = { unionSet,interSectionSet };
		return res;
	}

	// ���� ��� �޼ҵ�
	void PrintSet() {
		for (int i = 0; i < setSize; i++) {
			if (i == setSize - 1)
				cout << numSet[i];
			else
				cout << numSet[i] << ", ";
		}
		cout << "\n";
	}

};

int main() {
	int N, M;
	cout << "�� ���� �ڿ����� �Է��ϼ��� : ";
	cin >> N >> M;
	srand((unsigned int)time(NULL));
	Set A(N); // N���� �ڿ��� ���� A
	Set B(M); // M���� �ڿ��� ���� B
	vector<vector<int>> v = A.OperSet(B); // A�� B�� �����հ� �������� 2���� vector v�� ����([0]=������, [1]=������)

	Set C(v[0]); // ������
	Set D(v[1]); // ������

	// ���� A ���
	cout << "���� A - ";
	A.PrintSet();
	// ���� B ���
	cout << "���� B - ";
	B.PrintSet();

	// ���� A�� B�� ������ ���
	cout << "������ - ";
	C.PrintSet();
	
	// ���� A�� B�� ������ ���
	cout << "������ - ";
	D.PrintSet();	
}