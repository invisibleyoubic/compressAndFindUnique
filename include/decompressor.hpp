#pragma once

#include <vector>
#include <stdint.h>


class Decompressor
{
public:
    Decompressor();

    std::vector<int> decompress(const std::vector<int8_t>& array);

    size_t originalSize() const;
    size_t decompressedSize() const;

private:
    std::vector<std::pair<int, int>> VLD(const std::vector<int8_t>& array) const;
    std::vector<int> RLD(const std::vector<std::pair<int, int>>& array) const;

private:
    size_t m_originalSize;
    size_t m_decompressedSize;
};