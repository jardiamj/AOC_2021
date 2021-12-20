#include <iostream>
#include <fstream>
#include <vector>
#include <limits>

using namespace std;

int main(int argc, char* argv[]) {
    ifstream in_file;
    string f_name = "h_distance.txt";
    in_file.open(f_name);

    if (!in_file.good()) {
        cerr << "File " << f_name << " couln't be opened" << '\n';
        return 1;
    }

   vector<int> h_position;
    int pos; int max = 0;
    char c; // For discarding char
    while (in_file >> pos) {
        h_position.push_back(pos);
        if (pos > max) {
            max = pos;
        }
        in_file >> c;
    }

    vector<vector<int>> dist_matrix(max + 1, vector<int>(h_position.size()));

    for (int idx = 0; idx < h_position.size(); idx++) {
        int current_pos = h_position[idx];
        for (int row = 0; row < dist_matrix.size(); row++) {
            int dist = abs(current_pos - row);
            int dist_summation = dist * (dist + 1) / 2;
            dist_matrix[row][idx] = dist_summation;
        }
    }

    int min_sum = numeric_limits<int>::max();
    for (auto row : dist_matrix) {
        int row_sum = 0;
        for (auto col : row) {
            // cout << col << ", ";
            row_sum += col;
        }
        if (row_sum < min_sum) {
            min_sum = row_sum;
        }
        // cout << " sum: " << row_sum << '\n';
    }
    cout << "Min sum: " << min_sum << endl;
}