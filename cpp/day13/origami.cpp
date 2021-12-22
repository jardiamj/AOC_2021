#include <sstream>
#include <iostream>
#include "origami.h"

Origami::Origami(std::ifstream& input_file) : instructions{} {
    // Read all points
    // Get max X and Y for matrix
    std::vector<std::pair<int, int>> point_list;
    int x, y;
    char separator;
    std::string line;
    while (getline(input_file, line)) {
        if (line.empty()) {
            break; // finished reading all points
        }

        std::istringstream iss(line);
        iss >> x >> separator >> y;
        point_list.push_back(std::pair<int, int>(x, y));

        if (x > max_x) max_x = x;
        if (y > max_y) max_y = y;
    }

    // Read all folding instructions
    char axis;
    int value;
    while (std::getline(input_file, line)) {
        int equal_pos = line.find('=');
        axis = line[equal_pos - 1];
        value = stoi(line.substr(equal_pos + 1, std::string::npos));
        instructions.push_back(std::pair<char, int>(axis, value));
    }

    // Create paper matrix
    paper = std::vector<std::vector<char>>(max_y + 1,
                                           std::vector<char>(max_x + 1, '.'));

    for (auto point : point_list) {
        int p_x = point.first;
        int p_y = point.second;
        paper[p_y][p_x] = '#';
    }
}

void Origami::fold() {
    for (auto instruction : instructions) {
        char axis = instruction.first;
        int fold = instruction.second;
        if (axis == 'x') {
            fold_on_x(fold);
        } else {
            fold_on_y(fold);
        }
    }
}


// TODO: instead of iterating over the matrix conver the point vector into
// their mirror points based on the folds then used those to construct the
// matrix.
//
// max_x and max_y will always be x_line - 1 and y_line - 1, respectively.
void Origami::fold_on_y(int y_line) {
    // int max_y = paper.size() - 1;
    for (int y = max_y; y > y_line; y--) {
        int mirror_y = y_line - (y - y_line);
        for (int x = 0; x <= max_x; x++) {
            if (paper[y][x] == '#') paper[mirror_y][x] = paper[y][x];
        }
    }
    max_y = y_line - 1;
}

void Origami::fold_on_x(int x_line) {
    for (int y = 0; y <= max_y; y++) {
        for (int x = max_x; x > x_line; x--) {
            int mirror_x = x_line - (x - x_line);
            if (paper[y][x] == '#') paper[y][mirror_x] = paper[y][x];
        }
    }
    max_x = x_line - 1;
}

std::ostream& operator<<(std::ostream& os, const Origami& origami) {
    int n_dots = 0;
    os << "Dot Matrix:\n";
    for (int y = 0; y <= origami.max_y; y++) {
        for (int x =0; x <= origami.max_x; x++) {
            os << origami.paper[y][x];
            if (origami.paper[y][x] == '#') n_dots++;
        }
        os << '\n';
    }
    os << "Number of dots: " << n_dots << '\n';

    return os;
}
