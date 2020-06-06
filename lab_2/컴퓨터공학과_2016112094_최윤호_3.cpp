#include <iostream>

using namespace std;

struct treeNode { char info; struct treeNode* l, * r; int level; }; // Ʈ�� ������ ���� ����ü ����(��� level �߰�)
struct treeNode* x, * z;
void traverse(struct treeNode* t, char alpha); // Ʈ�� ��ȸ�� ���� �Լ� ����(������ȸ���)
typedef treeNode* itemType;
// Ʈ�� ���� �� ���� ����� ���� Stack Ŭ����
class Stack
{
public:
	Stack(int max = 100) { stack = new itemType[max]; p = 0; };
	~Stack() { delete stack; };

	inline void push(itemType v) { stack[p++] = v; }
	inline itemType pop() { return stack[--p]; }
	inline int empty() { return !p; }
private:
	itemType* stack;
	int p;
};

// ���� ��ȸ�� ���� Queue Ŭ����
class Queue {
public:
	Queue(int max = 100) {
		size = max;
		queue = new itemType[size];
		head = 0;
		tail = 0;
	}
	~Queue() {
		delete queue;
	}
	// Queue Ŭ���� �޼ҵ� �����-//
	void put(itemType);
	itemType get();
	inline int empty();
	// ---------------------------//
private:
	itemType* queue;
	int head, tail, size;

};
// Queue Ŭ���� �޼ҵ� ���Ǻ� --------------- //
void Queue::put(itemType v)
{
	queue[tail++] = v;
	if (tail > size) tail = 0;
}
itemType Queue::get()
{
	itemType t = queue[head++];
	if (head > size) head = 0;
	return t;
}
int Queue::empty() { return head == tail; }
// ------------------------------------------ //

int main()
{
	char c; Stack stack(50);
	z = new treeNode; z->l = z; z->r = z;
	while ((c = cin.get()) != '\n')
	{
		while (c == ' ') cin.get(c);
		x = new treeNode;
		x->info = c; x->l = z; x->r = z;
		if (c == '+' || c == '*' || c == '-') { x->r = stack.pop(); x->l = stack.pop(); }
		stack.push(x);
	}
	cin >> c; // ã���� �ϴ� �ǿ����� �Է�
	traverse(stack.pop(), c);
	cout << endl;
	return 0;
}

// ���� ��ȸ
void traverse(struct treeNode* t, char alpha) {
	Queue queue(50);
	int flag = 0; // Not found ���� flag
	t->level = 1; // root ����� ������ 1
	queue.put(t); // root ��带 ť�� ����
	while (!queue.empty()) {
		t = queue.get();

		// �ڽ�(���� ����)���� ť�� �����ϸ� �ǿ����� Ž��
		// ����, ������ �ڽ� ����� ���� �ǿ����ڿ� ������
		// �ش� level�� ����ϰ� break;
		if (t->l != z) {
			t->l->level = t->level + 1; // ���� +1
			if (t->l->info == alpha) {  
				cout << t->l->level << endl; 
				flag = 1;
				break;
			}
			queue.put(t->l);
		}
		if (t->r != z) {
			t->r->level = t->level + 1; // ���� +1
			if (t->r->info == alpha) { 
				cout << t->r->level << endl; 
				flag = 1;
				break;
			}
			queue.put(t->r);
		}
	}
	// ���ڸ� ���� Ʈ������ ã�� ������ ��
	if (flag == 0)
		cout << "Not found" << endl;
}