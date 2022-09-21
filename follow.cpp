#include <vector>
#include <iostream>
#include <unordered_map>
#include <set>
#include <cctype>
#include <string.h>
using namespace std;

void FindFollow(char);

unordered_map<char, set<char>> follow_set;

struct Rule {
// if has a rule like 「A -> BCD」
// its nonTerminal would be A
// its production would be BCD
    char nonTerminal;
    string production;
public:
    Rule(char nonTerminal, string production) {
        this->nonTerminal = nonTerminal;
        this->production = production;
    }
};
struct FirstSet {
// if A's first set contains b, c, d three symbol
// its nonTerminal would be A
// its set would be bcd
    char nonTerminal;
    string set;
public:
    FirstSet(char nonTerminal, string set) {
        this->nonTerminal = nonTerminal;
        this->set = set;
    }
};

vector<Rule> rules;
vector<FirstSet> firstSets;

int main() {
    string s;
    while (getline(cin, s) && s != "END_OF_GRAMMAR") { // if same, strcmp would return 0
        char nonTerminal = s[0];
        string production;
        for (int i = 2; i < s.length(); i++) {
            if (s[i] != '|') {
                production += s[i];
            }
            else {
                production += '$';
                rules.push_back(Rule(nonTerminal, production));
                production = "";
            }
        }
        production += '$';
        rules.push_back(Rule(nonTerminal, production));
    }

    while (getline(cin, s) && s != "END_OF_FIRST_SET") { // if same, strcmp would return 0
        char nonTerminal = s[0];
        string production;
        for (int i = 2; i < s.length(); i++) {
            production += s[i];
        }
        firstSets.push_back(FirstSet(nonTerminal, production));
    }

    /*for (int i = 0; i < rules.size(); i++) {
        std::cout << rules[i].nonTerminal << " -> " << rules[i].production <<
            std::endl;
    }
    for (int i = 0; i < firstSets.size(); i++) {
        std::cout << firstSets[i].nonTerminal << "'s first set is " <<
            firstSets[i].set << std::endl;
    }*/

    for (char ch = 'A'; ch <= 'Z'; ch++) {
        for (int i = 0; i < rules.size(); i++) {
            if (rules[i].nonTerminal == ch && follow_set[ch].empty()) {
                FindFollow(ch);
            }
        }
    }

    for (char ch = 'A'; ch <= 'Z'; ch++) {
        if (!follow_set[ch].empty()) {
            cout << ch << " ";
            for (auto it = follow_set[ch].begin(); it != follow_set[ch].end(); it++)
                cout << *it;
            cout << endl;
        }
    }
}

void FindFollow(char ch) {
    set<char> Follow;
    for (int i = 0; i < rules.size(); i++) {
        for (int j = 0; j < rules[i].production.length(); j++) {
            if (ch == rules[i].production[j]) {
                if (rules[i].production[j + 1] == '$') {
                    char next = rules[i].nonTerminal;
                    if (follow_set.find(next) == follow_set.end()) //先檢查在follow_set裡是否有找到follow
                        FindFollow(next);
                    Follow.insert(follow_set[next].begin(), follow_set[next].end());

                }
                else if (islower(rules[i].production[j + 1])) {
                    Follow.insert(rules[i].production[j + 1]);
                }
                else {
                    int pos;
                    for (int p = 0; p < firstSets.size(); p++) {
                        if (firstSets[p].nonTerminal == rules[i].production[j + 1]) {
                            pos = p;
                        }
                    }
                    for (int m = 0; m < firstSets[pos].set.length(); m++) {
                        Follow.insert(firstSets[pos].set[m]);
                    }
                    for (int k = 2; k < rules[i].production.length(); k++) {
                        if (firstSets[pos].set[0] == ';') {
                            if (rules[i].production[j + k] == '$') {
                                char next = rules[i].nonTerminal;
                                if (follow_set.find(next) == follow_set.end()) //先檢查在follow_set裡是否有找到follow
                                    FindFollow(next);
                                Follow.insert(follow_set[next].begin(), follow_set[next].end());
                                if (follow_set[next].find('$') == follow_set[next].end()) {
                                    break;
                                }
                                Follow.insert(rules[i].production[j + k]);
                                break;
                            }
                            else if (islower(rules[i].production[j + k])) {
                                Follow.insert(rules[i].production[j + k]);
                                break;
                            }
                            for (int p = 0; p < firstSets.size(); p++) {
                                if (firstSets[p].nonTerminal == rules[i].production[j + k]) {
                                    pos = p;
                                }
                            }
                            for (int n = 0; n < firstSets[pos].set.length(); n++) {
                                Follow.insert(firstSets[pos].set[n]);
                            }
                        }
                        else {
                            break;
                        }
                    }
                    /*for (auto it = Follow.begin(); it != Follow.end(); it++) {
                        cout << *it << " ";
                    }*/
                }
            }
        }
    }
    if (Follow.empty()) {
        Follow.insert('$');
    }
    Follow.erase(';');
    follow_set[ch].insert(Follow.begin(), Follow.end());
}
