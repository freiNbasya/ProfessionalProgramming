#include "Helpers.hpp"
#include <algorithm>
#include <ranges>


double dummyFunc(double x) {
    return x > 0 ? x : 0;
}

std::string repeatString(const std::vector<int>& numbers, const std::string& str) {
    if (numbers.empty()) {
        return "";
    }

    auto maxNum = *std::ranges::max(numbers);
    std::string result;
    
    for (int i = 0; i < maxNum; ++i) {
        result += str;
    }
    
    return result;
}
