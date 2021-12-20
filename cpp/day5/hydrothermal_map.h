
#ifndef HIDROTHERMAL_MAP
#define HIDROTHERMAL_MAP

#include <vector>
#include <utility>
#include <fstream>

class HidrothermalMap {
public:
    
    HidrothermalMap(std::ifstream &input_file);

    int point_overlaps();

private:
    typedef std::pair<int, int> point;
    std::vector<std::pair<point, point>> v_lines;
    std::vector<std::vector<int>> v_map;
};
#endif /* HIDROTHERMAL_MAP */