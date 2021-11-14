#include <string>
#include <vector>

void printChoices(std::vector<std::string> &options,
		  int selected,
                  std::string selected_color,
		  std::string inactiveColor);
void printMenu(std::vector<std::string> &options, int selected);
int menuSelect(std::vector<std::string> &options);
