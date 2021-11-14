#include <algorithm>
#include <iostream>
#include <iterator>
#include <ostream>
#include <string>
#include <vector>

#include "display.h"
#include "internals.h"
#include "menu_snake.h"

void printChoices(std::vector<std::string> &options, int selected,
                  std::string selectedColor, std::string inactiveColor) {

  // Pour un menu plaisant, on harmonise les largeurs de "boutons"
  // Calcul de la longeur pour que tout tienne
  std::vector<int> lengths;
  std::transform(std::begin(options), std::end(options),
                 std::back_inserter(lengths),
                 [](std::string s) { return s.length(); });
  auto longestLength = *max_element(std::begin(lengths), std::end(lengths));

  for (int i = 0; i < options.size(); i++) {
    std::string finalText =
      colorize(paddingFill(options.at(i), longestLength),
                 i == selected ? "green_highlight" : "dark_highlight");
    
    // TODO fix this messy shit with colors
    // TODO big align problems
    printCenteredLine(finalText, "normal", longestLength);
    printCenteredLine(" ");
  }
}

void printMenu(std::vector<std::string> &options, int selected) {
  backgroundClear();
  printTitle();
  printCenteredLine(" ");
  printCenteredLine(" ");
  printCenteredLine("Utilisez les touches ZQSD pour la navigation");
  printCenteredLine("Sélectionnez avec A");
  printCenteredLine(" ");
  printCenteredLine(" ");
  printChoices(options, selected, "pink_highlight", "dark_highlight");
}

int menuSelect(std::vector<std::string> &options) {
  char key;
  int selectedOption = 0;

  printMenu(options, selectedOption);
  while (true) {
    internal::frameSleep(100);
    if (internal::keyEvent()) {
      std::cin >> key;
      if (key == 'z') {
        selectedOption = (selectedOption - 1) % options.size();
        printMenu(options, selectedOption);
      } else if (key == 's') {
        selectedOption = (selectedOption + 1) % options.size();
        printMenu(options, selectedOption);
      } else if (key == 'a') {
        return selectedOption;
      }
    }
  }
}
