#include <array>
#include <vector>

void createFood(std::vector<int> &bg, std::array<int, 2> &food, const int &nx,
                const int &ny);
bool eatFood(std::array<int, 2> &food,
             const std::vector<std::pair<int, int>> &snake);
