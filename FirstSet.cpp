#include <iostream>
#include <unordered_map>
#include <set>
#include <vector>
#include <cctype>
#include <string>
using namespace std;

void FindFirst(char);

unordered_map<char, vector<string>> rule;
unordered_map<char, set<char>> first_set;

int main() {
    char ch;
    string str;
    while (cin >> ch >> str) {
        if (str == "ND_OF_GRAMMAR") break;
        size_t pos;
        while (pos = str.find('|'), pos != string::npos) {
            rule[ch].push_back(str.substr(0, pos));
            str.erase(0, pos + 1);
        }
        rule[ch].push_back(str);
    }
    for (char ch = 'A'; ch <= 'Z'; ch++) {
        if (rule.find(ch) == rule.end()) //如果ch不在rule裡面則跳到下一個英文
            continue;
        if (first_set.find(ch) == first_set.end()) //ch在rule裡面則開始找first set
            FindFirst(ch);
    }
    for (char ch = 'A'; ch <= 'Z'; ch++) {
        if (first_set.find(ch) == first_set.end())
            continue;
        cout << ch << " ";
        for (auto it = first_set[ch].begin(); it != first_set[ch].end(); it++)
            cout << *it;
        cout << endl;
    }
    cout << "END_OF_FIRST" << endl;
}

void FindFirst(char ch) {
    for (int i = 0; i < rule[ch].size(); i++) {
        set<char> RuleTmp;
        for (int j = 0; j < rule[ch][i].size(); j++) {
            char now = rule[ch][i][j];
            set<char> First;
            //terminal
            if (islower(now) || now == ';' || now == '$') {
                First.insert(now);
            }
            //nonterminal
            else {
                if (first_set.find(now) == first_set.end()) //先檢查在first_set裡是否有找到first
                    FindFirst(now);
                First.insert(first_set[now].begin(), first_set[now].end());
            }
            RuleTmp.insert(First.begin(), First.end());
            if (First.find(';') == First.end()) {  //如果沒有分號但後面還有字母則直接break不用找 若有分號則要找到小寫英文 否則就會有分號
                RuleTmp.erase(';');
                break;
            }
        }
        first_set[ch].insert(RuleTmp.begin(), RuleTmp.end());
    }
}

//compiler
//flex -o lex.yy.c 檔名.l
//gcc -o 檔名 lex.yy.c -lfl

//run
//./檔名 < input.txt(input的東西)

//lex
//* 0-無限   + 1-無限   ? 0/1   [] 集合中擇1(數字或大小英文字母連續區間用-隔開)
//\跳脫字元   ^ 在[]裡時表示排除,在外面表示行首   $ 表示行尾

//set迴圈遍歷
//for (std::set<int>::iterator it = myset.begin(); it != myset.end(); it++) {
// or
// for (auto it = myset.begin(); it != myset.end(); it++) {
//    std::cout << *it << " ";
//}

//for (const auto& s : myset) {
//    std::cout << s << " ";
//}

//unmap遍歷
//for (const auto& n : umap) {
//    std::cout << "name: " << n.first << ", id: " << n.second << "\n";
//}

//for (std::unordered_map<std::string, int>::iterator it = umap.begin(); it != umap.end(); it++) {
    // or
    // for (auto it = umap.begin(); it != umap.end(); it++) {
//std::cout << "name: " << (*it).first << ", id: " << (*it).second << "\n";
//    }