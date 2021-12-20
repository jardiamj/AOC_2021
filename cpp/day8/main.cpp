#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <set>

#include "reading.h"

using namespace std;

int main(int argc, char* argv[]) {
    ifstream in_file;
    string f_name = "digits.txt";
    in_file.open(f_name);

    if (!in_file.good()) {
        cerr << "File " << f_name << " couldn't be opened" << '\n';
        return 1;
    }

    vector<pair<vector<string>, vector<string>>> data;
    vector<string> unique_digits, output_val;
    set<int> unique = {2, 3, 4, 7};

    vector<Reading> reading_list;

    string line;
    while(getline(in_file, line)) {
        reading_list.push_back(Reading(line)); // automatic conversion
    }

    int total = 0;
    for (auto row : reading_list) {
        total += row.get_value();
        cout << row << '\n'; 
    };
    cout << "Total: " << total << '\n';
}