#include <iostream>
#include <fstream>
#include <vector>
#include <string>

using namespace std;

enum Position {
    UL_CORNER, UP, UR_CORNER, LEFT, RIGHT, BL_CORNER, BR_CORNER, BOTTOM, INNER
};

struct Move {
    int UP[2] = {-1, 0};
    int DOWN[2] = {1, 0};
    int LEF[2] = {0, -1};
    int RIGHT[2] = {1, 0};
};

int moves[4][2] = {{-1, 0},
                   {1, 0},
                   {0, -1},
                   {0, 1}};

Position get_position(const vector<string> h_map, int row, int col);
bool is_low_point(const vector<string> h_map, int row, int col);
bool is_valid(int row, int col, int max_row, int max_col);
void explore_basin(const vector<string>& h_map, 
                          vector<vector<bool>>& visited,
                          vector<int>& points,
                          int row, int col);

void get_top_kth(vector<int>& v, int k);

int main(int argc, char* argv[]) {
    ifstream input_file;
    input_file.open("cave_map.txt");

    if (!input_file.good()) {
        cerr << "File could not be opened" << '\n';
    }

    vector<string> height_map;

    // Populate map from file
    string line;
    while(input_file >> line) {
        height_map.push_back(line);
    }

    vector<vector<bool>> visited(height_map.size(),
                                 vector<bool>(height_map[0].size()));

    vector<vector<int>> basins;

    int risk_level = 0;
    for (int row = 0; row < height_map.size(); row++){
        for (int col = 0; col < height_map[row].size(); col++) {
            if (is_low_point(height_map, row, col)){
                int h = height_map[row][col] - '0';
                // risk_level += 1 + h;
                vector<int> basin;
                explore_basin(height_map, visited, basin, row, col);
                basins.push_back(basin);
            }
        }
    }

    vector<int> basin_sizes;
    for (auto basin : basins) {
        basin_sizes.push_back(basin.size());
        // cout << basin.size() << ", ";
    }
    // cout << '\n';

    get_top_kth(basin_sizes, 3);

    // for (int v : basin_sizes) {
    //     cout << v << ", ";
    // }
    // cout << '\n';

    int total_level = 1;
    int b_size = basin_sizes.size();
    for (int i = 1; i <= 3; i++) {
        total_level *= basin_sizes[b_size - i];
    }

    cout << "Larger Basin Size: " << total_level << '\n';
}

void swap_int (int& n, int& m) {
    int tmp = n;
    n = m;
    m = tmp;
}

void get_top_kth(vector<int>& v_list, int k) {
    int n = k < v_list.size() ? k : v_list.size();

    // bubble top kth elements to top
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < v_list.size() - (i + 1); j++) {
            if (v_list[j] > v_list[j + 1]) {
                swap_int(v_list[j], v_list[j + 1]);
            }
        }
    }
}

void explore_basin(const vector<string>& h_map, 
                          vector<vector<bool>>& visited,
                          vector<int>& points,
                          int row, int col) {
    
    if (!is_valid(row, col, h_map.size(), h_map[0].size())
        || visited[row][col]
        || h_map[row][col] == '9') {
        return;
    }

    points.push_back(h_map[row][col] - '0');
    visited[row][col] = true;

    for (int* move : moves) {
        int next_row = row + move[0];
        int next_col = col + move[1];
        // cout << "Visiting: " << next_row << ", " << next_col << '\n';
        explore_basin(h_map, visited, points, next_row, next_col);
    }
}


bool is_valid(int row, int col, int max_row, int max_col) {
    return row >= 0 && col >= 0 && row < max_row && col < max_col;
}

bool is_low_point(const vector<string> h_map, int row, int col) {
    Position pos = get_position(h_map, row, col);

    switch(pos) {
        case UL_CORNER:
            return h_map[row][col] < h_map[row][col + 1] &&
                   h_map[row][col] < h_map[row + 1][col];
        case UR_CORNER:
            return h_map[row][col] < h_map[row][col - 1] &&
                   h_map[row][col] < h_map[row + 1][col];
        case BL_CORNER:
            return h_map[row][col] < h_map[row][col + 1] &&
                   h_map[row][col] < h_map[row - 1][col];
        case BR_CORNER:
            return h_map[row][col] < h_map[row][col - 1] &&
                   h_map[row][col] < h_map[row -1][col];
        case UP:
            return h_map[row][col] < h_map[row][col - 1] &&
                   h_map[row][col] < h_map[row][col + 1] &&
                   h_map[row][col] < h_map[row + 1][col];
        case BOTTOM:
            return h_map[row][col] < h_map[row][col - 1] &&
                   h_map[row][col] < h_map[row][col + 1] &&
                   h_map[row][col] < h_map[row - 1][col];
        case LEFT:
            return h_map[row][col] < h_map[row - 1][col] &&
                   h_map[row][col] < h_map[row + 1][col] &&
                   h_map[row][col] < h_map[row][col + 1];
        case RIGHT:
            return h_map[row][col] < h_map[row - 1][col] &&
                   h_map[row][col] < h_map[row + 1][col] &&
                   h_map[row][col] < h_map[row][col - 1];
        default:
            return h_map[row][col] < h_map[row - 1][col] &&
                   h_map[row][col] < h_map[row + 1][col] &&
                   h_map[row][col] < h_map[row][col - 1] &&
                   h_map[row][col] < h_map[row][col + 1];
    }
}

Position get_position(const vector<string> h_map, int row, int col) {
    int height = h_map.size() - 1;
    int width = h_map[row].size() - 1;
    if (col == 0) {
        if (row == 0) {
            return UL_CORNER;
        } else if (row == height) {
            return BL_CORNER;
        } else {
            return LEFT;
        }
    }
    
    if (col == width) {
        if (row == 0) {
            return UR_CORNER;
        } else if (row == height) {
            return BR_CORNER;
        } else {
            return RIGHT;
        }
    }
    
    if (row == 0) {
        return UP;
    }

    if (row == height) {
        return BOTTOM;
    }

    return INNER;
}