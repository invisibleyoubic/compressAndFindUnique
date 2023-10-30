#pragma once

#include <vector>
#include <stdint.h>


class Compressor
{
public:
    Compressor();

    std::vector<int8_t> compress(const std::vector<int>& array);

    size_t originalSize() const;
    size_t compressedSize() const;
    
private:
    std::vector<std::pair<int, int>> RLE(const std::vector<int>& array) const;
    std::vector<int8_t> VLE(const std::vector<std::pair<int, int>>& array) const;

private:
    size_t m_originalSize;
    size_t m_compressedSize;
};