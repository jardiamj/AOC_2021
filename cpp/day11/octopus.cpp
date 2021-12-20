#include "octopus.h"
#include <iostream>

Octopus::Octopus (int row, int col, int level, OctoMap& oct_map) : 
    row(row), col(col), level(level), octo_map(oct_map) { }

int Octopus::get_level() const {return level;}

int Octopus::increase_level() {
    if (has_flashed()) { // Can only flash one per step
        return level;
    }

    if (level < 9) {
        level++;
        return level;
    } else { // flash
        level = 0;
        set_flashed(true);
        octo_map.increment_neighbors(row, col);
    }
    return level;
}

bool Octopus::has_flashed() const {
    return has_flashed_;
}

void Octopus::set_flashed(bool flashed) { has_flashed_ = flashed;}