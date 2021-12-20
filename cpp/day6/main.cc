#include <iostream>
#include <vector>
#include <fstream>
#include <gmpxx.h>

int main() {
    std::vector<uint64_t> fishMap(9);
    for (int i = 0; i < fishMap.size(); i++) {
        std::cout << fishMap[i] << ", ";
    }
    std::cout << '\n';

    std::ifstream in_file;
    in_file.open("init_fish.txt");

    int cur_timer;
    while (in_file >> cur_timer) {
        fishMap[cur_timer] += 1;
        if (in_file.peek() == ',') {
            in_file.ignore();
        }
    }

    for (int i = 0; i < fishMap.size(); i++) {
        std::cout << fishMap[i] << ", ";
    }
    std::cout << '\n';

    for (int i = 1; i <= 256; i++) {
        uint64_t n_baby_fish = fishMap[0];
        for (int tmr_idx = 0; tmr_idx < fishMap.size() - 1; tmr_idx++) {
            fishMap[tmr_idx] = fishMap[tmr_idx + 1];
        }
        fishMap[6] += n_baby_fish;
        fishMap[8] = n_baby_fish;

        std::cout << "day " << i << ": ";
        mpz_class total_fish = 0;
        for (auto fish_qty : fishMap) {
            total_fish += fish_qty;
        }
        std::cout << total_fish << '\n';
    }
}
