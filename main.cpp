#include <iostream>
#include <exception>
#include <vector>
#include <random>

#include <Graph_lib/Simple_window.h>
#include "cube.h"
#include "Race.h"
#include "startend_screens.h"

using namespace Graph_lib;

void game_step(Field &field, int player, int cube_result)
{
  field.change_text(player, cube_result);
  field.move_knights(field.win_w_value(), field.win_h_value(), player, cube_result);
}

int main()
try
{
  srand(time(NULL));
  int win_w = x_max();
  int win_h = y_max();
  int player = 0;
  std::vector<int> players{0, 0, 0, 0};
  int trap_point = 12;

  start_of_the_game();

  My_window win(Point(0, 0), win_w, win_h, "Race");
  Point cube_place{win_w / 2 - 64, win_h / 2 - 64};
  Field field{win_w, win_h};
  Image trap{Point(win_w * 31 / 48, win_h * 2 / 4 - 75), "trap.png"};

  field.attach_pole(win);
  win.attach(trap);
  win.wait_for_button();

  while (win.Fl_wait())
  {
    if (field.coordinates_knights_vec[player].can_move() == false)
      field.coordinates_knights_vec[player].set_move();
    else
    {
      int cube_result = random();
      Image cube{cube_place, cube_name(cube_result)};

      win.attach(cube);
      win.wait_for_button();

      game_step(field, player, cube_result);
      players[player] = field.current_steps(player);

      if (field.current_steps(player) == trap_point)
        field.coordinates_knights_vec[player].set_move();

      win.wait_for_button();
    }
    player++;

    if (player == 4)
      player = 0;

    if (((players[0] >= 24) && (players[1] >= 24) && (players[2] >= 24) && (players[3] >= 24)))
      break;
  }
  win.hide();
  end_of_the_game(win_w, win_h, players);
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
