#include <iostream>
#include <exception>
#include <vector>
#include <random>

#include <Graph_lib/Simple_window.h>
#include "cube.h"
#include "Race.h"

using namespace Graph_lib;

int main()
try
{
  int win_w = 1200;
  int win_h = 800;
  int player = 0;

  int p1 = 0;
  int p2 = 0;
  int p3 = 0;
  int p4 = 0;
  std::string x = "";

  My_window win(Point(0, 0), win_w, win_h, "Race");
  Point cube_place{win_w / 2 - 64, win_h / 2 - 64};

  draw_pole(win, win_w, win_h); // здесь нужен двойной цикл while true и for
  win.wait_for_button();

  while (not((p1 >= 24) & (p2 >= 24) & (p3 >= 24) & (p4 >= 24)))
  {
    int cube_result = random();
    Image cube{cube_place, cube_name(cube_result)};

    win.attach(cube);
    win.wait_for_button();

    if (player == 4)
    {
      player = 0;
    }

    p1 = steps_check(0);
    p2 = steps_check(1);
    p3 = steps_check(2);
    p4 = steps_check(3);

    change_text(player, cube_result);

    move_knights(win_w, win_h, player, cube_result);

    win.wait_for_button();
    player++;
  }

  int player1 = std::max({p1, p2, p3, p4});

  win.hide();

  My_window results(Point(0, 0), win_w, win_h, "Results");

  if (player1 == p1)
  {
    x = "Blue won!";
  }
  if (player1 == p2)
  {
    x = "Red won!";
  }
  if (player1 == p3)
  {
    x = "Yellow won!";
  }
  if (player1 == p4)
  {
    x = "Green won!";
  }

  Text print = Text(Point(win_w / 2, win_h / 2), x);
  results.attach(print);

  results.wait_for_button();
}
catch (std::exception &e)
{
  std::cerr << e.what() << std::endl;
  return 1;
}
catch (...)
{
  std::cerr << "Oops, something went wrong..." << std::endl;
  return 2;
}
