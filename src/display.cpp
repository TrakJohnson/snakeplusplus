#include "stdlib.h"
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

void printFrame(const int &nx, const int &ny, const std::vector<int> &bg, int points) {

   
  std::vector<std::string> titre = {"  ██████  ███▄    █  ▄▄▄       ██ ▄█▀▓█████ ",
    "▒██    ▒  ██ ▀█   █ ▒████▄     ██▄█▒ ▓█   ▀ ",
    "░ ▓██▄   ▓██  ▀█ ██▒▒██  ▀█▄  ▓███▄░ ▒███   ",
    "  ▒   ██▒▓██▒  ▐▌██▒░██▄▄▄▄██ ▓██ █▄ ▒▓█  ▄ ",
    "▒██████▒▒▒██░   ▓██░ ▓█   ▓██▒▒██▒ █▄░▒████▒",
    "▒ ▒▓▒ ▒ ░░ ▒░   ▒ ▒  ▒▒   ▓▒█░▒ ▒▒ ▓▒░░ ▒░ ░",
    "░ ░▒  ░ ░░ ░░   ░ ▒░  ▒   ▒▒ ░░ ░▒ ▒░ ░ ░  ░",
    "░  ░  ░     ░   ░ ░   ░   ▒   ░ ░░ ░    ░   ",
    "      ░           ░       ░  ░░  ░      ░  ░", 
    ""};

  for (std::string s: titre) {
    // int i = (int)((nx - s.size())/2);
    // std::cout << i << std::endl;
    std::cout << std::string((2*nx - 44)/2, ' ') << s << std::endl;
  }

  for (int j = 0; j < ny; j++) {
    for (int i = 0; i < nx; i++) {
      if (bg[i + j * nx] == 1) {
        std::cout << "\x1b[0;37;40m"
                  << "　"
                  << "\x1b[0m";
      } else if (bg[i + j * nx] == 2) {
        std::cout << "\x1b[1;37;41m"
                  << "　"
                  << "\x1b[0m";
      } else if (bg[i + j * nx] == 3) {
        std::cout << "\x1b[6;30;42m"
                  << "　"
                  << "\x1b[0m";
      } else if (bg[i + j * nx] == 4) {
        std::cout << "\x1b[1;37;44m"
                  << "　"
                  << "\x1b[0m";
      } else {
        std::cout << "　";
      }
    }
    std::cout << std::endl;
  }
  std::cout << "Points: " << points << std::endl;
}
