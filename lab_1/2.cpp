#include <iostream>

using namespace std;

typedef int itemType;
class Stack1
{
private:
	itemType* stack;
	int p;
public:
	Stack1(int max = 100) // Stack1�� ������(�Ű������� �⺻���� 100)
	{
		stack = new itemType[max]; // max���� ���� stack�� �Ҵ�.
		p = 0; // index�� ���� ���� p �ʱ�ȭ
	}
	~Stack1() // Stack1�� �Ҹ���
	{
		delete stack;
	}
	inline void push(itemType v) // push �޼ҵ�
	{
		stack[p++] = v;
	}
	inline itemType pop() // pop �޼ҵ�
	{
		return stack[--p];
	}
	inline int empty() // p�� 0�̸� stack�� �������
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
			x = 10 * x + (c - '0');  cin.get(c); //�ƽ�Ű�ڵ� ���� �̿��� ����ȯ
		}
		acc.push(x);
	}
	cout << acc.pop() << '\n';
}