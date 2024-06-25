#include "Helpers.hpp"
#include <algorithm>

double dummyFunc(double x) {
    return x > 0 ? x : 0;
}


std::string repeatString(const std::vector<int>& numbers, const std::string& str) {
    if (numbers.empty()) {
        return "";
    }
    
    int maxNum = *std::max_element(numbers.begin(), numbers.end());
    std::string result;
    
    for (int i = 0; i < maxNum; ++i) {
        result += str;
    }
    
    return result;
}
