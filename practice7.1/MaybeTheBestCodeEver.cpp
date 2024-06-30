#include <iostream>
#include <vector>
#include <ranges>
#include <algorithm>
#include <limits>
#include <numeric> 

class Rectangle {
private:
    double width;
    double height;
    double area;

public:
    Rectangle(double width = 0.0, double height = 0.0) : width(width), height(height) {
        area = width * height;
    }

    double getWidth() const { return width; }
    double getHeight() const { return height; }
    double getArea() const { return area; }

    bool canBePlacedInside(const Rectangle& other) const {
        return width <= other.getWidth() && height <= other.getHeight();
    }
};

#ifndef UNIT_TEST
int main() {
    std::vector<Rectangle> rectangles;
    double width, height;
    int numRectangles = 5;

    rectangles.reserve(numRectangles);

    for (int i = 0; i < numRectangles; ++i) {
        std::println("Enter rectangle ", i + 1, " (width height):");
        std::cin >> width >> height;
        rectangles.emplace_back(width, height);
    }

    auto areas = rectangles | std::views::transform([](const Rectangle& rect) { return rect.getArea(); });

    auto [smallestArea, biggestArea] = std::ranges::minmax(areas);

    for (size_t i = 0; i < rectangles.size(); ++i) {
        for (size_t j = 0; j < rectangles.size(); ++j) {
            if (i != j && rectangles[i].canBePlacedInside(rectangles[j])) {
                std::println("Rectangle ", i + 1, " can be placed inside Rectangle ", j + 1);
            }
        }
    }

    for (size_t i = 0; i < rectangles.size(); ++i) {
        double biggestSide = std::max(rectangles[i].getWidth(), rectangles[i].getHeight());
        std::println("The biggest side of rectangle ", i + 1, ": ", biggestSide);
    }

    double totalArea = std::accumulate(areas.begin(), areas.end(), 0.0);
    
    std::println("Total area of rectangles: ", totalArea);
    std::println("The biggest area: ", biggestArea);
    std::println("The smallest area: ", smallestArea);

    return 0;
}
#endif
