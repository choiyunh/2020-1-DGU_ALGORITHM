#include <iostream>

using namespace std;

struct treeNode { char info; struct treeNode* l, * r; }; // 트리 생성을 위한 구조체 정의
struct treeNode* x, * z;
void visit(struct treeNode* t); // 트리 순회 시 값 출력
void traverse(struct treeNode* t); // 트리 순회를 위한 함수(중위순회방식)

typedef treeNode* itemType;
// 트리 생성 시 스택 사용을 위한 클래스
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
// 중위 순회(왼쪽자식->부모->오른쪽자식)
void traverse(struct treeNode* t) {
	if (t != z) {
		traverse(t->l);
		visit(t);
		traverse(t->r);
	}
} 