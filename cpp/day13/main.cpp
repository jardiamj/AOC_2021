#include <iostream>
#include <fstream>
#include <vector>
#include <utility>
#include <sstream>

#include "origami.h"

using namespace std;

void fold_on_x(char* paper[], int max_x, int max_y, int x_line);
void print_matrix(char* paper[], int max_x, int max_y);

int main(int argc, char* argv[]) {
    string file_name = "input.txt";
    
    ifstream in_file(file_name);
    if (!in_file.good()) {
        cerr << "File " << file_name << "Could not be oppened.\n";
        exit(EXIT_FAILURE);
    }

    Origami origami_paper(in_file);

    // cout << origami_paper;

    origami_paper.fold();
    cout << origami_paper;
}
