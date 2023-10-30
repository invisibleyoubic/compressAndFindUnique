#include <gtest/gtest.h>

#include "../include/compressor.hpp"
#include "../include/decompressor.hpp"


namespace
{
constexpr int size = 1000000;
static std::vector<int> array;
}

void generate()
{
    unsigned int seed = std::chrono::system_clock::now().time_since_epoch().count();
    srand(seed);

    for (int iter = 0; iter < size; iter++)
    {
        array.push_back(rand() % 101);
    }
}

TEST(CompressTests, equality)
{
    Compressor compressor;
    const std::vector<int8_t> compressed = compressor.compress(array);
    
    Decompressor decompressor;
    const std::vector<int> decompressed = decompressor.decompress(compressed);

    bool isEqual = true;
    for (int iter = 0; iter < size; iter++)
    {
        if (decompressed[iter] == array[iter])
            continue;
        
        isEqual = false;
        break;
    }

    EXPECT_EQ (isEqual, 1);
}

TEST(CompressTests, size) 
{
    Compressor compressor;
    const std::vector<int8_t> compressed = compressor.compress(array);

    EXPECT_EQ (compressor.originalSize() > compressor.compressedSize(),  1);
}

int main(int argc, char** argv) 
{
    generate();

    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}