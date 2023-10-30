#include <omp.h>

#include "findUnique.hpp"


std::unordered_set<int> FindUnique::findUniqueNumbers(const std::vector<int>& array) 
{
    std::unordered_set<int> result;

    #pragma omp parallel for
    for (int iter = 0; iter < array.size(); iter++) {
        #pragma omp critical
        result.insert(array[iter]);
    }

    return result;
}