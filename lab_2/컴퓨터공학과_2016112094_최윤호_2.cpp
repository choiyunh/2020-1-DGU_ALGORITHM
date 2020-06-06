#include <iostream>

using namespace std;

struct treeNode { char info; struct treeNode* l, * r; }; // 트리 생성을 위한 구조체 정의
struct treeNode* x, * z;
void visit(struct treeNode* t); // 트리 순회 시 값 출력 함수 선언
void traverse(struct treeNode* t); // 트리 순회를 위한 함수 선언(중위순회방식)

typedef treeNode* itemType;
// 트리 생성 시 스택 사용을 위한 Stack 클래스
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

// 레벨 순회를 위한 Queue 클래스
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
	// Queue 클래스 메소드 선언부-//
	void put(itemType); 
	itemType get();
	inline int empty();
	// ---------------------------//
private:
	itemType* queue;
	int head, tail, size;

};
// Queue 클래스 메소드 정의부 --------------- //
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
	traverse(stack.pop());
	cout << endl;
	return 0;
}
// 노드 값 출력
void visit(struct treeNode* t) {
	cout << t->info << " ";
}
// 레벨 순회
void traverse(struct treeNode* t) {
	Queue queue(50);
	queue.put(t); // root 노드를 큐에 삽입
	while (!queue.empty())
	{
		t = queue.get(); visit(t); // 부모 노드부터 순회
		// 자식(다음 레벨)들을 큐에 삽입
		if (t->l != z) queue.put(t->l);
		if (t->r != z) queue.put(t->r);
	}
}