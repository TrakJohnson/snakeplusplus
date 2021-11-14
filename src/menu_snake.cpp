#include <algorithm>
#include <iostream>
#include <iterator>
#include <ostream>
#include <string>
#include <vector>

#include "display.h"
#include "internals.h"
#include "menu_snake.h"

using menuentry = std::pair<std::string, std::string>;

void printChoices(std::vector<menuentry> &options, int selected,
                  std::string selectedColor, std::string inactiveColor,
                  bool showTooltip,
                  std::string tooltipColor) {

  // Pour un menu plaisant, on harmonise les largeurs de "boutons"
  // Calcul de la longeur pour que tout tienne
  std::vector<int> lengths;
  std::transform(std::begin(options), std::end(options),
                 std::back_inserter(lengths),
                 [](menuentry s) { return s.first.length(); });
  auto longestLength = *max_element(std::begin(lengths), std::end(lengths));

  for (int i = 0; i < options.size(); i++) {
    std::string finalText =
        colorize(paddingFill(options.at(i).first, longestLength),
                 i == selected ? "green_highlight" : "dark_highlight");

    // TODO fix this messy shit with colors
    printCenteredLine(finalText, "normal", longestLength + 2);
    printCenteredLine(" ");

    // tooltips on each menu option
  }
  if (showTooltip) {
    printCenteredLine(" ");
    printCenteredLine(" ");
    printCenteredLine(" ");
    printCenteredLine(options.at(selected).second, tooltipColor);
  }
}

void printMenu(std::vector<menuentry> &options, int selected) {
  backgroundClear();
  printTitle();
  printCenteredLine(" ");
  printCenteredLine(" ");
  printCenteredLine("Utilisez les touches ZQSD pour la navigation");
  printCenteredLine("Sélectionnez avec A");
  printCenteredLine(" ");
  printCenteredLine(" ");
  printChoices(options, selected, "pink_highlight", "dark_highlight", true, "orange_highlight");
}

int menuSelect(std::vector<menuentry> &options) {
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
