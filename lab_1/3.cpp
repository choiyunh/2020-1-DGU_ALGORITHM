#include <iostream>

using namespace std;

typedef double itemType; // ������ ������ ���� double�� ����
class Stack2
{
public:
	Stack2() {  // head�� z(tail) ����
		head = new node;
		z = new node;
		head->next = z; // ������ ����ִ� �ʱ���� 
	}

	~Stack2() { // �Ҹ���
		delete(head);
		delete(z);
	}

	// �� ��� p�� �����Ͽ� key���� v�� �ְ�
	// head�� �����Ͽ� ������ ����
	void push(itemType v) { 
		struct node* p = new node;
		p->key = v;
		p->next = head->next;
		head->next = p;
	}

	// head�� �̿��Ͽ� ������ ���� ����(�������� push�� ��)��
	// ��ȯ�ϰ� ��带 ���� (head->next = head->next->next)
	itemType pop() {
		itemType temp = head->next->key; 
		head->next = head->next->next;
		return  temp;
	}

	int empty() { // stack�� ��������� 1��ȯ �ƴϸ� 0��ȯ
		return (head->next == z);
	}

private:
	struct node
	{
		itemType key; struct node* next;
	};
	struct node* head, * z;
};

// �Ҽ��� ���� ���� �ִ��� �Ǻ��ϴ� �Լ�
bool isDec(double d) {
	if (d == (int)d) return false; // �Ҽ��� ���� ���� ����
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
		// ������ �������� ��ȯ��Ģ�� �������� �����Ƿ� ó��
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
			x = 10 * x + (c - (double)'0');  cin.get(c); // �ƽ�Ű�ڵ� ���� ���� �������� overflow ��� �ذ��ϱ� ���� dobule����ȯ
		}
		acc.push(x);
	}
	x = acc.pop();
	if (isDec(x)) { // �Ҽ��� ���� ���� ���� ��� �Ҽ��� ��° �ڸ����� ���
		cout << fixed;
		cout.precision(2);
		cout << x << '\n';
	}
	else
		cout << x << '\n';	
}
