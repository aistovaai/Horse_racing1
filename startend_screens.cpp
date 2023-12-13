#include "startend_screens.h"

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

void start_of_the_game()
{
    Very_Simple_window rules_window(Point(x_max() / 2, y_max() / 2), 985, 393, "Rules");
    Image rules(Point(0, 0), "game_rules1.png");
    rules_window.attach(rules);
    rules_window.wait_for_button();
    rules_window.hide();
}

void end_of_the_game(int win_w, int win_h, int p1, int p2, int p3, int p4)
{
    My_cool_window result_screen(Point(0, 0), win_w, win_h, "Results");

    std::string x = results(p1, p2, p3, p4);

    Text print = Text(Point(win_w / 2 - 50, win_h / 2), x);

    print.set_font(FL_COURIER);
    print.set_font_size(20);

    result_screen.attach(print);

    result_screen.wait_for_button();
}