#include <iostream>

using namespace std;

typedef int itemType;
class Stack1
{
private:
	itemType* stack;
	int p;
public:
	Stack1(int max = 100) // Stack1의 생성자(매개변수의 기본값은 100)
	{
		stack = new itemType[max]; // max값에 따라 stack을 할당.
		p = 0; // index로 쓰일 변수 p 초기화
	}
	~Stack1() // Stack1의 소멸자
	{
		delete stack;
	}
	inline void push(itemType v) // push 메소드
	{
		stack[p++] = v;
	}
	inline itemType pop() // pop 메소드
	{
		return stack[--p];
	}
	inline int empty() // p가 0이면 stack이 비어있음
	{
		return !p;
	}
};

int main() {
	char c; Stack1 acc(50); int x;
	while ((c = cin.get()) != '\n')
	{
		x = 0;
		while (c == ' ') cin.get(c);
		if (c == '+') x = acc.pop() + acc.pop();
		if (c == '*') x = acc.pop() * acc.pop();
		while (c >= '0' && c <= '9')
		{
			x = 10 * x + (c - '0');  cin.get(c); //아스키코드 값을 이용한 형변환
		}
		acc.push(x);
	}
	cout << acc.pop() << '\n';
}