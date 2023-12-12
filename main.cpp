#include <iostream>
#include <exception>
#include <vector>
#include <random>

#include <Graph_lib/Simple_window.h>
#include "cube.h"
#include "Race.h"


std::vector<bool> can_move {true, true, true, true}; //та самая контролирующая штука 

using namespace Graph_lib;

int main()
try
{
  int win_w = 1200;
  int win_h = 800;
  int player = 0;
  int trap_point = 12;

  int p1 = 0;
  int p2 = 0;
  int p3 = 0;
  int p4 = 0;
  std::string x = "";
  srand(time(NULL));

  My_window win(Point(10, 10), win_w, win_h + 100, "Race");
  Point cube_place{win_w / 2 - 64, win_h / 2 - 64};

  std::string got_trapped_text = "Got trapped";
  Text got_trapped {Point(win_w / 2, win_h / 2), got_trapped_text};
  got_trapped.set_font(FL_COURIER);
  got_trapped.set_font_size(18);
  got_trapped.set_color(FL_RED);

  draw_pole(win, win_w, win_h); // здесь нужен двойной цикл while true и for

  Text trap {Point(win_w * 32 / 48, win_h * 2 / 4), "There is a trap"};
  trap.set_font(FL_COURIER);
  trap.set_font_size(20);
  trap.set_color(FL_RED);
  win.attach(trap);

  win.wait_for_button();
  

  while (not((p1 >= 24) & (p2 >= 24) & (p3 >= 24) & (p4 >= 24)))
  {
    if (can_move[player])
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

    //int trap_point = trap_point_st;

    change_text(player, cube_result);

    move_knights(win_w, win_h, player, cube_result);

    if (steps_check(player) == trap_point)
    {
        can_move[player] = false;
        win.attach(got_trapped);
        win.wait_for_button();

        win.detach(got_trapped);
    }

    win.wait_for_button();

    } else
    {
      can_move[player] = true;
    }

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

  print.set_font(FL_COURIER);
  print.set_font_size(18);
  
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
