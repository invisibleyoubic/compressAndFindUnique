#include <unordered_set>
#include <vector>


class FindUnique
{
public: 
    FindUnique() = default;
    std::unordered_set<int> findUniqueNumbers(const std::vector<int>& array);
};