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
        cout << "파일을 찾을 수 없습니다." << endl;
        exit(1);
    }

    string delimiters = " .,/";
    string line;
    vector<string> tokens;
    vector<vector<string>> res; // 줄 별 단어들의 vector를 저장할 이차원 vector
    while (!in.eof()) {
        getline(in, line); // 파일의 한 줄을 읽어옴
        Tokenize(line, tokens, delimiters); // 한 줄을 단어로 분리
        res.push_back(tokens);  // res벡터에 저장
        tokens.clear();
    }

    vector<pair<string, int>> dic; // 단어와 그 출현 횟수를 저장할 vector
    for (vector<string> v : res) {
        for (int i = 0; i < v.size(); i++) {
            bool isNew = true; // 새로운 단어이면 true
            for (vector<pair<string, int>>::iterator it = dic.begin(); it != dic.end(); ++it) {
                if (it->first == v[i]) { // 이미 있는 단어
                    isNew = false;
                    it->second++; // 출현 횟수 증가
                }
            }
            if (isNew)
                dic.push_back(make_pair(v[i], 1));
        }
    }

    quicksort(dic, 0, dic.size() - 1); // 빈도수 내림차순 정렬

    // 정렬된 dic을 빈도수가 같은 범위 내 부분 배열을 stringSort
    int temp = dic[0].second; // second는 빈도 수
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
            stringSort(dic, o - 1, p - 1); // 단어 오름차순(ASCII 코드 기준)
        }
    }

    // 결과 출력
    for (int i = 0; i < dic.size(); i++) {
        cout << dic[i].first << ": " << dic[i].second << endl;
    }
    return 0;
}

// 특수문자,공백등의 delimiter를 기준으로 문자열을 tokenizing
void Tokenize(string& str, vector<string>& tokens, string& delimiters) {
    string::size_type lastPos = str.find_first_not_of(delimiters, 0);
    string::size_type pos = str.find_first_of(delimiters, lastPos);

    while (string::npos != pos || string::npos != lastPos) {
        tokens.push_back(str.substr(lastPos, pos - lastPos)); // token을 vector에 추가
        lastPos = str.find_first_not_of(delimiters, pos); // 구분자 건너뜀
        pos = str.find_first_of(delimiters, lastPos); // 다음 token
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
                if (i == a.size() - 1) break; // vector overflow 예외처리
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

// 빈도 수가 같은 단어의 ASCII 기준 오름차순 정렬 (삽입 정렬로 구현)
void stringSort(vector<pair<string, int>>& a, int start, int end) {
    int i, j;
    pair<string, int> temp;
    for (i = start + 1; i <= end; i++) {
        temp = a[i];
        j = i;
        // a[j - 1].first > temp.first == strcmp(a[j - 1].first.c_str(), temp.first.c_str()) == 1
        while (a[j - 1].first > temp.first && a[j - 1].second == temp.second) { // second가 dummy 역할
            a[j] = a[j - 1];
            j--;
        }
        a[j] = temp;
    }
}
