#include <string>
#include <vector>

void printChoices(std::vector<std::pair<std::string, std::string>> &options,
		  int selected,
                  std::string selected_color,
		  std::string inactiveColor,
		  bool showTooltip = true,
		  std::string tooltipColor = "normal");
void printMenu(std::vector<std::pair<std::string, std::string>> &options, int selected);
int menuSelect(std::vector<std::pair<std::string, std::string>> &options);
