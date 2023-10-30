#include "decompressor.hpp"


Decompressor::Decompressor()
    : m_originalSize(0)
    , m_decompressedSize(0)
{}

std::vector<int> Decompressor::decompress(const std::vector<int8_t>& array)
{
    m_decompressedSize = 0;
    m_originalSize = 0;

    for (const int8_t& item : array)
    {
        m_originalSize += sizeof(item);
    }

    const std::vector<std::pair<int, int>> VLDDecodedArray = VLD(array);
    const std::vector<int> RLDDecodedArray = RLD(VLDDecodedArray);

    for (const int8_t& item : RLDDecodedArray)
    {
        m_decompressedSize += sizeof(item);
    }

    return RLDDecodedArray;
}

size_t Decompressor::originalSize() const
{
    return m_originalSize;
}

size_t Decompressor::decompressedSize() const
{
    return m_decompressedSize;
}

std::vector<std::pair<int, int>> Decompressor::VLD(const std::vector<int8_t>& array) const
{
    std::vector<std::pair<int, int>> result;

    int index = 0;
    const int arrauSize = array.size();
    while (index < array.size()) {
        int number = 0;
        int shift = 0;

        if (index < array.size()) {
            number |= array[index] << shift;
            index++;
        }

        int count = 0;
        shift = 0;
        while (index < array.size() && (array[index] & 0x80)) {
            count |= (array[index] & 0x7F) << shift;
            shift += 7;
            index++;
        }
        if (index < array.size()) {
            count |= array[index] << shift;
            index++;
        }

        result.emplace_back(number, count);
    }

    return result; 
}

std::vector<int> Decompressor::RLD(const std::vector<std::pair<int, int>>& array) const
{
    std::vector<int> result;

    for (const std::pair<int, int>& pair : array)
    {
        const int number = pair.first;
        const int count = pair.second;

        for (int iter = 0; iter < count; iter++)
        {
            result.push_back(number);
        }
    }

    return result;
}