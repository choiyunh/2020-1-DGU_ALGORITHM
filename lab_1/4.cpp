#include <iostream>
#include <random>
#include <time.h>
#include <stdio.h>
#include <vector>

#define MAX_NUM 55 // 적절한 예제 출력을 위해 원소의 MAX값 정의

using namespace std;

class Set {
private:
	vector<int> numSet; // 집합을 저장할 vector 멤버변수
	int setSize; // 집합의 크기를 저장할 int 멤버변수
public:
	Set(int size = 10) {  // 생성자의 매개변수가 정수형 size일 경우
		setSize = size;	  // 해당 크기만큼의 랜덤 원소 집합 생성
		numSet.resize(size);
		MakeRandomSet(); 
	}
	Set(vector<int> v) {    // 생성자의 매개변수가 vector일 경우
		setSize = v.size(); // 해당 vector로 집합 생성
		numSet = v;
	}	

	void MakeRandomSet() { // 랜덤 집합 생성 메소드
		int flag = 0; // 집합 내 원소의 중복 판별 위한 flag
		for (int i = 0; i < setSize; i++) {
			numSet[i] = rand() % MAX_NUM + 1; // 난수 생성
			for (int j = 0; j < i; j++) { // 생성된 난수가 중복된 수 인지 체크
				if (numSet[i] == numSet[j]) {
					flag = 1;
					break;
				}
			}
			if (flag == 1) { // 생성된 난수가 중복된 수 일때
				i--;
				flag = 0;
				continue;
			}
		}
		sort(numSet.begin(), numSet.end()); // 오름차순 정렬
	}

	// 합집합과 교집합을 구하는 메소드
	vector<vector<int>> OperSet(Set B) { 
		int ixA = 0, ixB = 0; //집합 A와B의 인덱스 변수
		vector<int> unionSet; // 합집합을 저장할 vector
		vector<int> interSectionSet; // 교집합을 저장할 vector

		while (ixA < setSize || ixB < B.setSize) { // 두 집합의 인덱스가 모두 끝까지 도달하면 반복문 종료
			if (ixA == setSize) {				// 집합 A의 인덱스만 끝까지 도달했으면
				unionSet.push_back(B.numSet[ixB++]); // 집합 B의 남은 원소를 모두 unionSet에 저장
				continue;
			}
			if (ixB == B.setSize) {				// 집합 B의 인덱스만 끝까지 도달했으면
				unionSet.push_back(numSet[ixA++]); // 집합 A의 남은 원소를 모두 unionSet에 저장
				continue;
			}
			// 두 집합의 원소를 비교하여 작은 원소를 unionSet에 저장하고
			// 해당 집합의 인덱스만 1 증가
			if (numSet[ixA] < B.numSet[ixB]) 
				unionSet.push_back(numSet[ixA++]);
			else if (numSet[ixA] > B.numSet[ixB]) 
				unionSet.push_back(B.numSet[ixB++]);
			// 두 집합의 원소가 같은 경우 interSectionSet과 unionSet에 저장하고
			// 두 집합의 인덱스 모두 1씩 증가
			else {
				unionSet.push_back(numSet[ixA++]);
				interSectionSet.push_back(B.numSet[ixB++]);
			}				
		}
		vector<vector<int>> res = { unionSet,interSectionSet };
		return res;
	}

	// 집합 출력 메소드
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
	cout << "두 개의 자연수를 입력하세요 : ";
	cin >> N >> M;
	srand((unsigned int)time(NULL));
	Set A(N); // N개의 자연수 집합 A
	Set B(M); // M개의 자연수 집합 B
	vector<vector<int>> v = A.OperSet(B); // A와 B의 합집합과 교집합을 2차원 vector v에 저장([0]=합집합, [1]=교집합)

	Set C(v[0]); // 합집합
	Set D(v[1]); // 교집합

	// 집합 A 출력
	cout << "집합 A - ";
	A.PrintSet();
	// 집합 B 출력
	cout << "집합 B - ";
	B.PrintSet();

	// 집합 A와 B의 합집합 출력
	cout << "합집합 - ";
	C.PrintSet();
	
	// 집합 A와 B의 교집합 출력
	cout << "교집합 - ";
	D.PrintSet();	
}