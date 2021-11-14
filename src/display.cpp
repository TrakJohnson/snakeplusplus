#include "stdlib.h"

#include <array>
#include <cmath>
#include <iomanip>
#include <iostream>
#include <map>
#include <ostream>
#include <sstream>
#include <stdexcept>
#include <stdio.h>
#include <sys/ioctl.h>
#include <unistd.h>
#include <vector>

// ---
// Terminal utils

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

// ---
// String utils

std::string trimDouble(double x, int precision) {
  // precision 0 gives just the int
  if (precision == 0) {
    precision = -1; // to remove the dot
  }
  return std::to_string(x).substr(0,
                                  std::to_string(x).find(".") + precision + 1);
}

std::string paddingFill(std::string &s, int finalLength) {
  // go from
  // |ab|
  // |abc|
  // |a|
  // --> to
  // | ab  |
  // | abc |
  // |  a  |
  int l = s.length();
  std::string additional = ((finalLength - l) % 2) ? " " : "";
  std::string base = std::string((finalLength - l) / 2, ' ');
  std::string padding = " ";
  if (finalLength <= l) {
    return padding + s + padding;
  } else {
    return padding + base + s + base + additional + padding;
  }
}

std::string colorize(std::string s, std::string color) {
  std::map<std::string, std::string> colors = {
      {"orange_highlight", "\e[7;33;40m"}, {"pink_highlight", "\e[7;35;47m"},
      {"green_highlight", "\e[7;32;47m"},  {"dark_highlight", "\e[7;30;47m"},
      {"orange_highlight", "\e[4;37;43m"},
  };

  if (color == "normal") {
    return s;
  } else {
    return colors.at(color) + s + "\e[0m";
  }
}

void printCenteredLine(std::string line, std::string color = "normal",
                       int lineLength = -1, int charSizeModifier = 1) {
  // if charSizeModifier is 2, your character is twice as wide as a normal one

  if (lineLength == -1) {
    lineLength = line.length();
  }
  // std::cout << getTermDimensions().second << std::endl;
  int space = (getTermDimensions().second - charSizeModifier * lineLength) / 2;
  std::cout << std::setprecision(2) << std::string(space, ' ')
            << colorize(line, color) << std::endl;
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
                int points, int frameLength, double speed) {
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

  printCenteredLine(std::string("Points: ") + std::to_string(points));
  printCenteredLine(std::string("Vitesse: ") + trimDouble(speed, 1) + " px/s");
}
