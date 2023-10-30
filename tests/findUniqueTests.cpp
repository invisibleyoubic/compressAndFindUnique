#include <random>

#include <gtest/gtest.h>

#include "../include/findUnique.hpp"


namespace
{
constexpr int uniqueSize = 1000;
constexpr int randomSize = 10000000;
static std::vector<int> randomArray(randomSize);
static std::vector<int> uniqueArray(uniqueSize);
}

void generate()
{
    for (int iter = 0; iter < uniqueSize; ++iter) {
        uniqueArray[iter] = iter;
    }

    unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
    std::shuffle(uniqueArray.begin(), uniqueArray.end(), std::default_random_engine(seed));

    for (int iter = 0; iter < randomSize; ++iter) {
        randomArray[iter] = uniqueArray[iter % uniqueSize];
    }
}

TEST(FindUniqueTests, sizeEquality)
{
    FindUnique findUnique;
    const std::unordered_set<int> uniqueNumbers = findUnique.findUniqueNumbers(randomArray);

    const bool isSizeEqual = uniqueNumbers.size() == uniqueSize;

    EXPECT_EQ (isSizeEqual, 1);
}

TEST(FindUniqueTests, contains)
{
    FindUnique findUnique;
    const std::unordered_set<int> uniqueNumbers = findUnique.findUniqueNumbers(randomArray);

    bool isEqual = true;
    for (const int& item : uniqueArray)
    {
        if (uniqueNumbers.count(item) != 0)
            continue;

        isEqual = false;
        break;
    }

    EXPECT_EQ (isEqual, 1);
}

int main(int argc, char** argv) 
{
    generate();

    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}