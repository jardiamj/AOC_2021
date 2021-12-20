#include "hydrothermal_map.h"
#include <string>
#include <sstream>
#include <iostream>

HidrothermalMap::HidrothermalMap(std::ifstream &input_file) {
    std::string line;
    std::string delimiter = " -> ";
    int max_x{0}, max_y{0};
    while (std::getline(input_file, line)) {
        size_t pos = line.find(delimiter);
        std::string point1_str = line.substr(0, pos);
        std::string point2_str = line.substr(pos + delimiter.length(),
                                             line.length());
        std::stringstream ss_p1(point1_str);
        std::stringstream ss_p2(point2_str);
        int p1_x, p1_y, p2_x, p2_y;
        char c;
        ss_p1 >> p1_x >> c >> p1_y;
        ss_p2 >> p2_x >> c >> p2_y;
        int greater_x = p1_x > p2_x ? p1_x : p2_x;
        int greater_y = p1_y > p2_y ? p1_y : p2_y;
        if (greater_x > max_x) max_x = greater_x;
        if (greater_y > max_y) max_y = greater_y;            
        // std::cout << p1_x << c << p1_y << " -> ";
        // std::cout << p2_x << c << p2_y << '\n';
        point point_1 = point(p1_x, p1_y);
        point point_2 = point(p2_x, p2_y);
        v_lines.push_back(std::pair<point, point>(point_1, point_2));
    }

    v_map = std::vector<std::vector<int>>(max_y + 1, std::vector<int>(max_x + 1));
        
}

int HidrothermalMap::point_overlaps() {
    for (auto line : v_lines) {
        point pt1 = line.first;
        point pt2 = line.second;
        int y1, y2, x1, x2;
        if (pt1.second < pt2.second) {
            y1 = pt1.second; y2 = pt2.second;
        } else {
            y1 = pt2.second; y2 = pt1.second;
        }

        if (pt1.first < pt2.first) {
            x1 = pt1.first; x2 = pt2.first;
        } else {
            x1 = pt2.first; x2 = pt1.first;
        }

        if (pt1.first == pt2.first) {
            int x = pt1.first;           
            for (int y = y1; y <= y2; y++) {
                v_map[y][x] += 1;
            }
        }

        if (pt1.second == pt2.second) {
            int y = pt1.second;
            for (int x = x1; x <= x2; x++) {
                v_map[y][x] += 1;
            }
        }

        if (x2 - x1 == y2 - y1) {
            int x_change = pt2.first > pt1.first ? 1 : -1;
            int y_change = pt2.second > pt1.second ? 1 : -1;
            for (int x = pt1.first, y = pt1.second;
                 x * x_change <= pt2.first * x_change; // Adjusts for the direction
                 x += x_change, y += y_change)
            {
                v_map[y][x] += 1;
            }
        }
    }

    int point_overlaps = 0;
    for (auto row : v_map) {
        for (auto val : row) {
            if (val > 1) point_overlaps += 1;
        }
    }

    return point_overlaps;
}
