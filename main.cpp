#include <iostream>
#include <exception>
#include <vector>
#include <random>

#include <Graph_lib/Simple_window.h>
#include "cube.h"
#include "Race.h"

using namespace Graph_lib;

std::string results(int blue, int red, int yellow, int green)
{

  std::string x = "";
  int winner = std::max({blue, red, yellow, green});

  if (winner == blue)
  {
    x += "Blue ";
  }
  if (winner == red)
  {
    x += "Red ";
  }
  if (winner == yellow)
  {
    x += "Yellow ";
  }
  if (winner == green)
  {
    x += "Green ";
  }
  x += "won!";
  return x;
}

int main()
try
{

  Very_Simple_window rules_window(Point(x_max() / 2, y_max() / 2), 985, 393, "Rules");
  Image rules(Point(0, 0), "game_rules1.png");
  rules_window.attach(rules);
  rules_window.wait_for_button();
  rules_window.hide();

  srand(time(NULL));

  int win_w = x_max();
  int win_h = y_max();
  int player = 0;

  int p1 = 0;
  int p2 = 0;
  int p3 = 0;
  int p4 = 0;
  int trap_point = 12;

  My_window win(Point(0, 0), win_w, win_h, "Race");
  Point cube_place{win_w / 2 - 64, win_h / 2 - 64};
  Field field{win_w, win_h};

  field.attach_pole(win);

  Image trap{Point(win_w * 31 / 48, win_h * 2 / 4 - 75), "trap.png"};
  win.attach(trap);
  win.wait_for_button();

  while (win.Fl_wait())
  {
    if (field.coordinates_knights_vec[player].can_move() == false)
    {
      field.coordinates_knights_vec[player].set_move();
    }
    else
    {

      int cube_result = random();
      Image cube{cube_place, cube_name(cube_result)};

      win.attach(cube);

      win.wait_for_button();

      field.change_text(player, cube_result);

      field.move_knights(win_w, win_h, player, cube_result);

      p1 = field.current_steps(0);
      p2 = field.current_steps(1);
      p3 = field.current_steps(2);
      p4 = field.current_steps(3);

      if (field.current_steps(player) == trap_point)
      {
        field.coordinates_knights_vec[player].set_move();
      }
      win.wait_for_button();
    }

    player++;

    if (player == 4)
    {
      player = 0;
    }

    if (((p1 >= 24) && (p2 >= 24) && (p3 >= 24) && (p4 >= 24)))
      break;
  }

  win.hide();

  My_cool_window result_screen(Point(0, 0), win_w, win_h, "Results");

  std::string x = results(p1, p2, p3, p4);

  Text print = Text(Point(win_w / 2 - 50, win_h / 2), x);

  print.set_font(FL_COURIER);
  print.set_font_size(20);

  result_screen.attach(print);

  result_screen.wait_for_button();
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
