#ifndef READING_H
#define READING_H

#include <map>
#include <string>
#include <vector>

class Reading {
public:
    Reading(std::string line);

    int get_value();

private:
    std::string digits[10];
    std::string output[4];
    std::string digit_map[10];
    std::map<std::string, int> str_map;

    std::vector<std::string> digits_253;
    std::vector<std::string> digits_690;

    void map_digits();

    bool contains(const std::string& str, const char c) const;
    void print_array(std::ostream& os, std::string str_arr[], int n);

    friend std::ostream& operator<<(std::ostream& os, const Reading& r);
};

#endif /* READING_H */