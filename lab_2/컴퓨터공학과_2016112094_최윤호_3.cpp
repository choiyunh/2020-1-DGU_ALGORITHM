#include <iostream>

using namespace std;

struct treeNode { char info; struct treeNode* l, * r; int level; }; // 트리 생성을 위한 구조체 정의(멤버 level 추가)
struct treeNode* x, * z;
void traverse(struct treeNode* t, char alpha); // 트리 순회를 위한 함수 선언(중위순회방식)
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
	cin >> c; // 찾고자 하는 피연산자 입력
	traverse(stack.pop(), c);
	cout << endl;
	return 0;
}

// 레벨 순회
void traverse(struct treeNode* t, char alpha) {
	Queue queue(50);
	int flag = 0; // Not found 위한 flag
	t->level = 1; // root 노드의 레벨은 1
	queue.put(t); // root 노드를 큐에 삽입
	while (!queue.empty()) {
		t = queue.get();

		// 자식(다음 레벨)들을 큐에 삽입하며 피연산자 탐색
		// 왼쪽, 오른쪽 자식 노드의 값이 피연산자와 같으면
		// 해당 level을 출력하고 break;
		if (t->l != z) {
			t->l->level = t->level + 1; // 레벨 +1
			if (t->l->info == alpha) {  
				cout << t->l->level << endl; 
				flag = 1;
				break;
			}
			queue.put(t->l);
		}
		if (t->r != z) {
			t->r->level = t->level + 1; // 레벨 +1
			if (t->r->info == alpha) { 
				cout << t->r->level << endl; 
				flag = 1;
				break;
			}
			queue.put(t->r);
		}
	}
	// 문자를 수식 트리에서 찾지 못했을 때
	if (flag == 0)
		cout << "Not found" << endl;
}