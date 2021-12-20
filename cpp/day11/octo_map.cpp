#include "octo_map.h"
#include <iostream>
#include <fstream>
#include <string>
#include "octopus.h"
// #include <sstream>

OctoMap::OctoMap(std::ifstream& in_file) {
    std::string line;

    int row = 0;
    while (in_file >> line) {
        std::vector<std::shared_ptr<Octopus>> oct_row;
        for (int col = 0; col < line.size(); col++) {
            int level = line[col] - '0';
            oct_row.push_back(std::shared_ptr<Octopus>(
                    new Octopus(row, col, level, *this)
                )
            );
        }
        map_.push_back(oct_row);
        row++;
    }
}

int OctoMap::width() const {return map_[0].size();}

int OctoMap::height() const {return map_.size();}

int OctoMap::get_flashes() const {return flashes;}

void OctoMap::advance_step() {
    for (auto row : map_) {
        for (auto octo_ptr : row) {
            octo_ptr->increase_level();
        }
    }

    // reset flashing state for next step
    reset_flashing();
}

void OctoMap::increment_neighbors(int row, int col) {
    // If this method got called by and octopus a new flash occurred so
    // we increment the flash count.
    flashes++;

    for (int idx = 0; idx < neighbors; idx++) {
        int next_row = row + d_row[idx];
        int next_col = col + d_col[idx];
        if (is_valid_cell(next_row, next_col)) {
            auto octo = map_[next_row][next_col];
            // if (!octo->has_flashed()) {
                octo->increase_level();
            // }
        }
    }
}

void OctoMap::reset_flashing() {
    for (auto row : map_) {
        for (auto octo_ptr : row) {
            octo_ptr->set_flashed(false);
        }
    }
}

bool OctoMap::is_valid_cell(int row, int col) const {
    int max_row = height(); int max_col = width();
    // indices start at 0
    return row >= 0 && col >= 0 & row < max_row && col < max_col;
}

std::ostream& operator<<(std::ostream& os, const OctoMap& oct_map) {
    for (auto row : oct_map.map_) {
        auto iter = row.begin();
        os << "[" << (*iter++)->get_level();
        for (; iter != row.end(); iter++) {
            os << ", " << (*iter)->get_level();
        }
        os << "]\n";
    }
    return os;
}