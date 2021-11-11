#include <iostream>
#include <string>
#include <vector>

#include "display.h"
#include "internals.h"
#include "menu_snake.h"

void printMenu(std::vector<std::string> &options, int selected) {
  backgroundClear();
  printTitle();
  printCenteredLine(" ");
  printCenteredLine(" ");
  printCenteredLine("Use ZQSD to navigate");
  printCenteredLine(" ");
  printCenteredLine(" ");
  for (int i = 0; i < options.size(); i++) {
    printCenteredLine(" ");
    if (i == selected) {
      printCenteredLine(options.at(i), "pink_highlight");
    } else {
      printCenteredLine(options.at(i));
    }    
    printCenteredLine(" ");
  }
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
