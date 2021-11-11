#include "stdlib.h"
#include <array>
#include <iostream>
#include <ostream>
#include <vector>
#include <cmath>

const char *cmd_clear = "clear";

void backgroundClear() {
  int out = system(cmd_clear);
  if (out != 0) {
    std::cerr << "clear command failed" << std::endl;
    exit(1);
  }
}

void printFrame(const int &nx, const int &ny, const std::vector<int> &bg,
                int points, int frameLength, int slowMult) {

  // Titre
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
    // cpp ne semble pas connaître la taille d'un unicode
    // std::cout << titre[0].size() << " " << std::mbrlen(titre[0][0]) << std::endl;
    std::cout << std::string((2 * nx - 44) / 2, ' ') << s << std::endl;
  }

  // Jeu
  std::array<std::string, 5> couleurs{
    "　",                     // vide
    "\x1b[0;37;40m　\x1b[0m", // murs
    "\e[0;37;45m　\e[0m",
    // "\x1b[1;37;41m　\x1b[0m", // nourriture
    "\x1b[6;30;42m　\x1b[0m", // corps
    "\x1b[1;37;44m　\x1b[0m"  // tête
  };
  
  for (int j = 0; j < ny; j++) {
    for (int i = 0; i < nx; i++) {
      std::cout << couleurs.at(bg.at(i + j * nx));
    }
    std::cout << std::endl;
  }

  // Infos en bas
  std::cout << "Points: " << points << std::endl;
  std::cout << "Vitesse: " << std::round(1000.0 / (slowMult*frameLength))  << " pixels/s"<< std::endl;
}
