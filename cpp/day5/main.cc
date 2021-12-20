
#include "hydrothermal_map.h"
#include <iostream>

int main(int argc, char* argv[]) {
    std::ifstream in_file;
    in_file.open("hydrothermal_vent.txt");
    // in_file.open("vents_test.txt");
    HidrothermalMap hm(in_file);
    std::cout << "Day 4, Hydrothermal Point Overlaps: "
              << hm.point_overlaps() << '\n';

    return 0;
}
