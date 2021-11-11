#include "sys/ioctl.h"
#include <array>
#include <iostream>
#include <vector>

#include "stdlib.h"

#include "config.h"
#include "display.h"
#include "food.h"
#include "internals.h"

// TODO
// - fix frames
// - add animation for eating
// - menu
// 


void backgroundSetup(const int nx, const int ny, std::vector<int> &bg) {
  decltype(bg.size()) i;
  for (i = 0; i < nx; i++) {
    bg[i] = 1;
  }
  for (i = 0; i < nx; i++) {
    bg[(ny - 1) * nx + i] = 1;
  }
  for (i = 0; i < ny; i++) {
    bg[i * nx] = 1;
  }
  for (i = 0; i < ny; i++) {
    bg[i * nx + nx - 1] = 1;
  }
}

void add_snake(const std::vector<std::pair<int, int>> &snake,
               std::vector<int> &bg, const int &nx, const int &ny) {
  for (auto [i, j] : snake) {
    bg[i + j * nx] = 3;
  }
  auto [start_x, start_y] = snake.front();
  bg[start_x + nx * start_y] = 4;
}

void remove_snake(const std::vector<std::pair<int, int>> &snake,
                  std::vector<int> &bg, const int &nx, const int &ny) {
  for (auto [x, y] : snake) {
    bg[x + nx * y] = 0;
  }
}


std::array<int, 2> snake_movement(const char &k, int dx, int dy) {
  int dx_new = 0;
  int dy_new = 0;
  if (k == 'd' || k == '6') {
    // Right
    dx_new = 1;
  } else if (k == 'q' || k == '4') {
    // Left
    dx_new = -1;
  } else if (k == 's' || k == '2') {
    // Down
    dy_new = 1;
  } else if (k == 'z' || k == '8') {
    // Up
    dy_new = -1;
  }
  
  std::array<int, 2> dxdy_old{dx, dy};
  // empêche l'utilisateur de se rentrer dedans "sur place"
  if (dx_new*dx != 0 || dy_new*dy != 0) {
    return dxdy_old;
  }
  std::array<int, 2> dxdy{dx_new, dy_new};
  return dxdy;
}

bool verifyBorder(const std::vector<std::pair<int, int>> &snake, int nx,
                  int ny) {
  auto [x0, y0] = snake.front();
  for (int i = 1; i < snake.size(); i++) {
    if (snake[i].first == x0 && snake[i].second == y0) {
      return false;
    }
  }
  return true;
}

void setupSnake(std::vector<std::pair<int, int>> &snake, const int &init_size) {
  for (int i = 0; i < init_size; i++) {
    snake.push_back({10 + i, 3});
  }
}

void update_snake_coordinates(std::vector<std::pair<int, int>> &snake,
                              const std::array<int, 2> dxdy, int nx, int ny) {
  // on fait coulisser le snake
  for (int i = snake.size() - 1; i >= 1; i--) {
    snake[i] = snake[i - 1];
  }
  // on met à jour la tête
  auto [x, y] = snake[0];
  auto [dx, dy] = dxdy;
  int nouveau_x = x + dx;
  int nouveau_y = y + dy;

  if (nouveau_x == 0) {
    nouveau_x = nx - 2;
  } else if (nouveau_x == nx - 1) {
    nouveau_x = 1;
  }
  if (nouveau_y == 0) {
    nouveau_y = ny - 2;
  } else if (nouveau_y == ny - 1) {
    nouveau_y = 1;
  }

  snake[0] = {nouveau_x, nouveau_y};
}

void startGame(const int &lap, const int &nx, const int &ny,
               std::vector<std::pair<int, int>> &snake, std::vector<int> &bg) {
  char key;
  std::array<int, 2> dxdy{-1, 0};
  std::array<int, 2> food{0, 0};
  int points = 0;
  const int frameLength = 50;
  int slowMult = 4;

  createFood(bg, food, nx, ny);

  while (true) {
    // d'abord opérations normales
    for (int i = 0; i < slowMult - 1; i++) {
      internal::frameSleep(frameLength);
      if (internal::keyEvent()) {
        std::cin >> key;
        dxdy = snake_movement(key, dxdy[0], dxdy[1]);
      }
      // TODO: probablement pas besoin de redessiner le snake à chaque fois
      backgroundClear();
      add_snake(snake, bg, nx, ny);
      printFrame(nx, ny, bg, points);
      remove_snake(snake, bg, nx, ny);
    }

    // opération seulement mouvement snake
    bool out = verifyBorder(snake, nx, ny);
    if (out == false) {
      std::cerr << "t'es mort" << std::endl;
      exit(1);
    }

    bool eat = eatFood(food, snake);
    if (eat) {
      points += 10;
      createFood(bg, food, nx, ny);
      snake.push_back({-1, -1});
    }
    update_snake_coordinates(snake, dxdy, nx, ny);
  }
}

int main() {
  const int snake_init_sz = 3;
  const int nx = 40;
  const int ny = 25;
  int lap = 200;

  std::vector<int> background(nx * ny, -1);

  std::vector<std::pair<int, int>> snake;
  backgroundSetup(nx, ny, background);
  setupSnake(snake, snake_init_sz);

  startGame(lap, nx, ny, snake, background);
  return EXIT_SUCCESS;
}
