#include <iostream>
#include <vector>
#include <string>

#include <stdlib.h>
#include <time.h>

#include <Graph_lib/Graph.h>
#include <Graph_lib/Simple_window.h>
#include "cube.h"

using namespace Graph_lib;

int random() 
{
    srand(time(NULL));

    return rand() % 6 + 1;
};


int draw_cube(int cube_result)
{
try
{
    win.detach(cube);

    std::cout << cube_result;
    switch (cube_result)
    {
    case 1:
    {
        Image cube{cube_place, "cube1.png"};

        win.attach(cube);
        win.wait_for_button();
        break;
    };

    case 2:
    {
        Image cube{cube_place, "cube2.png"};

        win.attach(cube);
        win.wait_for_button();
        break;
    };

    case 3:
    {
        Image cube{cube_place, "cube3.png"};

        win.attach(cube);
        win.wait_for_button();
        break;
    };

    case 4:
    {
        Image cube{cube_place, "cube4.png"};

        win.attach(cube);
        win.wait_for_button();
        break;
    };

    case 5:
    {
        Image cube{cube_place, "cube5.png"};

        win.attach(cube);
        win.wait_for_button();
        break;
    };

    case 6:
    {
        Image cube{cube_place, "cube6.png"};

        win.attach(cube);
        win.wait_for_button();
        break;
    };

    default:
        std::cout << "not expected result" << "\n";
        break;
    };

}
catch (std::exception& e)
{
    std::cerr << e.what() << std::endl;
    return 1;
}
};


int main()
{
    win.wait_for_button();

    for (int i = 1; i < 7; i++)
    {
        draw_cube(i);

        std::cout << i << "cat "<< " ";
    }

    win.wait_for_button();
};
