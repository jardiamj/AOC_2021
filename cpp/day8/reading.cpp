
#include <sstream>
#include <math.h>
#include <algorithm>

#include "reading.h"

Reading::Reading(std::string line) {
    size_t div_pos = line.find('|');
    std::istringstream unique_iss(line.substr(0, div_pos));
    std::istringstream output_iss(line.substr(div_pos + 1, std::string::npos));

    std::string digit;
    for (int i = 0; i < 10 && unique_iss >> digit; i++) {
        std::sort(digit.begin(), digit.end());
        digits[i] = digit;
        switch (digit.size()) {
            case 2: digit_map[1] = digit; break;
            case 3: digit_map[7] = digit; break;
            case 4: digit_map[4] = digit; break;
            case 5: digits_253.push_back(digit); break;
            case 6: digits_690.push_back(digit); break;
            case 7: digit_map[8] = digit;
        }
    }

    std::string out_digit;
    for (int i = 0; i < 4 && output_iss >> out_digit; i++) {
        std::sort(out_digit.begin(), out_digit.end());
        output[i] = out_digit;
    }

    map_digits();
}

void Reading::map_digits() {
    char missing_on_6;
    // find 6 --> doesn't contain both 1's segments
    for (auto iter = digits_690.begin(); iter != digits_690.end(); iter++) {
        if (!contains(*iter, digit_map[1][0])) {
            digit_map[6] = *iter;
            missing_on_6 = digit_map[1][0];
            digits_690.erase(iter);
            break;
        }

        if (!contains(*iter, digit_map[1][1])) {
            digit_map[6] = *iter;
            missing_on_6 = digit_map[1][1];
            digits_690.erase(iter);
            break;
        }
    }

    // 3 --> contains both 1's segments
    for (auto iter = digits_253.begin(); iter != digits_253.end(); iter++) {
        if (contains(*iter, digit_map[1][0]) &&
            contains(*iter, digit_map[1][1])) {
                digit_map[3] = *iter;
                digits_253.erase(iter);
                break;
        }
    }
    
    // 2 --> contains segment missing in 6
    for (auto iter = digits_253.begin(); iter != digits_253.end(); iter++) {
         if (contains(*iter, missing_on_6)) {
            digit_map[2] = *iter;
            digits_253.erase(iter);
            break;
        }
    }

    // 5 --> Is the only one left in digits_253
    digit_map[5] = digits_253[0];

    // 9 --> has all 4's segments
    // 0 --> is missing 1 of 4's segments
    for (char c : digit_map[4]) {
        if (!contains(digits_690[0], c)) {
            digit_map[0] = digits_690[0];
            digit_map[9] = digits_690[1];
            break;
        }
        if (!contains(digits_690[1], c)) {
            digit_map[0] = digits_690[1];
            digit_map[9] = digits_690[0];
            break;
        }
    }

    // fill string map
    for (int idx = 0; idx < 10; idx++) {
        str_map[digit_map[idx]] = idx;
    }
}

int Reading::get_value() {
    int result = 0;
    int val_len = 4;
    for (int i = 0; i < val_len; i++) {
        int idx = (val_len - i) - 1;
        result += str_map.at(output[idx]) * pow(10, i);
    }
    return result;
}

bool Reading::contains(const std::string& str, const char c) const {
    return (str.find(c) != std::string::npos);
}

std::ostream& operator<<(std::ostream& os, const Reading& r) {
    auto iter = r.str_map.begin();
    os << "Map: {" << iter->first << ": " << iter->second;
    for (auto& x : r.str_map) {
        os << ", " << x.first << ": " << x.second;
    }
    os << "}";

    os << "\n";

    int idx = 0;
    os << "Output: [" << r.output[idx++];
    for (; idx < 4; idx++) {
        os << ", " << r.output[idx];
    }
    os << "]";

    return os;
}