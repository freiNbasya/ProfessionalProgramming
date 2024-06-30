#include <print>
#include <Helpers.hpp>
#include <UnitTests.hpp>
#include <string>
#include <vector>
int main() {
    UnitTests testSuite;

    testSuite.addTest("Dummy_test1",
    [](){
        // Build:
        double value = 0.0;
    
        // Operate:
        auto result = dummyFunc(value);

        // Check:
        ASSERT_EQ(result, 0)
    });

    testSuite.addTest("Dummy_test2",
    [](){
        // Build:
        double value = 5.5;
    
        // Operate:
        auto result = dummyFunc(value);

        // Check:
        ASSERT_EQ(result, 5.5)
    });

    testSuite.addTest("Dummy_test3",
    [](){
        // Build:
        double value = -3;
    
        // Operate:
        auto result = dummyFunc(value);

        // Check:
        ASSERT_EQ(result, 0)
    });

    testSuite.addTest("test_doubleWord",
    [](){
        // Build:
        std::vector<int> numbers = {0, 2, 1};
        std::string str = "home";
    
        // Operate:
        auto result = repeatString(numbers, str);

        // Check:
        ASSERT_EQ(result, "homehome")
    });

        testSuite.addTest("test_noWord",
    [](){
        // Build:
        std::vector<int> numbers = {0, 0, 0};
        std::string str = "home";
    
        // Operate:
        auto result = repeatString(numbers, str);

        // Check:
        ASSERT_EQ(result, "")
    });

        testSuite.addTest("test_noWordNegativeVector",
    [](){
        // Build:
        std::vector<int> numbers = {-3, -2, -1};
        std::string str = "home";
    
        // Operate:
        auto result = repeatString(numbers, str);

        // Check:
        ASSERT_EQ(result, "")
    });

        testSuite.addTest("test_tripleWordMixed",
    [](){
        // Build:
        std::vector<int> numbers = {3, -2, -1};
        std::string str = "home";
    
        // Operate:
        auto result = repeatString(numbers, str);

        // Check:
        ASSERT_EQ(result, "homehomehome")
    });

        testSuite.addTest("test_emptyVector",
    [](){
        // Build:
        std::vector<int> numbers = {};
        std::string str = "home";
    
        // Operate:
        auto result = repeatString(numbers, str);

        // Check:
        ASSERT_EQ(result, "")
    });

    testSuite.run();
}
