#include <iostream>
#include <string>

#include <stdlib.h>
#include <time.h>

#include <Graph_lib/Graph.h>
#include <Graph_lib/Simple_window.h>

using namespace Graph_lib;

int random() //получаем число  в [1;6]
{

    return rand() % 6 + 1;
};

std::string cube_name(int cube_result) //на основе числа в [1;6] получаем нужную картинку кубика (её имя)
{
    return "cube" + std::to_string(cube_result) + ".png";
};
