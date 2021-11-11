#include "stdlib.h"

#include <array>
#include <cmath>
#include <iostream>
#include <sstream>
#include <ostream>
#include <stdexcept>
#include <stdio.h>
#include <sys/ioctl.h>
#include <unistd.h>
#include <vector>

const char *cmd_clear = "clear";

void backgroundClear() {
  int out = system(cmd_clear);
  if (out != 0) {
    std::cerr << "clear command failed" << std::endl;
    exit(1);
  }
}

// TODO: is it ok to run it a lot of times ?
std::pair<int, int> getTermDimensions() {
  struct winsize w;
  ioctl(STDOUT_FILENO, TIOCGWINSZ, &w);
  return std::pair<int, int>{w.ws_row, w.ws_col};
}

std::string colorize(std::string s, std::string color) {
  if (color == "orange_highlight") {
    return std::string("\e[4;37;43m") + s + "\e[0m";
  } else if (color == "pink_highlight") {
    return std::string("\e[7;35;40m") + s + "\e[0m";
  } else if (color == "normal") {
    return s;
  }
  // TODO ajouter les autres cas ici
  throw std::invalid_argument(std::string("Color not found: ") + color);
  return s;
}

void printCenteredLine(std::string line, std::string color = "normal", int lineLength = -1, int charSizeModifier = 1) {
  // charSizeModifier is 2 is your character is twice as wide as a normal one
  
  if (lineLength == -1) {
    lineLength = line.length();
  }
  // std::cout << getTermDimensions().second << std::endl;
  int space = (getTermDimensions().second - charSizeModifier * lineLength) / 2;
  std::cout << std::string(space, ' ') << colorize(line, color) << std::endl;
}

void printTitle() {
  std::array<std::string, 11> titre = {
    "",
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
    // std::cout << titre[0].size() << " " << std::mbrlen(titre[0][0]);
    
    printCenteredLine(s, "normal", 44);
  }  
}

void printFrame(const int &nx, const int &ny, const std::vector<int> &bg,
                int points, int frameLength, int slowMult) {
  printTitle();
  // Jeu
  std::array<std::string, 5> colors{
      "　",                     // vide
      "\x1b[0;37;40m　\x1b[0m", // murs
      "\e[0;37;45m　\e[0m",
      // "\x1b[1;37;41m　\x1b[0m", // nourriture
      "\x1b[6;30;42m　\x1b[0m", // corps
      "\x1b[1;37;44m　\x1b[0m"  // tête
  };

  for (int j = 0; j < ny; j++) {
    std::string line;
    for (int i = 0; i < nx; i++) {
      line.append(colors.at(bg.at(i + j * nx)));
    }
    printCenteredLine(line, "normal", nx, 2);
  }
  std::cout << std::endl;
  
  std::stringstream ss;
  ss << "Points: " << points
     << "\nVitesse: " << std::round(1000.0 / (slowMult * frameLength)) << " pixels/s"
     << std::endl;
  
  printCenteredLine(std::string("Points: ") + std::to_string(points));
  printCenteredLine(std::string("Vitesse: ") + std::to_string((int)(1000.0 / (slowMult * frameLength))) + " px/s");
}
