#include "stdlib.h"
#include <array>
#include <iostream>
#include <vector>

const char *cmd_clear = "clear";

void backgroundClear() {
  int out = system(cmd_clear);
  if (out != 0) {
    std::cerr << "clear command failed" << std::endl;
    exit(1);
  }
}

void printFrame(const int &nx, const int &ny, const std::vector<int> &bg,
                int points) {

  std::array<std::string, 10> titre = {
      "  ██████  ███▄    █  ▄▄▄       ██ ▄█▀▓█████ ",
      "▒██    ▒  ██ ▀█   █ ▒████▄     ██▄█▒ ▓█   ▀ ",
      "░ ▓██▄   ▓██  ▀█ ██▒▒██  ▀█▄  ▓███▄░ ▒███   ",
      "  ▒   ██▒▓██▒  ▐▌██▒░██▄▄▄▄██ ▓██ █▄ ▒▓█  ▄ ",
      "▒██████▒▒▒██░   ▓██░ ▓█   ▓██▒▒██▒ █▄░▒████▒",
      "▒ ▒▓▒ ▒ ░░ ▒░   ▒ ▒  ▒▒   ▓▒█░▒ ▒▒ ▓▒░░ ▒░ ░",
      "░ ░▒  ░ ░░ ░░   ░ ▒░  ▒   ▒▒ ░░ ░▒ ▒░ ░ ░  ░",
      "░  ░  ░     ░   ░ ░   ░   ▒   ░ ░░ ░    ░   ",
      "      ░           ░       ░  ░░  ░      ░  ░",
      ""};

  for (std::string s : titre) {
    // TODO: remplacer 44...
    std::cout << std::string((2 * nx - 44) / 2, ' ') << s << std::endl;
  }

  std::array<std::string, 5> couleurs{
    "　",                     // vide
    "\x1b[0;37;40m　\x1b[0m", // murs
    "\x1b[1;37;41m　\x1b[0m", // nourriture
    "\x1b[6;30;42m　\x1b[0m", // corps
    "\x1b[1;37;44m　\x1b[0m"  // tête
  };

  for (int j = 0; j < ny; j++) {
    for (int i = 0; i < nx; i++) {
      std::cout << couleurs.at(bg.at(i + j * nx));
    }
    std::cout << std::endl;
  }
  std::cout << "Points: " << points << std::endl;
}
