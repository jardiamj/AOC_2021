
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <stack>
#include <algorithm>

using namespace std;

string OPEN = "([{<";
string CLOSE = ")]}>";
int ERROR_SCORES[4] = {3, 57, 1197, 25137};
int CORRECT_SCORES[4] = {1, 2, 3, 4};

bool is_balanced(string& str, long& score);
bool closes(char open_c, char close_c);

int main(int argc, char* argv[]) {
    ifstream in_file;
    in_file.open("lines.txt");

    if (!in_file.good()) {
        cerr << "File could not be opened.\n";
    }

    vector<string> lines;

    string line;
    while (in_file >> line) {
        lines.push_back(line);
    }

    vector<int> illegal_scores;
    vector<long> autocorrect_scores;
    for (string line: lines) {
        long score;
        // int is_bal = is_balanced(line);
        if (!is_balanced(line, score)) {
            illegal_scores.push_back(score);
        } else {
            autocorrect_scores.push_back(score);
        }
    }

    int syntax_score = 0;
    for (int i_score : illegal_scores) {
        syntax_score += i_score;
    }
    cout << "Syntax Score: " << syntax_score << endl;

    sort(autocorrect_scores.begin(), autocorrect_scores.end());
    // cout << "Autocorrect scores:";
    // for (auto it = autocorrect_scores.begin(); it != autocorrect_scores.end(); it++) {
    //     cout << " " << *it;
    // }
    // cout << endl;

    cout << "Autocorrect winner: " << autocorrect_scores[autocorrect_scores.size()/2] << endl;
}

// return illegal character position in CLOSE array or -1 if balanced
bool is_balanced(string& str, long& score) {
    stack<char> chunks;
    for (char c : str) {
        int c_close_pos = CLOSE.find(c);
        if (OPEN.find(c) != string::npos) {
            chunks.push(c);
        } else if (string::npos != c_close_pos) {
            char c_top = chunks.top();
            int top_pos = OPEN.find(c_top);
            if (string::npos != top_pos && top_pos == c_close_pos) {
                chunks.pop();
            } else {
                // cout << "Expected: " << CLOSE[top_pos]
                //      << " but found: " << CLOSE[c_close_pos] << " char:" << c << '\n';
                score = ERROR_SCORES[c_close_pos];
                return false;
            }
        }
    }


    long correcting_score = 0;
    // if chunks is not empty complete string
    while(!chunks.empty()) {
        char o_top = chunks.top();
        int o_pos = OPEN.find(o_top);
        char c_top = CLOSE[o_pos];
        str += c_top;

        // calculate score
        correcting_score *= 5;
        correcting_score += CORRECT_SCORES[o_pos];
        chunks.pop();
    }
    // cout << "Complete: " << str << endl;
    score = correcting_score;
    return true;
}

bool closes(char open_c, char close_c) {
    switch(open_c) {
        case '(': return close_c == ')'; break;
        case '[': return close_c == ']'; break;
        case '{': return close_c == '}'; break;
        case '<': return close_c == '>'; break;
        default: return false;
    }
}
