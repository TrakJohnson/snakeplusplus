#include <string>
#include <vector>

void backgroundClear();
std::string paddingFill(std::string &s, int nToFill); // ,std::string padding = " ");
void printCenteredLine(const std::string line, std::string color = "normal",
                       int lineLength = -1, int charSizeModifier = 1);
std::string colorize(std::string s, std::string color);
void printTitle();
void printFrame(const int &nx, const int &ny, const std::vector<int> &bg,
                int points, int frameLength, double speed);
