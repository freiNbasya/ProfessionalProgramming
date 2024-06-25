
#include <iostream>
#include <vector>
#include <limits>

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

    for (int i = 0; i < numRectangles; ++i) {
        std::cout << "Enter rectangle " << i + 1 << " (width height):" << std::endl;
        std::cin >> width >> height;
        rectangles.emplace_back(width, height);
    }

    double biggestArea = 0;
    double smallestArea = std::numeric_limits<double>::max();
    for (const auto& rect : rectangles) {
        if (rect.getArea() > biggestArea) {
            biggestArea = rect.getArea();
        }
        if (rect.getArea() < smallestArea) {
            smallestArea = rect.getArea();
        }
    }

    for (size_t i = 0; i < rectangles.size(); ++i) {
        for (size_t j = 0; j < rectangles.size(); ++j) {
            if (i != j && rectangles[i].canBePlacedInside(rectangles[j])) {
                std::cout << "Rectangle " << i + 1 << " can be placed inside Rectangle " << j + 1 << std::endl;
            }
        }
    }

    for (size_t i = 0; i < rectangles.size(); ++i) {
        double biggestSide = std::max(rectangles[i].getWidth(), rectangles[i].getHeight());
        std::cout << "The biggest side of rectangle " << i + 1 << ": " << biggestSide << std::endl;
    }

    double totalArea = 0;
    for (const auto& rect : rectangles) {
        totalArea += rect.getArea();
    }
    
    std::cout << "Total area of rectangles: " << totalArea << std::endl;
    std::cout << "The biggest area: " << biggestArea << std::endl;
    std::cout << "The smallest area: " << smallestArea << std::endl;

    return 0;
}
#endif