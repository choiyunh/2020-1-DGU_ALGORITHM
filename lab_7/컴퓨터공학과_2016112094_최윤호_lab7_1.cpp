//
// Created by YunHo on 2020/05/31.
//

#include <iostream>
#include <time.h>

using namespace std;

typedef int itemType;
typedef int infoType;

#define infoNIL 0
#define itemMIN -1
#define black 0
#define red 1

struct node {
    itemType key, tag;
    infoType info;
    struct node *l, *r;

    node(itemType k, infoType i, struct node *ll, struct node *rr) {

        key = k;
        info = i;
        l = ll; r = rr;
    }

    node(itemType k, infoType i, itemType t, struct node *ll, struct node *rr) {
        key = k;
        info = i;
        tag = t;
        l = ll;
        r = rr;
    }
};

struct node *head, *tail, *x, *p, *g, *gg, *z, *_z;
struct node *T1, *T2, *T3;
int cmp_build1, cmp_build2, cmp_build3;

void RBtree(int max);
void split(itemType k, int &cmp);
struct node *rotate(itemType k, struct node *y, int &cmp);
void insert(struct node *T3, itemType k, infoType info, int &cmp);
infoType search(struct node *T3, itemType k);


void RBtree(int max) {

    z = new node(0, infoNIL, black, 0, 0);
    z->l = z;
    z->r = z;

    _z = new node(0, infoNIL, 0, 0);
    _z->l = _z;
    _z->r = _z;

    T1 = new node(itemMIN, infoNIL, _z, _z);
    T2 = new node(itemMIN, infoNIL, _z, _z);
    T3 = new node(itemMIN, infoNIL, black, z, z);
}

void insert(struct node *T3, itemType k, infoType info, int &cmp) {

    x = T3;
    p = T3;
    g = T3;

    while (x != z) {
        gg = g;
        g = p;
        p = x;
        x = (k < x->key) ? x->l : x->r;
        cmp++;

        if (x->l->tag && x->r->tag)
            split(k, cmp);
    }

    x = new node(k, info, red, z, z);

    if (k < p->key) p->l = x;
    else         p->r = x;
    cmp++;

    split(k, cmp);
    T3->r->tag = black;
}

struct node *rotate(itemType k, struct node *y, int &cmp) {

    struct node *high, *low;

    high = (k< y->key) ? y->l : y->r;
    cmp++;

    if (k < high->key) {
        low = high->l;
        high->l = low->r;
        low->r = high;
    }

    else {
        low = high->r;
        high->r = low->l;
        low->l = high;
    }

    cmp++;

    if (k < y->key) y->l = low;
    else         y->r = low;

    return low;
}

void split(itemType k, int &cmp) {

    x->tag = red;
    x->l->tag = black;
    x->r->tag = black;

    if (p->tag) {

        cmp++;
        g->tag = red;

        if (k < g->key != k < p->key)
            p = rotate(k, g, cmp);

        x = rotate(k, gg, cmp);
        x->tag = black;
    }
}

infoType search(struct node *T3, itemType k) {

    struct node *x = T3->r;

    int count = 0;

    while (k != x->key)  {
        x = (k < x->key) ? x->l : x->r;
        count++;
    }

    x->info = count;
    return x->info;
}

void initArray(int *ary, int N);
void init_array(int **temp, int *ary, int N);
void BSTinsert(struct node *T, itemType v, infoType info, int &cmp);
infoType BSTsearch(struct node *T, itemType v);
void inorder(struct node *p);

int main() {

    int N;
    cin >> N;
    int *ary = new int[N];

    srand(time(NULL));

    initArray(ary, N);

    RBtree(N);

    for (int i = 0; i < N; i++)
        BSTinsert(T1, ary[i], 0, cmp_build1);

    inorder(T1->r);

    int cmp1 = 0, cmp2 = 0, cmp3 = 0;
    for (int i = 0; i < N; i++) {
        cmp1 += BSTsearch(T1, ary[i]);
        cmp2 += BSTsearch(T2, ary[i]);
        cmp3 += search(T3, ary[i]);
    }


    cout << (double)cmp_build1 / N << " (T1의 구축 시 평균 비교 회수)" << endl;
    cout << (double)cmp_build2 / N << " (T2의 구축 시 평균 비교 회수)" << endl;
    cout << (double)cmp_build3 / N << " (T3의 구축 시 평균 비교 회수)" << endl;

    cout << endl;

    cout << (double)cmp1 / N << " (T1의 평균 탐색 비교 회수)" << endl;
    cout << (double)cmp2 / N << " (T2의 평균 탐색 비교 회수)" << endl;
    cout << (double)cmp3 / N << " (T3의 평균 탐색 비교 회수)" << endl;

    return 0;
}

void initArray(int *ary, int N) {

    int **temp = new int*[N];

    srand((unsigned)time(NULL));

    for (int i = 0; i < N; i++) {
        temp[i] = new int[2];
        temp[i][0] = rand() % N + 1;
        temp[i][1] = i + 1;
    }

    init_array(temp, ary, N);

    for (int i = 0; i < N; i++)
        ary[i] = temp[i][1];

    for (int i = 0; i < N; i++)
        delete[] temp[i];

    delete[] temp;
}

void init_array(int **temp, int *ary, int N) {

    int i, j, h;
    itemType v1, v2;

    h = 1;
    do {
        h = 3 * h + 1;
    } while (h < N);

    do {
        h = h / 3;
        for (i = h; i < N; i++) {
            v1 = temp[i][0];
            v2 = temp[i][1];

            j = i;

            while (temp[j - h][0] > v1) {
                temp[j][0] = temp[j - h][0];
                temp[j][1] = temp[j - h][1];

                j -= h;

                if (j <= h - 1)   break;
            }
            temp[j][0] = v1;
            temp[j][1] = v2;
        }
    } while (h > 1);

    for (int i = 0; i < N; i++)
        ary[i] = temp[i][1];
}

void BSTinsert(struct node *T, itemType v, infoType info, int &cmp) {

    struct node *p, *x;

    p = T;
    x = T->r;

    while (x != _z) {
        p = x;
        x = (v < x->key) ? x->l : x->r;
        cmp++;
    }

    x = new node(v, info, _z, _z);

    if (v < p->key) p->l = x;
    else         p->r = x;
    cmp++;
}

infoType BSTsearch(struct node *T, itemType v) {

    struct node *x = T->r;

    int count = 0;
    while (v != x->key)  {
        x = (v < x->key) ? x->l : x->r;
        count++;
    }

    x->info = count;
    return x->info;
}

void inorder(struct node *p) {

    if (p != _z) {
        inorder(p->l);

        BSTinsert(T2, p->key, 0, cmp_build2); // T2
        insert(T3, p->key, 0, cmp_build3); // T3
        inorder(p->r);
    }
}

