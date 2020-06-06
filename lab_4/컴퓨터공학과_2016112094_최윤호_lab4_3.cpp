#include <iostream>
#include <fstream>
#include <string>
#include <vector>

using namespace std;

void Tokenize(string& str, vector<string>& tokens, string& delimiters);
inline void swap(vector<pair<string, int>>& a, int i, int j);
int partition(vector<pair<string, int>>& a, int l, int r);
void quicksort(vector<pair<string, int>>& a, int l, int r);
void stringSort(vector<pair<string, int>>& a, int first, int n);

int main() {
    ifstream in("datafile.txt");
    if (!in.is_open()) {
        cout << "������ ã�� �� �����ϴ�." << endl;
        exit(1);
    }

    string delimiters = " .,/";
    string line;
    vector<string> tokens;
    vector<vector<string>> res; // �� �� �ܾ���� vector�� ������ ������ vector
    while (!in.eof()) {
        getline(in, line); // ������ �� ���� �о��
        Tokenize(line, tokens, delimiters); // �� ���� �ܾ�� �и�
        res.push_back(tokens);  // res���Ϳ� ����
        tokens.clear();
    }

    vector<pair<string, int>> dic; // �ܾ�� �� ���� Ƚ���� ������ vector
    for (vector<string> v : res) {
        for (int i = 0; i < v.size(); i++) {
            bool isNew = true; // ���ο� �ܾ��̸� true
            for (vector<pair<string, int>>::iterator it = dic.begin(); it != dic.end(); ++it) {
                if (it->first == v[i]) { // �̹� �ִ� �ܾ�
                    isNew = false;
                    it->second++; // ���� Ƚ�� ����
                }
            }
            if (isNew)
                dic.push_back(make_pair(v[i], 1));
        }
    }

    quicksort(dic, 0, dic.size() - 1); // �󵵼� �������� ����

    // ���ĵ� dic�� �󵵼��� ���� ���� �� �κ� �迭�� stringSort
    int temp = dic[0].second; // second�� �� ��
    for (int o = 1; o < dic.size(); o++) {
        if (temp > dic[o].second) {
            temp = dic[o].second;
        }
        else {
            int p;
            for (p = o + 1; p < dic.size(); p++) {
                if (dic[p].second < temp)
                    break;
            }
            stringSort(dic, o - 1, p - 1); // �ܾ� ��������(ASCII �ڵ� ����)
        }
    }

    // ��� ���
    for (int i = 0; i < dic.size(); i++) {
        cout << dic[i].first << ": " << dic[i].second << endl;
    }
    return 0;
}

// Ư������,������� delimiter�� �������� ���ڿ��� tokenizing
void Tokenize(string& str, vector<string>& tokens, string& delimiters) {
    string::size_type lastPos = str.find_first_not_of(delimiters, 0);
    string::size_type pos = str.find_first_of(delimiters, lastPos);

    while (string::npos != pos || string::npos != lastPos) {
        tokens.push_back(str.substr(lastPos, pos - lastPos)); // token�� vector�� �߰�
        lastPos = str.find_first_not_of(delimiters, pos); // ������ �ǳʶ�
        pos = str.find_first_of(delimiters, lastPos); // ���� token
    }
}

inline void swap(vector<pair<string, int>>& a, int i, int j) {
    pair<string, int> t = a[i];
    a[i] = a[j];
    a[j] = t;
}

int partition(vector<pair<string, int>>& a, int l, int r) {
    int i, j; pair<string, int> v;
    if (r > l) {
        v = a[l]; i = l; j = r + 1;
        for (;;) {
            while (a[++i].second > v.second)
                if (i == a.size() - 1) break; // vector overflow ����ó��
            while (a[--j].second < v.second);
            if (i >= j) break;
            swap(a, i, j);
        }
        swap(a, j, l);
    }
    return j;
}

void quicksort(vector<pair<string, int>> & a, int l, int r) {
    int j;
    if (r > l) {
        j = partition(a, l, r);
        quicksort(a, l, j - 1);
        quicksort(a, j + 1, r);
    }
}

// �� ���� ���� �ܾ��� ASCII ���� �������� ���� (���� ���ķ� ����)
void stringSort(vector<pair<string, int>>& a, int start, int end) {
    int i, j;
    pair<string, int> temp;
    for (i = start + 1; i <= end; i++) {
        temp = a[i];
        j = i;
        // a[j - 1].first > temp.first == strcmp(a[j - 1].first.c_str(), temp.first.c_str()) == 1
        while (a[j - 1].first > temp.first && a[j - 1].second == temp.second) { // second�� dummy ����
            a[j] = a[j - 1];
            j--;
        }
        a[j] = temp;
    }
}
