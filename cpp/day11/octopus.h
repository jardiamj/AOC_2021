#ifndef OCTOPUS_H
#define OCTOPUS_H

#include "octo_map.h"

class Octopus {
public:
    // Publicly available accessors
    int get_level() const;
    bool has_flashed() const;

private:
    // Make OctoMap a friend class so that it can instantiate Octupi.
    friend class OctoMap;

    // Private constructor only availabre to friend class OctoMap
    Octopus(int row, int col, int level, OctoMap& oct_map);

    // Mutators only available through friend class OctoMap
    int increase_level();
    void set_flashed(bool flashed);    

    // Map that holds all octopus in the simulation
    OctoMap& octo_map;

    // Octopus coordinates within map
    int col;
    int row;

    // Octopus level
    int level;

    // flag if octopus has flashed during this simulation step
    bool has_flashed_ = false;
};

#endif /* OCTOPUS_H */