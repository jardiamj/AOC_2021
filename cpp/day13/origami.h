#ifndef ORIGAMI_H
#define ORIGAMI_H

#include <fstream>
#include <vector>
#include <utility>

class Origami {
public:
    Origami(std::ifstream& input_file);

    // Folds the origamy paper according to the folding instructions.
    void fold();

private:
    int max_x = 0;
    int max_y = 0;
    std::vector<std::vector<char>> paper;    
    std::vector<std::pair<char, int>> instructions;

    // Helper methods for folding on x or y
    void fold_on_y(int y_line);
    void fold_on_x(int x_line);

    friend std::ostream& operator<<(std::ostream& os, const Origami& origami);
};

#endif /* ORIGAMI_H */