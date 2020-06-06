#include <iostream>

using namespace std;

typedef double itemType; // 나눗셈 연산을 위해 double로 정의
class Stack2
{
public:
	Stack2() {  // head와 z(tail) 선언
		head = new node;
		z = new node;
		head->next = z; // 스택이 비어있는 초기상태 
	}

	~Stack2() { // 소멸자
		delete(head);
		delete(z);
	}

	// 새 노드 p를 생성하여 key값에 v를 넣고
	// head와 연결하여 스택을 구성
	void push(itemType v) { 
		struct node* p = new node;
		p->key = v;
		p->next = head->next;
		head->next = p;
	}

	// head를 이용하여 스택의 가장 윗값(마지막에 push된 값)을
	// 반환하고 노드를 삭제 (head->next = head->next->next)
	itemType pop() {
		itemType temp = head->next->key; 
		head->next = head->next->next;
		return  temp;
	}

	int empty() { // stack이 비어있으면 1반환 아니면 0반환
		return (head->next == z);
	}

private:
	struct node
	{
		itemType key; struct node* next;
	};
	struct node* head, * z;
};

// 소수점 이하 값이 있는지 판별하는 함수
bool isDec(double d) {
	if (d == (int)d) return false; // 소수점 이하 값이 없음
	else return true;
}

int main() {
	char c; Stack2 acc; itemType x, temp;
	while ((c = cin.get()) != '\n')
	{
		x = 0;
		while (c == ' ') cin.get(c);
		if (c == '+') x = acc.pop() + acc.pop();
		if (c == '*') x = acc.pop() * acc.pop();
		// 뺄셈과 나눗셈은 교환법칙이 성립되지 않으므로 처리
		if (c == '-') {
			temp = acc.pop();
			x = acc.pop() - temp;
		}
		if (c == '/') {
			temp = acc.pop();
			x = acc.pop() / temp;
		}
		while (c >= '0' && c <= '9')
		{
			x = 10 * x + (c - (double)'0');  cin.get(c); // 아스키코드 값을 빼는 과정에서 overflow 경고를 해결하기 위해 dobule형변환
		}
		acc.push(x);
	}
	x = acc.pop();
	if (isDec(x)) { // 소수점 이하 값이 있을 경우 소수점 둘째 자리까지 출력
		cout << fixed;
		cout.precision(2);
		cout << x << '\n';
	}
	else
		cout << x << '\n';	
}
