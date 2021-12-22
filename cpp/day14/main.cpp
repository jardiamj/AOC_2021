#include <iostream>
#include <string>
#include <fstream>
#include <list>
#include <vector>
#include <unordered_map>
#include <limits>

using namespace std;
void poly_insert(unordered_map<string, long>& polymer_pairs,
                 const unordered_map<string, char>& insertions);
void print_stats(unordered_map<string, long>& polymer_pairs, char fc, char lc);
void print_pairs(const unordered_map<string, long>& polymer_pairs);

int main(int argc, char* argv[]) {
    string file_name = "input.txt";

    ifstream in_file(file_name);

    if (!in_file.good()) {
        cerr << "File " << file_name << "Could not be opened.\n";
    }

    string tmplt_str;
    // Keep track pairs instead of individual polimer elements because of the
    // exponential growth.
    in_file >> tmplt_str;
    unordered_map<string, long> polymer_pairs;

    size_t prev_idx = 0;
    size_t cur_idx = 1;
    for (; cur_idx < tmplt_str.size(); cur_idx++, prev_idx++) {
        string p = {tmplt_str[prev_idx], tmplt_str[cur_idx]};
        if (polymer_pairs.find(p) == polymer_pairs.end()) {
            polymer_pairs[p] = 1;
        } else {
            polymer_pairs[p] += 1;
        }
    }

    // read all pair insertions
    unordered_map<string, char> insertions;
    string pair; string separator; char insert;
    while (in_file >> pair >> separator >> insert) {
        insertions[pair] = insert;
    }

    cout << "Template:\n";
    print_pairs(polymer_pairs);

    for (int i = 1; i <= 40; i++) {
        poly_insert(polymer_pairs, insertions);
    }

    cout << "After Step 10:\n";
    print_pairs(polymer_pairs);
    print_stats(polymer_pairs, tmplt_str[0], tmplt_str[tmplt_str.size() - 1]);
}

void poly_insert(unordered_map<string, long>& polymer_pairs,
                 const unordered_map<string, char>& insertions)
{
    // Determine new pairs
    unordered_map<string, long> new_pairs;
    for (auto insertion : insertions) {
        string key = insertion.first;
        if (polymer_pairs.find(key) != polymer_pairs.end()) {
            long n_pairs = polymer_pairs[key];
            polymer_pairs.erase(key);
            string p1 = {key[0], insertion.second};
            string p2 = {insertion.second, key[1]};

            if (new_pairs.find(p1) != new_pairs.end()) {
                new_pairs[p1] += n_pairs;
            } else {
                new_pairs[p1] = n_pairs;
            }

            if (new_pairs.find(p2) != new_pairs.end()) {
                new_pairs[p2] += n_pairs;
            } else {
                new_pairs[p2] = n_pairs;
            }
        }
    }

    // Add new pairs
    for (auto p : new_pairs) {
        if (polymer_pairs.find(p.first) != polymer_pairs.end()) {
            polymer_pairs[p.first] += p.second;
        } else {
            polymer_pairs[p.first] = p.second;
        }
    }
}

void print_stats(unordered_map<string, long>& polymer_pairs, char fc, char lc) {
    unordered_map<char, long> frequency;
    for (auto p : polymer_pairs) {
        char c1 = p.first[0];
        char c2 = p.first[1];
        
        if (frequency.find(c1) != frequency.end()) {
            frequency[c1] += p.second;
        } else {
            frequency[c1] = p.second;
        }
        if (frequency.find(c2) != frequency.end()) {
            frequency[c2] += p.second;
        } else {
            frequency[c2] = p.second;
        }
    }

    for (auto f : frequency) {
        cout << f.first << " : " << f.second << endl;
        if (f.first == fc || f.first == lc) {
            frequency[f.first] = ((f.second - 1) / 2) + 1;
        } else {
            frequency[f.first] = f.second / 2;
        }
    }

    char max_k, min_k;
    long max_v = 0;
    long min_v = numeric_limits<long>::max();
    auto it = frequency.begin();
    for ( ; it != frequency.end(); it++) {
        if (it->second < min_v) {
            min_v = it->second;
            min_k = it->first;
        }
        if (it->second > max_v) {
            max_v = it->second;
            max_k = it->first;
        }
    }

    cout << "Max -> " << max_k << ": " << max_v << endl;
    cout << "Min -> " << min_k << ": " << min_v <<  endl;
    cout << "Diff = " << (max_v - min_v) << endl;
}

void print_pairs(const unordered_map<string, long>& polymer_pairs) {
    for (auto p : polymer_pairs) {
        cout << p.first << ": " << p.second << endl;
    }
}