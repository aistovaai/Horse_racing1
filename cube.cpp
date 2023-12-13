#include <iostream>
#include <string>

#include <stdlib.h>
#include <time.h>
#include "cube.h"

int random()
{
    return rand() % 6 + 1;
};

std::string cube_name(int cube_result)
{
    return "cube" + std::to_string(cube_result) + ".png";
};
