
#include <iostream>
#include <fstream>
#include <vector>
#include <queue>
#include <limits>
#include <memory>

using namespace std;

int delta[4][2] = {{-1, 0}, // Up
                   {0, -1}, // Left
                   {1, 0},  // Down
                   {0, 1}}; // Right

char delta_name[4] = {'^', '<', 'v', '>'};

struct Cell {
    int risk = numeric_limits<int>::max();
    int visited = false;
    int action = -1;
    int col;
    int row;
};

class Compare {
public:
    Compare(bool reverse = false) : reverse(reverse) {}

    bool operator()(const Cell& a, const Cell& b) {
        if (reverse) return a.risk > b.risk;
        return a.risk < b.risk;
    }

private:
    bool reverse;
};

void print_risk_map(const vector<vector<int>>& risk_map);
void print_policy(const vector<vector<Cell>>& policy);
void find_shortest_path(const vector<vector<int>>& risk_map,
                        vector<vector<Cell>>& policy);
bool is_valid(int row, int col, int max_row, int max_col);
void print_actions(const vector<vector<Cell>>& policy);
void print_risk(const vector<vector<Cell>>& policy);
void expand(vector<vector<int>>& risk_map, int multiplier);

int main(int argc, char* argv[]) {
    string file_name = "risk_map.txt";

    ifstream input_file(file_name);
    if (!input_file.good()) {
        cerr << "File " << file_name << "Couldn't be opened.\n";
        exit(EXIT_FAILURE);
    }

    // Read risk map
    vector<vector<int>> risk_map;
    string line;
    while (getline(input_file, line)) {
        vector<int> row;
        for (char c : line) {
            row.push_back(c - '0');
        }
        risk_map.push_back(row);
    }

    // Since the map is 5 times bigger we expand it by 4
    expand(risk_map, 4);

    // create the policy matrix
    vector<vector<Cell>> policy;
    for (int row = 0; row < risk_map.size(); row++) {
        vector<Cell> cell_row;
        for (int col = 0; col < risk_map[0].size(); col++) {
            Cell new_cell;
            new_cell.row = row;
            new_cell.col = col;
            cell_row.push_back(new_cell);
        }
        policy.push_back(cell_row);
    }

    // print_risk_map(risk_map);
    find_shortest_path(risk_map, policy);
    // print_actions(policy);
    // print_risk(policy);

}

void find_shortest_path(const vector<vector<int>>& risk_map,
                        vector<vector<Cell>>& policy)
{
    int max_row = risk_map.size() - 1;
    int max_col = risk_map[0].size() - 1;
    int goal[2] = {max_row, max_col};
    priority_queue<Cell, vector<Cell>, Compare> open(Compare(true));
    policy[0][0].risk = 0;
    open.push(policy[0][0]);
    while (!open.empty()) {
        auto current = open.top(); open.pop();
        policy[current.row][current.col].visited = true;
        if (current.row == goal[0] && current.col == goal[1]) {
            cout << "Smallest total risk to goal is: " << current.risk << endl;
            return; // we have reached our goal
        }

        for (int act = 0; act < 4; act++) {
            int next_row = current.row + delta[act][0];
            int next_col = current.col + delta[act][1];
            if (is_valid(next_row, next_col, max_row, max_col) &&
                !policy[next_row][next_col].visited) {
                // Explore unvisited valid vertices
                int next_risk = current.risk + risk_map[next_row][next_col];
                if (next_risk < policy[next_row][next_col].risk) {
                    policy[next_row][next_col].risk = next_risk;
                    policy[next_row][next_col].action = act;
                    // found a path with smaller risk so we add
                    // vertex to the open priority queue
                    open.push(policy[next_row][next_col]);
                }
            }
        }
    }
}

void expand(vector<vector<int>>& risk_map, int multiplier) {
    int width = risk_map[0].size();
    for (int m = 0; m < multiplier; m++) {
        for (int row = 0; row < risk_map.size(); row++) {
            vector<int> &cur_row = risk_map[row];
            for (int col = 0; col < width; col++) {
                // Modulus 9 produces values 0 to 8 so we add 1
                cur_row.push_back((risk_map[row][col] + 1 * m) % 9 + 1);
            }
        }
    }

    int height = risk_map.size();
    vector<int> new_row(risk_map[0].size(), 0);
    for (int m = 0; m < multiplier; m++) {
        for (int row = 0; row < height; row++) {
            for (int col = 0; col < risk_map[0].size(); col++) {
                new_row[col] = (risk_map[row][col] + 1 * m) % 9 + 1;
            }
            risk_map.push_back(new_row);
        }
    }

}

bool is_valid(int row, int col, int max_row, int max_col) {
    return row >= 0 && col >= 0 && row <= max_row && col <= max_col;
}

void print_risk_map(const vector<vector<int>>& risk_map) {
    for (auto row : risk_map) {
        for (int v : row) {
            cout << v;
        }
        cout << endl;
    }
}

void print_policy(const vector<vector<Cell>>& policy) {
    for (auto row : policy) {
        for (auto cell : row) {
            cout << "<" << cell.risk
                 << "," << cell.visited
                 << "," << cell.action << ">";
        }
        cout << endl;
    }
}

void print_actions(const vector<vector<Cell>>& policy) {
    for (auto row : policy) {
        for (auto cell : row) {
            cout << delta_name[cell.action];
        }
        cout << endl;
    }
}

void print_risk(const vector<vector<Cell>>& policy) {
    for (auto row : policy) {
        for (auto cell : row) {
            cout << "[" << cell.risk << "]";
        }
        cout << endl;
    }
}