#ifndef STARTEND_SCREENS_H
#include "Race.h"

std::string results(int blue, int red, int yellow, int green);

void start_of_the_game();

void end_of_the_game(int win_w, int win_h, std::vector<int> players);

#endif