#include <iostream>
#include <fstream>
#include <string>
#include "octo_map.h"
#include "octopus.h"

using namespace std;

int main(int argc, char* argv[]) {
    string file_name = "octo_input.txt";
    ifstream in_file(file_name);
    
    if (!in_file.good()) {
        cerr << "File " << file_name << " coldn't be opened.\n";
        exit(EXIT_FAILURE);
    }

    OctoMap octo_map(in_file);

    cout << "Initial State:\n";
    cout << octo_map << '\n';

    int prev_flashes = 0;
    int sync_step = 0;
    for (int step = 1; step <= 500; step++) {
        octo_map.advance_step();
        if (sync_step == 0 && octo_map.get_flashes() - prev_flashes == 100) {
            sync_step = step;
        }
        prev_flashes = octo_map.get_flashes();

        cout << "Step " << step << ", ";
        cout << "Total Flashes: " << octo_map.get_flashes() << "\n";
    }
    cout << "Synchronizing step: " << sync_step << '\n';
}