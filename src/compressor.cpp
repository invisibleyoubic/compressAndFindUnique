#include "compressor.hpp"


Compressor::Compressor()
    : m_originalSize(0)
    , m_compressedSize(0)
{}

std::vector<int8_t> Compressor::compress(const std::vector<int>& array)
{
    m_originalSize = 0;
    m_compressedSize = 0;

    for (const int& item : array)
    {
        m_originalSize+= sizeof(item);
    }

    const std::vector<std::pair<int, int>> RLEEncodedArray = RLE(array);
    const std::vector<int8_t> VLEEncodedArray = VLE(RLEEncodedArray);

    for (const int8_t& item : VLEEncodedArray)
    {
        m_compressedSize += sizeof(item);
    }

    return VLEEncodedArray;
}

size_t Compressor::originalSize() const
{
    return m_originalSize;
}

size_t Compressor::compressedSize() const
{
    return m_compressedSize;
}
    
std::vector<std::pair<int, int>> Compressor::RLE(const std::vector<int>& array) const
{
    std::vector<std::pair<int, int>> result;

    int sequenceCounter = 1;

    const int arraySize = array.size();
    for (int iter = 0; iter < arraySize - 1; iter++)
    {
        const int firstNum = array[iter];
        const int secondNum = array[iter + 1];

        if (firstNum == secondNum)
        {
            sequenceCounter++;
        }
        else
        {
            result.emplace_back(firstNum, sequenceCounter);
            sequenceCounter = 1;
        }
    }

    result.emplace_back(array.back(), sequenceCounter);

    return result;
}

std::vector<int8_t> Compressor::VLE(const std::vector<std::pair<int, int>>& array) const
{
    std::vector<int8_t> result;

    for (const std::pair<int, int>& pair : array) {
        int number = pair.first;
        int count = pair.second;

        result.push_back(number);

        while (count >= 128) {
            result.push_back((count & 0x7F) | 0x80);
            count >>= 7;
        }
        result.push_back(count);
    }

    return result;
}