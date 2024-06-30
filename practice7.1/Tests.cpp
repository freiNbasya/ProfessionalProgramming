#include "UnitTests.hpp"
#include "MaybeTheBestCodeEver.cpp" 

void testRectangleArea() {
    Rectangle rect(3.0, 4.0);
    ASSERT_EQ(rect.getArea(), 12.0);
}

void testRectangleCanBePlacedInside() {
    Rectangle rect1(2.0, 3.0);
    Rectangle rect2(4.0, 5.0);
    ASSERT_EQ(rect1.canBePlacedInside(rect2), true);
    ASSERT_EQ(rect2.canBePlacedInside(rect1), false);
}

void testRectangleBiggestSide() {
    Rectangle rect(2.0, 5.0);
    ASSERT_EQ(std::max(rect.getWidth(), rect.getHeight()), 5.0);
}

void testBiggestAndSmallestArea() {
    std::vector<Rectangle> rectangles = {
        Rectangle(3.0, 4.0),
        Rectangle(5.0, 6.0),
        Rectangle(2.0, 3.0),
        Rectangle(4.0, 4.0),
        Rectangle(1.0, 1.0)
    };

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

    ASSERT_EQ(biggestArea, 5.0 * 6.0);
    ASSERT_EQ(smallestArea, 1.0 * 1.0);
}

void testTotalArea() {
    std::vector<Rectangle> rectangles = {
        Rectangle(3.0, 4.0),
        Rectangle(5.0, 6.0),
        Rectangle(2.0, 3.0),
        Rectangle(4.0, 4.0),
        Rectangle(1.0, 1.0)
    };

    double totalArea = 0;
    for (const auto& rect : rectangles) {
        totalArea += rect.getArea();
    }

    ASSERT_EQ(totalArea, 3.0 * 4.0 + 5.0 * 6.0 + 2.0 * 3.0 + 4.0 * 4.0 + 1.0 * 1.0);
}

int main() {
    UnitTests tests;

    tests.addTest("Test Rectangle Area", testRectangleArea);
    tests.addTest("Test Rectangle Can Be Placed Inside", testRectangleCanBePlacedInside);
    tests.addTest("Test Rectangle Biggest Side", testRectangleBiggestSide);
    tests.addTest("Test Biggest and Smallest Area", testBiggestAndSmallestArea);
    tests.addTest("Test Total Area", testTotalArea);

    tests.run();

    return 0;
}
