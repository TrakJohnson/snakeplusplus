#include "sys/ioctl.h"
#include <array>
#include <cstdlib>
#include <iostream>
#include <ostream>
#include <vector>
#include <queue>
#include <cstdlib>
#include <ctime>

#include "stdlib.h"

#include "config.h"
#include "display.h"
#include "food.h"
#include "internals.h"
#include "menu_snake.h"


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

void snakeMovement(const char &k, std::queue<std::array<int, 2>> &dxdy_queue) {
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

  // must compare to queue.back() to get desired behaviour
  auto [dx, dy] = dxdy_queue.back();
  // empêche l'utilisateur de se rentrer dedans "sur place"
  if (dx_new * dx == 0 && dy_new * dy == 0) {
    dxdy_queue.push(std::array<int, 2>{dx_new, dy_new});
  }
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

int speedToSlowMult(double s, int frameLength) {
  return (int)(1000.0 / (s * frameLength));
}

void startGame(const int &nx, const int &ny,
               std::vector<std::pair<int, int>> &snake, std::vector<int> &bg) {

  char key;

  // we use a movement queue instead of a single variable
  // this allows the user to chain movements when the snake is in low speed
  // and avoid eating yourself accidentally in between movement frames
  std::queue<std::array<int, 2>> dxdy_queue;
  dxdy_queue.push({-1, 0});
  
  std::array<int, 2> food{0, 0};
  int points = 0;
  const int frameLength = 16;
  double speed{5.5};
  int slowMult{speedToSlowMult(speed, frameLength)};

  createFood(bg, food, nx, ny);

  while (true) {
    // d'abord opérations normales
    for (int i = 0; i < slowMult - 1; i++) {
      internal::frameSleep(frameLength);
      if (internal::keyEvent()) {
        std::cin >> key;
	// modifies the queue inplace
        snakeMovement(key, dxdy_queue);
      }
    }

    backgroundClear();
    add_snake(snake, bg, nx, ny);
    printFrame(nx, ny, bg, points, frameLength, speed);
    remove_snake(snake, bg, nx, ny);

    if (dxdy_queue.size() > 1) {
      dxdy_queue.pop();
    }
    update_snake_coordinates(snake, dxdy_queue.front(), nx, ny);

    bool out = verifyBorder(snake, nx, ny);
    if (out == false) {
      // TODO : proper death screen
      std::cerr << "t'es mort" << std::endl;
      exit(1);
    }

    bool eat = eatFood(food, snake);
    if (eat) {
      points += 1;
      // maj de la vitesse
      speed += 0.5;
      slowMult = speedToSlowMult(speed, frameLength);
      // nouvelle nourriture
      createFood(bg, food, nx, ny);
      snake.push_back({-1, -1});
    }
  }
}

int main() {
  const int snake_init_sz = 3;
  const int nx = 40;
  const int ny = 25;

  // change the rand seed each time
  srand((int) time(0));
  
  std::vector<int> background(nx * ny, 0);
  std::vector<std::pair<int, int>> snake;

  std::vector<std::string> choices{"1 joueur", "2 joueurs", "Quitter"};
  int choice{menuSelect(choices)};

  if (choice == 0) {
    // printChoices(choices, 0, "pink_highlight", "dark_highlight");
    backgroundSetup(nx, ny, background);
    setupSnake(snake, snake_init_sz);
    startGame(nx, ny, snake, background);
  } else if (choice == 1) {
    // TODO
    return EXIT_FAILURE;
  } else if (choice == 2) {
    return EXIT_SUCCESS;
  }

  return EXIT_SUCCESS;
}
