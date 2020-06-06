//
// Created by YunHo on 2020/05/25.
//

#include <iostream>
#include <vector>

#define infoNIL 0
#define itemMIN -1

typedef int itemType;
typedef int infoType;

using namespace std;

class BST{
private:
    struct node{
        itemType key; infoType info;
        struct node *l, *r;
        node(itemType k, infoType i, struct node *ll, struct node *rr)
        { key = k; info = i; l = ll; r = rr; };
    };
    struct node *head, *z;
public:
    BST(int max){
        z = new node(0,infoNIL,0,0);
        head = new node(itemMIN,infoNIL,z,z);
    }
    ~BST(){};
    infoType BSTsearch(itemType v);
    void BSTinsert(itemType v, infoType info);
    void BSTdelete(itemType v);
};

infoType BST::BSTsearch(itemType v) {
    struct node *x = head->r;
    z->key = v;
    while(v != x->key) x = (v < x->key) ? x->l:x->r;
    return x->info;
}

void BST::BSTinsert(itemType v, infoType info) {
    struct node *p, *x;
    p = head; x = head->r;
    while(x!=z){
        p = x;
        x = (v<x->key) ? x->l : x->r;
        info++;
    }
    x = new node(v,info,z,z);
    x->info++;
    if(v<p->key) p->l = x; else p->r = x;
}

int main() {
    int size; cin >> size;
    int *a = new int[size];

    srand((unsigned)time(NULL));
    vector<pair<int,int>> v;
    for(int i=0; i<size;i++){
        v.push_back(pair<int,int>(rand()%size+1,i+1));
    }
    sort(v.begin(), v.end());
    for(int i=0;i<size;i++) a[i] = v[i].second;

    BST bst = BST(size);
    for(int i=0;i<size;i++) bst.BSTinsert(a[i],infoNIL);
    int count=infoNIL;
    for(int i=1;i<=size;i++) count+=bst.BSTsearch(i);

    cout << (double)count/(double)size << "(T1의 평균 비교 횟수)"<<endl;

    return 0;
}
