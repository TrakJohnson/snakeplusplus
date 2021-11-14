#include "config.h"
#include "stdlib.h"

#include <array>
#include <vector>

void createFood(std::vector<int> &bg, std::array<int, 2> &food, const int &nx,
                const int &ny) {
  if (food[0] == 0) {
    food[0] = rand() % (nx - 2) + 1;
    food[1] = rand() % (ny - 2) + 1;
    bg[food[0] + food[1] * nx] = 2;
  }
}

bool eatFood(std::array<int, 2> &food,
             const std::vector<std::pair<int, int>> &snake) {
  auto [x, y] = snake.front();
  if ((food[0] == x) && (food[1] == y)) {
    food[0] = 0;
    food[1] = 1;
    return true;
  }
  return false;
}
