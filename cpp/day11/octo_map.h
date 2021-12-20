#ifndef OCTOMAP_H
#define OCTOMAP_H

#include <vector>
#include <memory>

class Octopus;

class OctoMap {
public:
    OctoMap(std::ifstream& in_file);

    // returns the number of columns in the map
    int width() const;

    // returns the number of rows in the map
    int height() const;

    // Returns the total number of flashes for the duration of the
    // simulation.
    int get_flashes() const;

    // advances the simulation by 1 step
    void advance_step();

    // increments the give octopus neighbors
    // gets called by octopi when they flash
    void increment_neighbors(int row, int col);

private:
    // Horizontal and vertical neighbors as delta col/row
    const int neighbors = 8;
    const int d_col[8] = {1,  1,  0, -1, -1, -1, 0, 1};
    const int d_row[8] = {0, -1, -1, -1,  0,  1, 1, 1};

    // 2D array of Octopii
    std::vector<std::vector<std::shared_ptr<Octopus>>> map_;

    // Stores the total number of octopus flashes
    int flashes = 0;

    // helper method for checking for valid cells
    bool is_valid_cell(int row, int col) const;

    // helper method for resetting
    void reset_flashing();

    // friend output stream operator
    friend std::ostream& operator<<(std::ostream& os, const OctoMap& oct_map);
};

#endif /* OCTOMAP_H */